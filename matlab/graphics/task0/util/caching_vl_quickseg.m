function [viewable, labels] = caching_vl_quickseg(image, ratio, kernelSize, maxDist, cachingPolicy)

    if ~isa(image, 'uint8')
        error('image must be uint8');
    end

    if cachingPolicy.use
        functionName = 'vl_quickseg';
        args.image = image;
        args.ratio = ratio;
        args.kernelSize = kernelSize;
        args.maxDist = maxDist;
        % сумма пикселей по изображению, конечно не является качественной
        % хэш-функцией, но шанс коллизии невелик, и работает быстро
        key = [mat2str(sum(sum(double(image)))) '; ' mat2str([ratio kernelSize maxDist])];
        cached = cacheGet(functionName, args, key, cachingPolicy);
        if ~isempty(cached)
            viewable = cached{1};
            labels = cached{2};
            return;
        end
    end
    
    [viewable, labels] = vl_quickseg(image, ratio, kernelSize, maxDist);
    
    if cachingPolicy.use
        cachePut(functionName, args, key, {viewable, labels}, cachingPolicy);
    end
end
