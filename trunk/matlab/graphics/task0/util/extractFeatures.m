function [features, good, tag] = extractFeatures(original, labels, dictionary, index, options)

    if(min(labels(:)) < 1)
        error('Bad labels.');
    end
    
    n = max(labels(:));
    
    features = [];
    good = true(n, 1);
    tag = '';

    if options.featuresSIFT
        dictionarySize = size(dictionary, 2);  
        [SIFTfeatures, SIFTtag] = makeBagsOfFeaturesForImage(original, labels, dictionary, index, options);
        
        % l1 нормы векторов признаков
        norms = sum(SIFTfeatures, 2);

        % некоторые суперпиксели могли не словить ни одной фичи, тогда норма
        % гистограммы нулевая
        % их нужно отбросить, как и имеющие класс void
        good = good & (norms > 0);

        % нормируем вектора
        SIFTfeatures = SIFTfeatures ./ norms(:, ones(1, dictionarySize));
        
        features = [features SIFTfeatures];
        
        if isempty(tag)
            tag = SIFTtag;
        else
            tag = sprintf('%s_%s', tag, SIFTtag);
        end
    end
    
    if options.featuresColor
        [r, g, b] = getSuperPixelColor(original, labels);
        
        features = [features single(repmat([r g b], 1, options.colorImportance))];
        ColorTag = sprintf('meancolorX%d', int32(options.colorImportance));
        if isempty(tag)
            tag = ColorTag;
        else
            tag = sprintf('%s_%s', tag, ColorTag);
        end
    end
end

