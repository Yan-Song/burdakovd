function buildReport(options, db, caseName, isGeneric, report)

    report('---------------------------------------------------\n\n');
    report('Report: %s\n\n', caseName);

    testselPath = sprintf('%s/%s/testsel.txt', options.resultsPath, caseName);
    if exist(testselPath, 'file')
        fid = fopen(testselPath);
        testsel = textscan(fid, '%s');
        testsel = testsel{1};
        fclose(fid);

        fid = fopen(sprintf('%s/%s/classes.txt', options.resultsPath, caseName));
        classes = fscanf(fid, '%d');
        fclose(fid);
        ncats = length(classes);

        resultsPath = sprintf('%s/%s/results/%%s.png', options.resultsPath, caseName);

        % confcounts(i, j) - количество пикселей,
        % настоящий класс которых i, а предсказанный - j
        confcounts = zeros(ncats);

        for localImageId = 1 : length(testsel)
            imageId = testsel{localImageId};
            %report('[buildReport] image %s (%d/%d)\n', imageId, localImageId, length(testsel));

            predicted = double(makeIndexes(imread(sprintf(resultsPath, imageId)), classes));
            if isGeneric
                etalon = double(makeIndexes(db.loadSegmentationForce(imageId, classes), classes));
            else
                etalon = double(makeIndexes(db.loadSegmentation(imageId), classes));
            end

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
        pixelAccuracy = 100 * sum(truePositives) / sum(totalPrecedents);
        classAccuracy = 100 * truePositives ./ totalPrecedents;
        unions = sum(confcounts, 2) + sum(confcounts, 1)' - truePositives;
        IUClassAccuracy = 100 * truePositives ./ unions;

        report('  Pixel accuracy: %4.0f\n\n', pixelAccuracy);

        titles = {'Class', 'Intersection/union class'};
        sources = {classAccuracy, IUClassAccuracy};

        for i = 1 : length(titles)
            report('  %s accuracy:\n', titles{i});

            report('    ');
            for c = 1 : ncats
                classId = classes(c);
                className = db.className(classId);
                className = className(1 : min(5, length(className)));
                for sp = 1 : (5 - length(className))
                    report(' ');
                end
                report(' %s', className);
            end

            report('   mean');
            report('\n');
            report('    ');
            report('|%4.0f ', sources{i});
            report('| %4.0f ', mean(sources{i}));
            report('\n\n');
        end

        report('\n');
    else
        report('Case %s is invalid, can''t read testsel.txt\n', caseName);
    end
end

