function predictor = makeLinearRegressionPredictor(db, outDir)
    gFeatures = [];
    gComponents = emptyComponents();
    gGt_classes = [];
    
    for fileId = 1 : db.size()
        outFile = [outDir db.name(fileId)];
        fprintf(1, 'Learning on image %s\n', db.name(fileId));
        
        bw = db.bw(fileId);
        [~, ~, cc, bw] = getConnectedComponents(bw, outFile);
        components = getComponents(cc);
        features = getFeatures(bw, cc, components, outFile);
        gt_classes = getClasses(bw, db.groundTruth(fileId), cc, outFile);
        
        gFeatures = [gFeatures; features]; %#ok<AGROW>
        gGt_classes = [gGt_classes; gt_classes']; %#ok<AGROW>
        gComponents = mergeComponents(gComponents, components);
    end
    
    areas = gComponents.areas';

    isGoodCase = gGt_classes ~= 4;
    nBadCases = length(find(~isGoodCase));
    
    if(nBadCases > 0)
        percentage = nBadCases * 100 / length(gGt_classes);
        fprintf(1, 'Have got some background components: %.2f%% (%d of %d)\n', percentage, nBadCases, length(gGt_classes));
        assert(percentage < 10);
        gGt_classes = gGt_classes(isGoodCase);
        gFeatures = gFeatures(isGoodCase, :);
        areas = areas(isGoodCase);
    end
    
    isGoodCase = gGt_classes ~= 3;
    nBadCases = length(find(~isGoodCase));
    
    if(nBadCases > 0)
        percentage = nBadCases * 100 / length(gGt_classes);
        fprintf(1, 'Have got some text-and-picture-at-the-same-time components: %.2f%% (%d of %d)\n', percentage, nBadCases, length(gGt_classes));
        assert(percentage < 5);
        gGt_classes = gGt_classes(isGoodCase);
        gFeatures = gFeatures(isGoodCase, :);
        areas = areas(isGoodCase);
    end
    
    assert(isempty(find(gGt_classes ~= 1 & gGt_classes ~= 2, 1)));
    
    predictor.learned = learnRegression(gFeatures, gGt_classes == 1, areas);
    predictor.predict = buildPredictor(predictor.learned, outDir);
end

function predictor = buildPredictor(learned, outDir)
    predictor = @(bw, name) local_classify(bw, learned, [outDir name]);
end

function [originalCc, originalComponents, cc, bw] = getConnectedComponents(bw, outFile)
    % enhance image
    cc = bwconncomp(~bw, 4);
    originalCc = cc;
    fprintf(1, 'Connected components in original image: %d, after filtering: ', cc.NumObjects);

    components = getComponents(cc);
    originalComponents = components;

    for id = find( ...
            components.areas < 32 | ...
            components.heights > 512 | ...
            components.widths > 512)
        bw(cc.PixelIdxList{id}) = true;
    end

    if ~strncmp(outFile, 'no', 2)
        imwrite(bw, [outFile  '.bw.filtered.png'], 'png');
    end

    cc = bwconncomp(~bw, 4);
    fprintf(1, '%d.\n', cc.NumObjects);
end

function gt_classes = getClasses(bw, gt, cc, outFile)

    isText = gt == 1;
    isPicture = gt == 2;
    isBoth = gt == 3;
    isNone = gt == 4;

    gt_classes = gt(cellfun(@(list) list(1), cc.PixelIdxList));
    assert(size(gt_classes, 1) == 1);
    assert(size(gt_classes, 2) == length(gt_classes));
    
    ok = bw;
    ok(isText) = 1;
    ok(isPicture) = 1;
    ok(isBoth) = 1;
    ok(isNone) = 1;

    if(~isempty(find(ok == 0, 1)))
        imwrite(ok, [outFile  '.bw_fail.png'], 'png');
        assert(false);
    end
    assert(isempty(find(gt_classes ~= 1 & gt_classes ~= 2 & gt_classes ~= 3 & gt_classes ~= 4, 1)));
end

function features = getFeatures(bw, cc, components, outFile)
    if ~strncmp(outFile, 'no', 2)
        imwrite(bw, [outFile  '.bw.png'], 'png');
    end

    labels = labelmatrix(cc);
    border_pixels = histc(labels(labels ~= 0 & bwperim(~bw)), 1 : max(labels(:)))';
    perims = makePerims(labels);
    features1 = perims .^ 2 ./ components.areas;
    features2 = border_pixels ./ components.areas;

    features = [features1; features2]';
end

function [segmentated, textConfidence] = local_classify(originalBw, learned, outFile)
    [originalCc, originalComponents, cc, bw] = getConnectedComponents(originalBw, outFile);
    features = getFeatures(bw, cc, getComponents(cc), outFile);

    prediction = rpredict(learned, features);

    % 5 == unknown
    segmentated = uint8(~originalBw) * 5;

    % mark large areas as images
    for id = find( ...
            originalComponents.heights > 512 | ...
            originalComponents.widths > 512)
        segmentated(originalCc.PixelIdxList{id}) = 9;
    end

    for i = 1 : cc.NumObjects
        segmentated(cc.PixelIdxList{i}) = 2 - (prediction(i) > 0.5);
    end
    
    
    if ~strncmp(outFile, 'no', 2)
        bgtextpicturecmap = [1 1 1; 1 0 0; 0 0 1; 1 0.9 0.9; 0.9 0.9 1; 0.7 0.7 0.7; 0 0 0; 0 0 0; 0 0 0; 0 0 1];
        % todo: update color map for "9"
        imwrite(segmentated, bgtextpicturecmap, [outFile '.segmentated.png']);

        smooth_s = ones(size(bw, 1), size(bw, 2), 3);
        smooth_s(:, :, 1) = 1 - 0.5 * double(~originalBw);
        for id = find( ...
                originalComponents.heights > 512 | ...
                originalComponents.widths > 512)
            smooth_s(originalCc.PixelIdxList{id}) = 0;
        end

        for i = 1 : cc.NumObjects
            smooth_s(cc.PixelIdxList{i}) = prediction(i);
        end
        smooth_s(:, :, 3) =  1 - double(~originalBw) .* smooth_s(:, :, 1);
        smooth_s(:, :, 2) = min(smooth_s(:, :, 1), smooth_s(:, :, 3));
        imwrite(smooth_s, [outFile '.segmentated_probabilistic.png']);
    end
    
    textConfidence = NaN(size(originalBw, 1), size(originalBw, 2)); 
    for i = 1 : cc.NumObjects
        textConfidence(cc.PixelIdxList{i}) = prediction(i);
    end
end
