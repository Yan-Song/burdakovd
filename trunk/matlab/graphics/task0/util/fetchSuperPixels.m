function labels = fetchSuperPixels(image, options)
    [~, labels] = caching_vl_quickseg(image, 0.5, 2, 8, options.cachingPolicy);
    labels = uint16(labels);
end

