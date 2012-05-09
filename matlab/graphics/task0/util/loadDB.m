function db = loadDB(VOC, MSRC, tag)
    fprintf(1, 'Loading database %s\n', tag);
    if regexp(tag, '^p07')
        db = loadVOCdb(VOC, tag);
    elseif regexp(tag, '^msrcocidv2')
        db = loadMSRCOCIDv2(MSRC, tag);
    else
        error('Unknown db tag: %s', tag);
    end
end


function db = loadMSRCOCIDv2(MSRC, tag)
    classesPath = [MSRC.groundTruth '/%s_s_GT.bmp'];
    originalsPath = [MSRC.originals '/%s_s.bmp'];
    
    db.tag = tag;
    
    if strcmp(tag, 'msrcocidv2grasscowsheep')
        ids = arrayfun(@(i, j) sprintf('%d_%d', i, j), repmat([1 5 9]', 1, 30), repmat(1:30, 3, 1), 'UniformOutput', false)';
        ids = ids(:);
        n = length(ids);
        perm = randperm(n);
        db.train = ids(perm(1 : int32(n / 2)));
        db.dict = db.train;
        db.test = ids(perm(int32(n / 2) + 1 : n));
        fprintf(1, 'Splitting set of %d images into %d for train and %d for test.\n', n, length(db.train), length(db.test));
        
        db.classes = [3 5 7];        
        incomingColorMap = [0 128 0; 0 0 128; 0 128 128]';
        
        db.loadOriginal = @(id) imread(sprintf(originalsPath, id));
        db.loadSegmentation = @(id) loadMSRCSegmentation(sprintf(classesPath, id), db.classes, incomingColorMap);

        db.backgroundClass = 3;

        % получает на вход какое-либо из значений db.classes
        db.className = @(id) MSRCshowName(id);
        db.colorMap = @() MSRCcolormap();
    elseif strcmp(tag, 'msrcocidv2grasscow')
        ids = arrayfun(@(i, j) sprintf('%d_%d', i, j), repmat([1 5]', 1, 30), repmat(1:30, 2, 1), 'UniformOutput', false)';
        ids = ids(:);
        n = length(ids);
        perm = randperm(n);
        db.train = ids(perm(1 : int32(n / 2)));
        db.dict = db.train;
        db.test = ids(perm(int32(n / 2) + 1 : n));
        fprintf(1, 'Splitting set of %d images into %d for train and %d for test.\n', n, length(db.train), length(db.test));
        
        db.classes = [3 5];
        incomingColorMap = [0 128 0; 0 0 128]';
        
        db.loadOriginal = @(id) imread(sprintf(originalsPath, id));
        db.loadSegmentation = @(id) loadMSRCSegmentation(sprintf(classesPath, id), db.classes, incomingColorMap);

        db.backgroundClass = 3;

        % получает на вход какое-либо из значений db.classes
        db.className = @(id) MSRCshowName(id);
        db.colorMap = @() MSRCcolormap();
    else
        error('Unknown db tag: %s', tag);
    end
end


function map = MSRCcolormap()
    map = ones(256, 3);
    map(4, :) = [0 0.5 0];
    map(6, :) = [0 0 0.5];
    map(8, :) = [0 0.5 0.5];
end


function name = MSRCshowName(id)
    if id == 3
        name = 'grass';
    elseif id == 5
        name = 'cow';
    elseif id == 7
        name = 'sheep';
    else
        error('Unknown name');
    end
end


function segmentation = loadMSRCSegmentation(filename, classes, incomingColorMap)
    % читает RGB изображение
    % изображение должно быть 8-битным
    
    I = imread(filename);
    if size(I, 3) ~= 3
        error('Bad segmentation');
    end
    
    % изначально заполняем метками void
    h = size(I, 1);
    w = size(I, 2);
    
    segmentation = 255 * ones(h, w);
    
    for i = 1 : length(classes)
        match = ...
            I(:, :, 1) == incomingColorMap(1, i) & ...
            I(:, :, 2) == incomingColorMap(2, i) & ...
            I(:, :, 3) == incomingColorMap(3, i);
        segmentation(match) = classes(i);
    end
    
    segmentation = uint8(segmentation);
end


function db = loadVOCdb(VOC, tag)
    classesPath = [VOC.datadir '/VOC2007/SegmentationClass/%s.png'];
    originalsPath = VOC.imgpath;
    
    db.tag = tag;
    
    fid = fopen(sprintf(VOC.seg.imgsetpath, 'train'));
    VOCTrainIds = textscan(fid, '%s');
    fclose(fid);
    
    VOCTrainIds = VOCTrainIds{:};

    if strcmp(tag, 'p07ss2')
        db.train = VOCTrainIds(1:10);
        db.dict = db.train;
        db.test = VOCTrainIds(11:20);
        db.classes = [0 15];
    elseif strcmp(tag, 'p07s6')
        db.train = VOCTrainIds(1:100);
        db.dict = db.train;
        db.test = VOCTrainIds(101:200);
        db.classes = [0 2 7 12 15 19];
    elseif strcmp(tag, 'p07s2')
        db.train = VOCTrainIds(1:100);
        db.dict = db.train;
        db.test = VOCTrainIds(101:200);
        db.classes = [0 15];
    elseif strcmp(tag, 'p07s')
        db.train = VOCTrainIds(1:100);
        db.dict = db.train;
        db.test = VOCTrainIds(101:200);
        db.classes = 0:20;
    elseif strcmp(tag, 'p07full')
        fid = fopen(sprintf(VOC.seg.imgsetpath, 'trainval'));
        VOCTrainIds = textscan(fid, '%s');
        fclose(fid);
        db.train = VOCTrainIds{:};
        db.dict = db.train;
        fid = fopen(sprintf(VOC.seg.imgsetpath, 'test'));
        VOCTestIds = textscan(fid, '%s');
        fclose(fid);
        db.test = VOCTestIds{:};
        db.classes = 0:20;
    elseif strcmp(tag, 'p07generic')
        db.classes = 0:20;
        db.loadSegmentationForce = @(id, classes) loadKeepingSomeClasses(sprintf(classesPath, id), classes);
    else
        error('Unknown db tag: %s', tag);
    end
    
    db.loadOriginal = @(id) imread(sprintf(originalsPath, id));
    db.loadSegmentation = @(id) loadKeepingSomeClasses(sprintf(classesPath, id), db.classes);
    db.backgroundClass = 0;
    
    % получает на вход какое-либо из значений db.classes
    db.className = @(id) VOCshowName(id, VOC.classes);
    db.colorMap = @() VOClabelcolormap(256);
end


function name = VOCshowName(id, names)
    if id == 0
        name = 'background';
    else
        name = names{id};
    end
end
