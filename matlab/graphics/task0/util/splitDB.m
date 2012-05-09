function db = splitDB(db)
    % splits db.train into db.train and db.validation
    % db.dict = db.train
    train = db.train;
    n = length(train);
    
    perm = randperm(n);
    
    nval = min(100, floor(n / 3));
    db.validation = train(perm(1 : nval));
    db.train = train(perm(nval + 1 : n));
    db.dict = db.train;
    
    fprintf(1, 'Splitting set of %d train images into %d for train and %d for validation.\n', n, n - nval, nval);
end
