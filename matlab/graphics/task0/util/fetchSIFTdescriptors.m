function [features, descriptors, tag] = fetchSIFTdescriptors(original, options)

    binSize = options.sift.binSize;
    magnif = 3;
    step = 1;
    
    gray = double(rgb2gray(original));
    % нормализация
    gray = gray - min(gray(:));
    gray = gray / max(gray(:));
    
    % vl_imsmooth expects doubles
    gray = vl_imsmooth(gray, sqrt((binSize / magnif) ^ 2 - 0.25));

    gray = single(gray);
    
    % vl_dsift expects singles
    [features, descriptors] = caching_vl_dsift(gray, binSize, step, options.cachingPolicy);
    features(3, :) = binSize / magnif;
    features(4, :) = 0;

    tag = sprintf('dsift_binSize%d', int32(binSize));
    if step ~= 1
        tag = sprintf('%s_step%d', tag, int32(step));
    end
    if magnif ~= 3
        tag = sprintf('%s_magnif%d', tag, int32(magnif));
    end
    
    features = single(features);
end
