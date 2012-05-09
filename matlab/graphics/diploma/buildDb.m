function db = buildDb()
    originalDir = 'C:\\data\\private\\doc\\Универ\\Дипломная работа\\материалы\\data\\original\\';
    gtDir = 'C:\\data\\private\\doc\\Универ\\Дипломная работа\\материалы\\data\\ground_truth\\';
    setsDir = 'C:\\data\\private\\doc\\Универ\\Дипломная работа\\материалы\\data\\sets\\';
    originalFilesList = 'main.txt';
    
    originalFiles = loadFileNames([setsDir originalFilesList]);
    fprintf(1, 'Have %d images at all\n', length(originalFiles));

    db.size = @() length(originalFiles);
    db.name = @(n) originalFiles{n};
    db.original = @(n) imread([originalDir originalFiles{n}]);
    db.bw = @(n) makeBW(db.original(n));
    db.groundTruth = @(n) parseGT(imread([gtDir originalFiles{n} '.ground_truth.png']));
    db.sub = @(ids) makeSubDb(db, ids);
    db.test = @(ids) removeGT(db.sub(ids));
end

function train = makeSubDb(db, ids)
    assert(~isempty(ids));
    train.size = length(ids);
    train.name = @(n) db.name(ids(n));
    train.original = @(n) db.original(ids(n));
    train.bw = @(n) db.bw(ids(n));
    train.groundTruth = @(n) db.groundTruth(ids(n));
    train.sub = @(ids) makeSubDb(db, ids);
    train.test = @(ids) removeGT(train.sub(ids));
end

function withoutGT = removeGT(db)
    withoutGT = rmfield(db, 'groundTruth');
end

function gt = parseGT(image)
    gt_red = image(:, :, 1);
    gt_green = image(:, :, 2);
    gt_blue = image(:, :, 3);
    
    isText = gt_red > gt_green & gt_red > gt_blue;
    isPicture = gt_blue > gt_red & gt_blue > gt_green;
    isBoth = gt_red == gt_blue & gt_red > gt_green;
    isNone = gt_red == gt_blue & gt_red == gt_green;
    
    gt = zeros(size(image, 1), size(image, 2), 'uint8');
    gt(isText) = 1;
    gt(isPicture) = 2;
    gt(isBoth) = 3;
    gt(isNone) = 4;
end
