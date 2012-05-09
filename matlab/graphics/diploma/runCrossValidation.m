function runCrossValidation(db, predictorFactory, validator, outDir)
    nRuns = 5;
    ratio = 0.75;
    
    n = db.size();
    assert(n >= 2);
    nTrain = round(ratio * n);
    if nTrain == n
        nTrain = n - 1;
    end
    nVal = n - nTrain;
    assert(nTrain > 0 && nVal > 0);
    
    fprintf(1, 'CV: will use %d images for train and %d for validation\n', nTrain, nVal);
    fprintf(1, 'CV: will make %d runs\n', nRuns);
    
    sum = 0;
    
    RandStream.setDefaultStream(RandStream('mt19937ar'));
    
    for runId = 1 : nRuns
        perm = randperm(n);
        trainIds = perm(1 : nTrain);
        valIds = perm(nTrain + 1 : end);
        
        predictor = predictorFactory(db.sub(trainIds), outDir);
        result = validator(db.sub(valIds), predictor);
        fprintf('CV: run #%d, %.2f%%\n', runId, result * 100);
        sum = sum + result;
    end
    
    fprintf('CV: average accuracy %.2f%%\n', sum / nRuns * 100);
end
