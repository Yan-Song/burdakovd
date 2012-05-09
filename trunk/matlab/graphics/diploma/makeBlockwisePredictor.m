function predictorFactory = makeBlockwisePredictor(blockSize, pixelwisePredictorFactory)
    predictorFactory = ...
        @(db, outDir) ...
        makeBlockWisePredictorImpl( ...
            blockSize, ...
            pixelwisePredictorFactory, ...
            db, ...
            outDir);
end

function predictor = makeBlockWisePredictorImpl(blockSize, pixelwisePredictorFactory, db, outDir)
    nCrf = min(floor(db.size() / 3), 30);
    nPixelwise = floor((db.size() - nCrf) / 2);
    nBlockwise = db.size() - nCrf - nPixelwise;
    fprintf('Have got %d training images, will use %d for pixelwise training, %d for blockwise, %d for crf gridsearch\n', ...
        db.size(), nPixelwise, nBlockwise, nCrf);
    perm = randperm(db.size());
    pixelwiseTrainIds = perm(1 : nPixelwise);
    blockwiseTrainIds = perm(nPixelwise + 1 : nPixelwise + nBlockwise);
    crfTrainIds = perm(nPixelwise + nBlockwise + 1 : end);

    predictor.blockSize = blockSize;
    predictor.pixelwise = pixelwisePredictorFactory(db.sub(pixelwiseTrainIds), outDir);
    predictor.blockwise = makeBlockwiseFromPixelwise(blockSize, predictor.pixelwise, db.sub(blockwiseTrainIds), outDir);
    
    coefficient = crfGridSearch(db.sub(crfTrainIds), predictor.blockwise.predict, blockSize);
    
    predictor.predict = makeCRFdPredictor(predictor.blockwise.predict, coefficient, outDir);
end

function coefficient = crfGridSearch(db, predictor, blockSize)
    doers = arrayfun(@(i) predictWithCRFStage1(db.bw(i), db.name(i), predictor), 1 : db.size(), 'UniformOutput', false);
    gts = arrayfun(@(i) makeBlockwiseGroundTruthFromPixelwise(blockSize, db.groundTruth(i), db.bw(i), db.original(i), 'no'), 1 : db.size(), 'UniformOutput', false);
    evaluate = @(coefficient) evaluatePrediction(doers, gts, coefficient);
    
    nCells = 10; nIterations = 5;
    left = -5; right = 5;
    
    fprintf('Doing CRF gridsearch with nCells = %d, nIterations = %d\n', nCells, nIterations);
    for stepId = 1 : nIterations
        fprintf('  Iteration %d/%d. Searching on %.3f..%.3f\n', stepId, nIterations, exp(left), exp(right));
        step = (right - left) / nCells;
        points = left + (1 : (nCells - 1)) * step;
        values = arrayfun(evaluate, exp(points));
        [accuracy, i] = max(values);
        fprintf('  The best accuracy was %.6f%% for %.3f\n\n', accuracy * 100, exp(points(i)));
        left = points(i) - step;
        right = points(i) + step;
    end
    coefficient = exp(points(i));
    fprintf('Chosen CRF coefficient: %.3f\n', coefficient);
end

function evaluation = evaluatePrediction(doers, gts, coefficient)
    predictions = cellfun(@(doer) doer(coefficient), doers, 'UniformOutput', false);
    accuracies = arrayfun(@(i) rawBlockwiseValidate(gts{i}, predictions{i}), 1 : length(doers));
    evaluation = mean(accuracies);
    fprintf('    Accuracy for %.3f is %.6f%%\n', coefficient, evaluation * 100);
end

function predictor = makeCRFdPredictor(predictor, coefficient, outDir)
    predictor = @(bw, name) predictWithCRF(bw, name, predictor, coefficient, [outDir name]);
end

function [doer, windows, N] = predictWithCRFStage1(bw, name, predictor)
    [Y_hat, votes, windows] = predictor(bw, name);

    % Y_hat - выход классификатора, Nx1
    % votes - выход классификатора, количество голосов для каждого 
    % суперпикселя за каждую метку, NxC
    % windows - разметка исходного ихображения на блоки, HxW
    % crfParameterValue - параметр CRF, вес парных потенциалов
    
    N = size(votes, 1);
    C = size(votes, 2);
    
    assert(min(windows(:)) == 1);
    assert(max(windows(:)) == N);

    % унарный потенциал для CRF
    votes = votes ./ repmat(sum(votes, 2), [1 size(votes, 2)]);
    unary = single(-log(votes + 1e-3))';

    % начальные значения меток
    start = Y_hat;
    assert(isempty(find(start ~= 1 & start ~= 2 & start ~= 4, 1)));
    start(start == 4) = 3;
    start = start' - 1;

    % парные потенциалы для суперпикселей
    wh = windows(size(windows, 1), 1);
    ws = 1 : N;
    uppers = ws(rem(ws, wh) > 0);
    lowers = uppers + 1;
    lefts = ws(ws < windows(1, size(windows, 2)));
    rights = lefts + wh;
    is = [lowers uppers lefts rights];
    js = [uppers lowers rights lefts];
    ss = ones(1, length(is));
    pairwise = sparse(is, js, ss, N, N);
    
    % и для меток
    labelcost = single(ones(C) - eye(C));

    doer = buildDoer(start, unary, pairwise, labelcost, N);
end

function doer = buildDoer(start, unary, pairwise, labelcost, N)
    doer = @(coefficient) predictWithCRFStage2(start, unary, coefficient, pairwise, labelcost, N);
end

