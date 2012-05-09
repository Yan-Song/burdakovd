function [dictionary, tag] = buildDictionary(db, options)
    
    % db.dict - вертикальный вектор
    fprintf(1, 'Reading images: ');
    sizes = cellfun(@(id) numCandidates(id, db, options), db.dict, 'UniformOutput', false);
    sizes = cell2mat(sizes);
    total = sum(sizes, 1);
    fprintf(1, 'done, total positions for SIFT by classes: %s.\n', vect2str(total, 'formatstring', '%d'));
    
    chances = min(options.descriptorsForDictionary / length(total) ./ total, 1);
    fprintf(1, 'Will choose randomly %s%% of descriptors (approx. %s points) to build dictionary.\n', ...
        vect2str(chances * 100, 'formatstring', '%.2f'), ...
        vect2str(int32(total .* chances), 'formatstring', '%d'));

    [dictionary, tag] = makeDictionary(db, chances, options);
    tag = sprintf('%s_dictF%d_balanced_%s', db.tag, int32(options.descriptorsForDictionary), tag);
end


function candidates = numCandidates(id, db, options)
    % количество позиций, где можно взять SIFT
    % возвращает в горизонтальном векторе количество позиций по каждому
    % классу
    % вектор соответствует вектору db.classes и имеет ту же размерность
    
    % читаем сегментацию
    segmentation = makeIndexes(db.loadSegmentation(id), db.classes);
    
    % получаем все возможные точки выбора фреймов
    frames = possibleFrames(segmentation, ones(1, length(db.classes)), options.sift.binSize);
    
    candidates = countPointsByClass(segmentation, frames, db);
end


function candidates = countPointsByClass(segmentation, frames, db)
    n = size(frames, 2);

    % одномерная развертка координат
    positions = int32(frames(1, :) - 1) * size(segmentation, 1) + int32(frames(2, :));
    
    % смотрим классы в выбранных точках
    labels = segmentation(positions);
    
    % считаем количество найденных точек по классам
    candidates = vl_binsum(zeros(1, length(db.classes)), ones(1, n), labels);
end


function [dictionary, tag] = makeDictionary(db, chance, options)
    % кластеризовать дескрипторы SIFT
    
    fprintf(1, 'Loading descriptors: ');
    [data, byClass] = cellfun(@(id) getDescriptors(id, db, chance, options), db.dict', 'UniformOutput', false);
    data = cell2mat(data);
    byClass = cell2mat(byClass');
    byClass = sum(byClass, 1);
    n = size(data, 2);
    fprintf(1, ' done, %d descriptors loaded.\n', n);
    
    fprintf(1, 'Descriptors loaded by class: %s.\n', vect2str(byClass, 'formatstring', '%d'));
    
    dictionarySize = options.dictionarySize;
    fprintf(1, 'Building dictionary (ikmeans, %d points, K = %d): ', n, dictionarySize);
    
    dictionary = caching_vl_ikmeans(data, min(dictionarySize, n), 'elkan', options.cachingPolicy);
    dictionary = single(dictionary);
    tag = sprintf('dictK%d', int32(dictionarySize));
    
    fprintf(1, ' done.\n');
end


function [descriptors, byClass] = getDescriptors(id, db, chance, options)
    % вторым параметром возвращает строку - количество дескрипторов по классам

    gray = rgb2gray(db.loadOriginal(id));
    segmentation = makeIndexes(db.loadSegmentation(id), db.classes);
    frames = possibleFrames(segmentation, chance, options.sift.binSize);

    if isempty(frames)
        descriptors = [];
        byClass = zeros(1, length(db.classes));
    else
        % нормализация
        gray = gray - min(gray(:));
        gray = gray / max(gray(:));

        gray = single(gray);
        % vl_sift expects singles
        [~, descriptors] = caching_vl_sift(gray, frames, options.cachingPolicy);
        
        byClass = countPointsByClass(segmentation, frames, db);
    end
    
    fprintf(1, '.');
end


function dictionary = caching_vl_ikmeans(data, K, method, cachingPolicy)
    
    if ~isa(data, 'uint8')
        error('data must be uint8.');
    end

    if cachingPolicy.use
        functionName = 'vl_ikmeans';
        args.data = data;
        args.K = K;
        args.method = method;
        % сумма дескрипторов, конечно, не является качественной
        % хэш-функцией, но шанс коллизии невелик, и работает быстро
        key = [mat2str(sum(data, 2)) '; ' mat2str(K) '; ' method];
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            dictionary = cached{1};
            return;
        end
    end
    
    dictionary = vl_ikmeans(data, K, 'method', method);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {dictionary}, cachingPolicy);
    end
end
