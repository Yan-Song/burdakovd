function [features, descriptors] = caching_vl_dsift(image, binSize, step, cachingPolicy) 
    
    if ~isa(image, 'single') || size(image, 3) ~= 1
        error('Parameter "I" must be of class SINGLE and grayscale.');
    end

    if cachingPolicy.use
        functionName = 'vl_dsift';
        args.image = image;
        args.binSize = binSize;
        args.step = step;
        
        % сумма пикселей по изображению, конечно не является качественной
        % хэш-функцией, но шанс коллизии невелик, и работает быстро
        key = [mat2str(sum(sum(double(image)))) '; ' mat2str([binSize step])];
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            features = cached{1};
            descriptors = cached{2};
            return;
        end
    end
    
    [features, descriptors] = vl_dsift(image, 'size', binSize, 'step', step);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {features, descriptors}, cachingPolicy);
    end
end
