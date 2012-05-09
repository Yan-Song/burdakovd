function [bags, tag] = makeBagsOfFeaturesForImage(original, labels, dictionary, index, options)

    % список суперпикселей изображения
    superPixelCount = double(max(labels(:)));
    
    [features, descriptors, tagSIFT] = fetchSIFTdescriptors(original, options);
    clear original;
    
    % инициализировать гистограммы нулями
    dictionarySize = size(dictionary, 2);
    bags = zeros(superPixelCount, dictionarySize);
    
    rows = ceil(features(2, :));
    cols = ceil(features(1, :));
    
    labels = double(labels(rows + (cols - 1) * size(labels, 1)));
    
    % используется soft-weighting
    % для каждой фичи берём N ближайших слов и суммируем степень её
    % похожести на эти слова с убывающим весом
    % Суперпиксель, к которому относится фича определяется по её центру.
    % sim(j, k) == 1, в надежде, что множителя 2^(1-n) будет достаточно
    N = 4;
    sim = 1.0;
    nearests = caching_vl_kdtreequery(index, dictionary, single(descriptors), N, options.cachingPolicy);
    nearests = double(nearests);
    
    idx = repmat(labels, 4, 1) + (nearests - 1) * superPixelCount;
    addend = repmat(sim * (0.5 .^ (0 : (N-1))'), 1, length(labels));
    
    if ~isa(bags, 'double') || ~isa(addend, 'double') || ~isa(idx, 'double')
        error('Should be of DOUBLE class.');
    end
    bags(:) = vl_binsum(bags(:), addend(:), idx(:));
        
    bags = single(bags);
    tag = sprintf('%s_histSoft%d', tagSIFT, int32(N));
end


function [nearests, dists] = caching_vl_kdtreequery(forest, X, Y, numNeighbors, cachingPolicy)

    if ~isa(X, 'single') || ~isa(Y, 'single')
        error('X and Y should be of SINGLE class.');
    end
    
    if size(X, 3) ~= 1 || size(Y, 3) ~= 1 || size(X, 1) ~= size(Y, 1)
        error('Bad sizes of X and Y.');
    end

    if cachingPolicy.use
        functionName = 'vl_kdtreequery';
        args.forest = forest;
        args.X = X;
        args.Y = Y;
        args.numNeighbors = numNeighbors;
        
        key = [mat2str([sum(double([forest.trees.dataIndex])) ...
            double(forest.dimension) double(forest.numData)]) ...
            mat2str(sum(sum(double(X), 2) .* double(sum(Y, 2)))) ...
            mat2str(numNeighbors)];
        
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            nearests = cached{1};
            dists = cached{2};
            return;
        end
    end
    
    [nearests, dists] = vl_kdtreequery(forest, X, Y, 'NumNeighbors', numNeighbors);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {nearests, dists}, cachingPolicy);
    end
    
end
