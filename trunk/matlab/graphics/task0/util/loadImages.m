function images = loadImages(ids, loader, options)
    % loadImages Загрузить изображения
    
    fprintf(1, 'Loading %d images: ', length(ids));
    images = cellfun(@(id) loadImage(id, loader, options), ids);
    fprintf(1, ' done.\n');
end

function image = loadImage(id, loader, options)

    image.id = id;
    image.original = @() loader(id);
    image.labels = @(orig) fetchSuperPixels(orig, options);
        
    fprintf(1, '.');
end
