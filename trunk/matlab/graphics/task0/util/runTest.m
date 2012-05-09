function runTest(learned, tag, db, options)
    
    tag = ['my@' tag];

    fprintf(1, 'Test begins: %s\n', tag);
    
    colormap = db.colorMap();

    outdir = [options.resultsPath '/' tag '/'];
    resultDir = [outdir 'results/'];
    reportDir = [outdir 'reports/'];
    testselFileName = [outdir 'testsel.txt'];
    classesFileName = [outdir 'classes.txt'];
    dbFileName = [outdir 'db_tag.txt'];
    testselFileNameTmp = [testselFileName '.tmp'];
    if ~exist(resultDir, 'dir')
        mkdir(resultDir);
    end
    if ~exist(reportDir, 'dir')
        mkdir(reportDir);
    end
    if exist(testselFileName, 'file')
        delete(testselFileName);
    end
    resultPath = [resultDir '/%s.png'];
    reportPath = [reportDir '/%s.png'];
    
    cfid = fopen(classesFileName, 'w');
    for classId = db.classes
        fprintf(cfid, '%d\n', classId);
    end
    fclose(cfid);
    
    dfid = fopen(dbFileName, 'w');
    fprintf(dfid, '%s\n', db.tag);
    fclose(dfid);
    
    images = loadImages(db.test, db.loadOriginal, options);
    
    idsfid = fopen(testselFileNameTmp, 'w');
    
    fprintf(1, 'Predicting on %d images: ', int32(length(images)));
    for i = 1 : length(images)
        original = images(i).original();
        labels = images(i).labels(original);
        
        [features, good, ~] = extractFeatures(original, labels, learned.dictionary, learned.dictionaryIndex, options);
        [Y_hat, votes] = classRF_predict(double(features(good, :)), learned.forest);
        predicted = predictClasses(good, Y_hat, votes, original, labels, db.classes, options, sparse(boundaryLength(labels)));
        predicted = predicted.do(predicted, learned);
        imwrite(predicted, colormap, sprintf(resultPath, images(i).id));
        
        etalon = db.loadSegmentation(images(i).id);
        target = mode(double(etalon(etalon ~= db.backgroundClass & etalon ~= 255)));
        
        original = im2uint8(original);
        etalon = im2uint8(ind2rgb(etalon, colormap));
        predicted = im2uint8(ind2rgb(predicted, colormap));
        label = find(target == db.classes);

        if isnan(target) || isempty(label)
            chances = im2uint8(ind2rgb(0, colormap));
        else
            chances = votes(:, label == learned.forest.orig_labels) ./ sum(votes, 2);
            chancesBySuperPixel(good) = chances; %#ok<AGROW>
            chancesBySuperPixel(~good) = mean(chances); %#ok<AGROW>
            chance = chancesBySuperPixel(labels);
            chances = im2uint8(ind2rgb(uint8(floor(addLegend(chance) * 10.99)), redbluecmap(11)));
        end
        
        h = max([size(original, 1), size(etalon, 1), size(predicted, 1), size(chances, 1)]) + 10;
        w = max([size(original, 2), size(etalon, 2), size(predicted, 2), size(chances, 2)]) + 10;
        report = [addBorder(original, h, w) addBorder(etalon, h, w); addBorder(predicted, h, w) addBorder(chances, h, w)];
        imwrite(report, sprintf(reportPath, images(i).id));
        
        fprintf(idsfid, '%s\n', images(i).id);
        fprintf(1, '.');
    end
    fprintf(1, ' done\n');
    
    fclose(idsfid);
    movefile(testselFileNameTmp, testselFileName);
    
    buildReport(options, db, tag, false, @(varargin) fprintf(1, varargin{:}));
end
