function [learned, tag] = learn(dictionary, dictionaryTag, db, options)

    % возвращает структуру с следующими полями:
    % learn - то, что понадобится в дальнейшем для сегментации
    
    this.learn.dictionary = dictionary;    
    
    if options.featuresSIFT
        % todo: есть же vl_ikmeans_push, зачем индекс?
        dictionaryIndex = makeDictionaryIndex(dictionary, options);
    else
        dictionaryIndex = [];
    end
    this.learn.dictionaryIndex = dictionaryIndex;
    
    images = loadImages(db.train, db.loadOriginal, options);
    
    [features, classes, tag] = learnFromImages(images, dictionary, dictionaryIndex, db, options);
    
    clear images;
    clear dictionary;
    clear dictionaryIndex;
    
    % сортировка нужна, чтобы передать веса меток в classRF_train
    labels = sort(unique(double(classes)));
    
    % выбрать из каждой категории подмножество для обучения
    chosen = [];
    for i = 1 : length(labels)
        label = labels(i);       
        possible = find(classes == label);
        n = min(length(possible), options.precedentsPerCategory);
        perm = randperm(length(possible));
        perm = perm(1 : n)';
        chosen = [chosen; possible(perm)]; %#ok<AGROW>
    end
    clear perm;
    clear possible;
    
    if options.precedentsPerCategory ~= Inf
        tag = sprintf('%s_precPerClassLimit%d', tag, int32(options.precedentsPerCategory));
    end
    
    classes = classes(chosen);
    features = features(chosen, :);
    clear chosen;
    
    counts = int32(arrayfun(@(label) length(find(classes == label)), labels));
    clear labels;
    
    treeCount = options.classifierTreeCount;
    tag = sprintf('%s_nTrees%d', tag, int32(options.classifierTreeCount));
    mTree = options.mTree;
    if mTree == 0
        mTree = floor(sqrt(size(features, 2)));
    else
        tag = sprintf('%s_mTree%d', tag, int32(mTree));
    end
    
    use_weights = options.learnClassifierWeighted;
    if use_weights
        extra_options.classwt = 1.0 ./ double(counts);
    else
        extra_options.classwt = ones(size(counts, 1), 1);
        tag = sprintf('%s_nowt', tag);
    end
    clear counts;
    extra_options.do_trace = 1;
    extra_options.DEBUG_ON = true;
    
    features = double(features);
    classes = double(classes);
    
    fprintf(1, 'Building classifier (classRF_train, trees: %d, mTree: %d, data size: %d): ', treeCount, mTree, length(classes));
    forest = caching_classRF_train(features, classes, treeCount, mTree, extra_options, options.cachingPolicy);
    this.learn.forest = forest;
    fprintf(1, 'done.\n');
    
    if ~strcmp(options.crfType, 'none')
        tag = sprintf('%s_CRF%s', tag, options.crfType);
    
        if strcmp(options.crfType, 'simple')
            if strcmp(options.crfParameterType, 'fixed')
                tag = sprintf('%s_fixed%g', tag, options.crfParameterValue);
            elseif strcmp(options.crfParameterType, 'fakegridsearch')
                tag = sprintf('%s_fakegridsearch', tag);
            elseif strcmp(options.crfParameterType, 'gridsearch')
                tag = sprintf('%s_gridsearch', tag);
                this.learn.crfParameterValue = doCRFGridSearch(this.learn, db, options);
            else
                error('Unsupported simple CRF parameter type');
            end
        elseif strcmp(options.crfType, 'extended')
            if strcmp(options.crfParameterType, 'fixed')
                tag = sprintf('%s_fixed%g', tag, options.crfParameterValue);
            elseif strcmp(options.crfParameterType, 'gridsearch')
                tag = sprintf('%s_gridsearch', tag);
                this.learn.crfParameterValue = doCRFGridSearch(this.learn, db, options);
            else
                error('Unsupported extended CRF parameter type');
            end
        else
            error('Unsupported CRF type');
        end
    end

    learned = this.learn;
    if options.featuresSIFT
        tag = sprintf('%s_%s', dictionaryTag, tag);
    else
        tag = sprintf('%s_%s', db.tag, tag);
    end
