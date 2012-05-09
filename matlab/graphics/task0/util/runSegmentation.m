function runSegmentation(VOC, MSRC, options, db)

    RandStream.setDefaultStream(RandStream('mt19937ar'));
    db = loadDB(VOC, MSRC, db);

    if ~strcmp(options.crfType, 'none') && ~strcmp(options.crfParameterType, 'fixed')
        RandStream.setDefaultStream(RandStream('mt19937ar'));
        db = splitDB(db);
    end
    
    if options.featuresSIFT
        % построение словаря
        RandStream.setDefaultStream(RandStream('mt19937ar'));
        [dictionary, tag] = buildDictionary(db, options);
    else
        dictionary = 0;
        tag = db.tag;
    end

    % обучение
    RandStream.setDefaultStream(RandStream('mt19937ar'));
    [learned, tag] = learn(dictionary, tag, db, options);

    % тестирование
    RandStream.setDefaultStream(RandStream('mt19937ar'));
    runTest(learned, tag, db, options);
end
