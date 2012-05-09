function predictor = makeRandomForestPredictor(db, outDir)
    gFeatures = [];
    gComponents = emptyComponents();
    gGt_classes = [];
    
    for fileId = 1 : db.size()
        outFile = [outDir db.name(fileId)];
        fprintf(1, 'Learning on image %s\n', db.name(fileId));
        
        bw = db.bw(fileId);
        [~, cc, bw] = getConnectedComponents(bw, outFile);
        components = getComponents(cc);
        features = getFeatures(bw, cc, components, outFile);
        gt_classes = getClasses(bw, db.groundTruth(fileId), cc, outFile);
        
        gFeatures = [gFeatures; features]; %#ok<AGROW>
        gGt_classes = [gGt_classes; gt_classes']; %#ok<AGROW>
        gComponents = mergeComponents(gComponents, components);
    end
    
    predictor.learned = learnRF(gFeatures, gGt_classes == 1, gComponents.areas');
    predictor.predict = buildPredictor(predictor.learned, outDir);
end

function predictor = buildPredictor(learned, outDir)
    predictor = @(bw, name) local_classify(bw, learned, [outDir name]);
end

function [originalCc, cc, bw] = getConnectedComponents(bw, outFile)
    % enhance image
    cc = bwconncomp(~bw, 4);
    originalCc = cc;
    fprintf(1, 'Connected components in original image: %d, after filtering: ', cc.NumObjects);

    components = getComponents(cc);

    for id = find( ...
            components.areas < 5 | ...
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
    gt_red = gt(:, :, 1);
    gt_green = gt(:, :, 2);
    gt_blue = gt(:, :, 3);

    isText = gt_red > 0 & gt_green == 0 & gt_blue == 0;
    isPicture = gt_red == 0 & gt_green == 0 & gt_blue == 0;

    gt_classes = zeros(1, cc.NumObjects);
    gt_classes(cellfun(@(list) isText(list(1)), cc.PixelIdxList)) = 1;
    gt_classes(cellfun(@(list) isPicture(list(1)), cc.PixelIdxList)) = 2;

    ok = bw;
    ok(isText) = 1;
    ok(isPicture) = 1;

    if(~isempty(find(ok == 0, 1)))
        imwrite(ok, [outFile  '.bw_fail.png'], 'png');
        assert(false);
    end
    assert(isempty(find(gt_classes == 0, 1)));
end

function features = getFeatures(bw, cc, components, outFile)
    imwrite(bw, [outFile  '.bw.png'], 'png');

    labels = labelmatrix(cc);
    border_pixels = histc(labels(labels ~= 0 & bwperim(~bw)), 1 : max(labels(:)))';
    perims = makePerims(labels);
    features1 = perims .^ 2 ./ components.areas;
    features2 = border_pixels ./ components.areas;

    features = [features1; features2]';
end

function learned = learnRF(features, ground_truth, weights)
    classes = ones(length(ground_truth), 1);
    classes(~ground_truth) = 2;
    nTree = 50;
    m = floor(sqrt(size(features, 2)));
    extra_options.do_trace = 1;
    extra_options.DEBUG_ON = true;
    learned.forest = classRF_train(features, classes, nTree, m, extra_options);
end

function segmentated = local_classify(originalBw, learned, outFile)
    [originalCc, cc, bw] = getConnectedComponents(originalBw, outFile);
    originalComponents = getComponents(originalCc);
    features = getFeatures(bw, cc, getComponents(cc), outFile);

    [~, votes] = classRF_predict(features, learned.forest);
    
    prediction = votes(:, 1) ./ sum(votes, 2);

    % 5 == unknown
    segmentated = uint8(~originalBw) * 5;

    % mark large areas as images
    for id = find( ...
            originalComponents.heights > 512 | ...
            originalComponents.widths > 512)
        segmentated(originalCc.PixelIdxList{id}) = 2;
    end

    for i = 1 : cc.NumObjects
        segmentated(cc.PixelIdxList{i}) = 2 - (prediction(i) > 0.5);
    end
    
    if ~strncmp(outFile, 'no', 2)
        bgtextpicturecmap = [1 1 1; 1 0 0; 0 0 1; 1 0.9 0.9; 0.9 0.9 1; 0.7 0.7 0.7];
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
end
