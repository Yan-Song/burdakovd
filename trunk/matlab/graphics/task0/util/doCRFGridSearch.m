function parameter = doCRFGridSearch(learned, db, options)
    fprintf(1, 'Preparation for gridsearch.\n');
    images = loadImages(db.validation, db.loadOriginal, options);
    
    fprintf(1, 'Precalc for validation images: ');
    for i = 1 : length(images)
        original = images(i).original();
        images(i).groundTruth = db.loadSegmentation(images(i).id);
        labels = images(i).labels(original);
        [features, good] = extractFeatures(original, labels, ...
            learned.dictionary, ...
            learned.dictionaryIndex, options);
        [Y_hat, votes] = ...
            classRF_predict(double(features(good, :)), ...
            learned.forest);
        boundaries = sparse(boundaryLength(labels));
        images(i).predictor = predictClasses(good, Y_hat, votes, ...
            original, labels, db.classes, options, boundaries);
        fprintf(1, '.');
    end
    fprintf(1, ' done.\n');
    
    l = -16; r = 8;
    while r - l > 0.01
        w = 16;
        fprintf(1, '\nSearching in range [%g; %g]\n', exp(l), exp(r));
        values = l + (0 : w) * (r - l) / w;
        results = zeros(1, length(values));
        
        for i = 1 : length(values)
            results(i) = evaluateParameter(learned, exp(values(i)), db.classes, images);
        end
        
        [~, i] = max(results);
        bounds = values(i) + 2 * [-1 1] * (r - l) / w;
        l = bounds(1);
        r = bounds(2);
    end
    
    parameter = exp((l + r) / 2);
    fprintf(1, '\nHave chosen %g as CRF parameter.\n\n', parameter);
end

function mark = evaluateParameter(learned, value, classes, images)
    fprintf(1, 'Results for %g: ', value);

    ncats = length(classes);
    
    % confcounts(i, j) - количество пикселей,
    % настоящий класс которых i, а предсказанный - j
    confcounts = zeros(ncats);

    for i = 1 : length(images)
        image = images(i);

        learned.crfParameterValue = value;
        predicted = double(makeIndexes(...
            image.predictor.do(image.predictor, learned), classes));
        
        etalon = double(makeIndexes(image.groundTruth, classes));

        % какие пиксели нас интересуют
        locs = find(etalon < 255);

        % какой позиции в одномерной развертке confcounts
        % соответствует каджый пиксель изображения
        cells = etalon + (predicted - 1) * ncats;

        % добавляем к нужным ячейкам confcounts
        % единицы
        confcounts(:) = vl_binsum(confcounts(:), ones(size(locs)), cells(locs));
    end
    
    totalPrecedents = sum(confcounts, 2);
    truePositives = diag(confcounts);
    classAccuracy = 100 * truePositives ./ totalPrecedents;
    mark = mean(classAccuracy(~isnan(classAccuracy)));
    
    fprintf(1, 'by class: %s%%, mean: %.1f%%\n', vect2str(int32(classAccuracy), 'formatstring', '%d'), mark);
end
