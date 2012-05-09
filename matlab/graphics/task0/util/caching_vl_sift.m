function [features, descriptors] = caching_vl_sift(image, frames, cachingPolicy) 

    if ~isa(image, 'single') || size(image, 3) ~= 1
        error('Parameter "I" should be a gray-scale image in single precision');
    end
    
    if cachingPolicy.use
        functionName = 'vl_sift';
        args.image = image;
        args.frames = frames;
        % сумма пикселей по изображению, конечно не является качественной
        % хэш-функцией, но шанс коллизии невелик, и работает быстро
        key = mat2str([sum(sum(double(image))) sum(frames, 2)']);
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            features = cached{1};
            descriptors = cached{2};
            return;
        end
    end
    
    [features, descriptors] = vl_sift(image, 'Frames', frames);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {features, descriptors}, cachingPolicy);
    end
end