function blockwise = predictWithCRFStage2(start, unary, coefficient, pairwise, labelcost, N)
    [labelByBlock, ~, ~] = GCMex(start, unary, coefficient * pairwise, labelcost, 1);
    blockwise = reshape(labelByBlock + 1, N, 1);
    blockwise(blockwise == 3) = 4;
end

function blockwise = predictWithCRF(bw, name, predictor, coefficient, outFile)
    [doer, windows, N] = predictWithCRFStage1(bw, name, predictor);
    blockwise = doer(coefficient);

    if true
        votes = zeros(N, 6);
        votes((1 : N)' + (blockwise - 1) * N) = 1;
        fname = [outFile  '.blockwise_prediction_with_crf_' num2str(coefficient) '.png'];
        imwrite(vizualiseBlockwiseSegmentation(bw, windows, blockwise, votes), fname, 'png');
        copyfile(fname, [outFile  '.blockwise_prediction_with_crf.png']);
    end
end

function learned = makeBlockwiseFromPixelwise(blockSize, pixelwise, db, outDir)
    [features, classes] = ...
        arrayfun( ...
        @(i) ...
            learnFromImage( ...
                blockSize, ...
                pixelwise, ...
                db.sub(i), ...
                outDir), (1 : db.size())', ...
            'UniformOutput', false);
    
    features = cell2mat(features);
    classes = cell2mat(classes);
    
    classes(classes == 7 & rand(length(classes), 1) < 0.7) = 4; % 70%
    classes(classes == 7 & rand(length(classes), 1) < 1 / 2) = 1; % 15%
    classes(classes == 7) = 2; % 15%
    
    assert(isempty(find(~(unique(classes) == [1 2 4]'), 1)));
    
    nTree = 50;
    m = 2;%floor(sqrt(size(features, 2)));
    extra_options.do_trace = 1;
    extra_options.DEBUG_ON = true;
    learned.forest = classRF_train(features, classes, nTree, m, extra_options);
    learned.predict = buildBlockwisePredictor(pixelwise.predict, learned.forest, blockSize, outDir);
end

function predictor = buildBlockwisePredictor(pixelwise, forest, blockSize, outDir)
    predictor = @(bw, name) local_classify(bw, name, pixelwise, forest, blockSize, [outDir name]);
end

function [blockwise, votes, windows] = local_classify(bw, name, pixelwise, forest, blockSize, outFile)
    [pixelwise, textConfidence] = pixelwise(bw, name);
    windows = window_id(size(bw, 1), size(bw, 2), blockSize);
    features = getFeatures(pixelwise, textConfidence, bw, windows);
    [blockwise, votes] = classRF_predict(features, forest);    
    
    % force response for empty blocks
    isempty = isEmptyBlock(features);
    blockwise(isempty) = 4;
    votes(isempty, :) = repmat([0.15, 0.15, 0.7], [length(find(isempty)) 1]);
    
    if ~strncmp(outFile, 'no', 2)
        cl = zeros(size(votes, 1), 1);
        [viz, probabilistic] = vizualiseBlockwiseSegmentation(bw, windows, blockwise, [votes(:, 1 : 2), cl, votes(:, 3), cl, cl, cl]);
        imwrite(viz, [outFile '.blockwise_prediction.png'], 'png');
        imwrite(probabilistic, [outFile '.blockwise_probabilistic_prediction.png'], 'png');
    end
end

function isempty = isEmptyBlock(features)
    isempty = features(:, 1) == 1;
end

function [features, classes] = learnFromImage(blockSize, pixelwise, db, outDir)
    assert(db.size() == 1);
    bw = db.bw(1);
    name = db.name(1);
    
    [groundTruth, windows] = makeBlockwiseGroundTruthFromPixelwise(blockSize, db.groundTruth(1), bw, db.original(1), [outDir name]);
    [pixelwise, textConfidence] = pixelwise.predict(bw, name);
    
    classes = groundTruth;
    
    assert(isempty(find(~(classes == 1 | classes == 2 | classes == 4 | classes == 6 | classes == 7), 1)));
    
    features = getFeatures(pixelwise, textConfidence, bw, windows);
    features = features(classes ~= 6, :);
    classes = classes(classes ~= 6);
end

function features = getFeatures(pixelwise, textConfidence, bw, windows)
    pxClasses = zeros(size(bw, 1), size(bw, 2));
    
    pxClasses(pixelwise == 5) = 2;
    pxClasses(pixelwise == 9) = 3;
    pxClasses(pixelwise == 1) = -1;
    pxClasses(pixelwise == 2) = -1;
    pxClasses(bw) = 1;
    pxClasses = pxClasses(:);
    textConfidence = textConfidence(:);
    windows = windows(:);
    
    assert(isempty(find(pxClasses == 0, 1)));
    
    nClasses = 5;
    nWindows = max(windows);
    indices = windows + nWindows * (pxClasses - 1);
    counts = zeros(1, nWindows * nClasses);
    counts = vl_binsum(counts, ones(1, length(find(pxClasses ~= -1))), indices(pxClasses ~= -1));
    counts = vl_binsum(counts, textConfidence(pxClasses == -1), windows(pxClasses == -1) + nWindows * (4 - 1));
    counts = vl_binsum(counts, 1 - textConfidence(pxClasses == -1), windows(pxClasses == -1) + nWindows * (5 - 1));
    counts = reshape(counts, nWindows, nClasses);
    features = counts;
    features(:, 1) = features(:, 1) ./ sum(features, 2);
    blacks = sum(features(:, 2 : 5), 2);
    features(:, 2 : 5) = features(:, 2 : 5) ./ repmat(blacks, [1 4]);
    features(isnan(features)) = 0;
end