end


function index = makeDictionaryIndex(dictionary, options)
    % построить структуру для быстрого поиска ближайших слов в словаре

    fprintf(1, 'Building dictionary index (KD-tree): ');
    
    numTrees = 1;
    index = caching_vl_kdtreebuild(dictionary, numTrees, options.cachingPolicy);
    
    fprintf(1, 'done.\n');
end


function [features, classes, tag] = learnFromImages(images, dictionary, index, db, options)

    % для каждого суперпикселя построить гистограмму частот слов
    % построить соответствие "гистограмма -> класс"
    
    fprintf(1, 'Extracting features: ');
    
    [features, classes, tags] = arrayfun(@(image) learnFromImage(image, dictionary, index, db, options), images, 'UniformOutput', false);
    features = cell2mat(features);
    classes = cell2mat(classes);
    tag = tags{1};
    
    fprintf(1, ' done.\n');
end


function forest = caching_classRF_train(X, Y, treeCount, mTree, extra_options, cachingPolicy)

    if ~isa(X, 'double') || ~isa(Y, 'double')
        error('X and Y should be of DOUBLE class.');
    end

    if cachingPolicy.use
        functionName = 'classRF_train';
        args.X = X;
        args.Y = Y;
        args.treeCount = treeCount;
        args.mTree = mTree;
        args.extra_options = extra_options;
        
        key = [mat2str(X' * (Y + 1)) '; ' mat2str([treeCount mTree]) '; ' mat2str(sum(extra_options.classwt))];
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            forest = cached{1};
            return;
        end
    end
    
    forest = classRF_train(X, Y, treeCount, mTree, extra_options);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {forest}, cachingPolicy);
    end
end


function index = caching_vl_kdtreebuild(dictionary, numTrees, cachingPolicy)

    if ~isa(dictionary, 'single')
        error('dictionary must be single');
    end

    if cachingPolicy.use
        functionName = 'vl_kdtreebuild';
        args.dictionary = dictionary;
        args.numTrees = numTrees;

        key = [mat2str(sum(double(dictionary))) '; ' mat2str(numTrees)];
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            index = cached{1};
            return;
        end
    end
    
    index = vl_kdtreebuild(dictionary, 'NumTrees', numTrees);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {index}, cachingPolicy);
    end
end


function [features, classes, tag] = learnFromImage(image, dictionary, index, db, options)

    original = image.original();
    labels = image.labels(original);
    
    [features, good, tag] = extractFeatures(original, labels, dictionary, index, options);
    
    classes = readEtalonClasses(image, labels, db);
    good = good & (classes ~= 255);
    
    features = features(good, :);
    classes = classes(good);
    
    fprintf(1, '.');
end


function classes = readEtalonClasses(image, labels, db)
    
    % возвращает эталонный класс каждого суперпикселя заданного
    % изображения
    % для суперпикселей, которые не удалось отнести ни к одному классу -
    % возвращается 255
    
    labels = labels(:);
    N = max(labels);
    
    if min(labels) < 1
        error('Bad labels.');
    end
    
    % эталонное разложение пикселей на классы
    % тут мы получаем псевдоклассы из [1:length(db.classes) 255] 
    etalonClasses = int32(makeIndexes(db.loadSegmentation(image.id), db.classes));
    etalonClasses = etalonClasses(:);
    
    % отбрасываем класс void
    labels = labels(etalonClasses ~= 255);
    etalonClasses = etalonClasses(etalonClasses ~= 255);
    
    % ищем для каждого суперпикселя наиболее популярный класс
    classes_ = getMaxX(labels, etalonClasses);
    
    % суперпиксели, для которых не было ground truth - будут иметь метку
    % 255
    classes = 255 * ones(N, 1);
    classes(unique(labels)) = classes_(:);
    
    if min(classes(:)) < 1
        error('Something wrong');
    end
end
