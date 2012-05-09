% prepare
inFile = ...
    'C:\\var\\aleksey_set\\original\\1cw.bmp';
original = imread(inFile);
if size(original, 3) == 3
    gray = rgb2gray(original);
elseif size(original, 3) == 1
    gray = original;
else
    error('Bad image');
end
imwrite(gray, [inFile  '.gray.png'], 'png')
bw = im2bw(gray, graythresh(gray));
imwrite(bw, [inFile  '.bw.png'], 'png')

% split into windows
window_size = 10;
rows = repmat((1:size(bw, 1))', 1, size(bw, 2));
cols = repmat(1:size(bw, 2), size(bw, 1), 1);
window_rows = floor((rows - 1) / window_size) + 1;
window_cols = floor((cols - 1) / window_size) + 1;
window_grid_height = max(window_rows(:));
window_grid_width = max(window_cols(:));
window_id = window_rows + (window_cols - 1) .* window_grid_height;

% bw ratio
total = histc(window_id(:), min(window_id(:)) : max(window_id(:)));
black = histc(window_id(~bw), min(window_id(:)) : max(window_id(:)));
ratio = black ./ total;
ratio = reshape(ratio, window_grid_height, window_grid_width);
imwrite(1.0 - ratio, [inFile  '.bwratio.png'], 'png')

% black run-length
is_end_of_black_line = ~bw & ...
    [ ...
        (window_id(:, 2:end) ~= window_id(:, 1:end-1)) | bw(:, 2:end), ...
        true(size(bw, 1), 1) ...
    ];
imwrite(~is_end_of_black_line, ...
    [inFile  '.is_end_of_black_line.png'], 'png');
lines = histc(window_id(is_end_of_black_line), 1 : max(window_id(:)));
black_run_length = black ./ lines;
black_run_length(lines == 0.0) = 0.0;
black_run_length = ...
    reshape(black_run_length, window_grid_height, window_grid_width);
imwrite(1.0 - black_run_length / window_size, ...
    [inFile  '.run_length.png'], 'png');

% cross-corellation
corr_candidates = @(window_id, delta) ...
    [window_id(1:end-delta, :) == window_id(1+delta:end, :); false(delta, size(window_id, 2))];
corr = @(bw, delta, candidates) ...
    [xor(bw(1 : end - delta, :), bw(1 + delta : end, :)); ...
    false(delta, size(bw, 2))] ...
    & candidates;
corr_windowed_internal = @(bw, delta, window_id, candidates) ...
    reshape( ...
        histc(window_id(corr(bw, delta, candidates)), 1:max(window_id(:))) ...
            ./ histc(window_id(candidates), 1:max(window_id(:))), ...
        window_grid_height, ...
        window_grid_width);
corr_windowed = @(bw, delta, window_id) ...
    corr_windowed_internal(bw, delta, window_id, ...
        corr_candidates(window_id, delta));
corr_1 = corr_windowed(bw, 1, window_id);
corr_5 = corr_windowed(bw, 5, window_id);
imwrite(1.0 - corr_1, [inFile  '.corr_windowed_1.png'], 'png')
imwrite(1.0 - corr_5, [inFile  '.corr_windowed_5.png'], 'png')
imwrite(corr_1 < 0.015, ...
    [inFile  '.corr_windowed_1_thresholded.png'], 'png')
imwrite(corr_5 < 0.015, ...
    [inFile  '.corr_windowed_5_thresholded.png'], 'png')

% naive classification
TEXT_MARKER = 0.5;
PICTURE_MARKER = 0;
BACKGROUND_MARKER = 1;
simple_classified = ones(window_grid_height, window_grid_width) * BACKGROUND_MARKER;
isText = (ratio > 0.02) & (ratio <= 0.85) & (black_run_length > 1) & ...
    (corr_1 > 0.015) & (corr_5 > 0.015);
isPicture = (ratio > 0.85) & (corr_1 < 0.015) & (corr_5 < 0.015);
simple_classified(isText) = TEXT_MARKER;
simple_classified(isPicture) = PICTURE_MARKER;
imwrite(simple_classified, ...
    [inFile '.simple_classified.png'], 'png')

% apply masks
haselement = @(data, index1, index2) vertcat(horzcat(true(size(data, 1) - index1 + 1, size(data, 2) - index2 + 1), false(size(data, 1) - index1 + 1, index2 - 1)), false(index1 - 1, size(data, 2)));
getelement = @(data, index1, index2) vertcat(horzcat(data(index1:end, index2:end), nan(size(data, 1) - index1 + 1, index2 - 1)), nan(index1 - 1, size(data, 2)));

majority_filter_1_filter = @(data) haselement(data, 1, 2) & ...
    getelement(data, 1, 2) ~= BACKGROUND_MARKER & ...
    getelement(data, 1, 2) == getelement(data, 2, 1) & ...
    getelement(data, 1, 2) == getelement(data, 2, 3) & ...
    getelement(data, 1, 2) == getelement(data, 3, 2);
majority_filter_1_replacement = @(data) getelement(data, 1, 2);
majority_filter_1 = @(data) setelement(data, ...
    majority_filter_1_replacement(data), ...
    majority_filter_1_filter(data), 2, 2);

majority_filter_2_filter = @(data) ...
    getelement(data, 1, 1) ~= BACKGROUND_MARKER & ...
    getelement(data, 1, 1) == getelement(data, 1, 3);
majority_filter_2 = @(data) setelement(data, ...
    data, majority_filter_2_filter(data), 1, 2);

transpose_filter = @(filter) @(data) filter(data')';

majority_filter_3 = transpose_filter(majority_filter_2);

majority_filters = @(data) majority_filter_3( ...
    majority_filter_2(majority_filter_1(data)));

majority_filtered = majority_filters(simple_classified);
imwrite(majority_filtered, ...
    [inFile '.majority_filtered.png'], 'png')

expand_corners_filter_1_filter = @(data) ...
    getelement(data, 1, 1) ~= BACKGROUND_MARKER & ...
    getelement(data, 1, 1) == getelement(data, 1, 2) & ...
    getelement(data, 1, 1) == getelement(data, 2, 2) & ...
    getelement(data, 1, 1) == getelement(data, 3, 3);
expand_corners_filter_1 = @(data) ...
    setelement(data, data, ...
    expand_corners_filter_1_filter(data), 1, 3);

mirror_filter = @(filter, dim) @(data) flipdim(filter(flipdim(data, dim)), dim);

expand_corners_filter_2 = mirror_filter(expand_corners_filter_1, 1);
expand_corners_filter_3 = mirror_filter(expand_corners_filter_1, 2);
expand_corners_filter_4 = mirror_filter(expand_corners_filter_2, 2);

expand_corners_filters = @(data) ...
    expand_corners_filter_1( ...
    expand_corners_filter_2( ...
    expand_corners_filter_3( ...
    expand_corners_filter_4(data))));

corners_expanded = expand_corners_filters(majority_filtered);
imwrite(corners_expanded, ...
    [inFile '.corners_expanded.png'], 'png')

smooth_picture_edges_filter_1_filter = @(data) ...
    getelement(data, 1, 1) == BACKGROUND_MARKER & ...
    getelement(data, 1, 2) == TEXT_MARKER & ...
    getelement(data, 1, 3) == PICTURE_MARKER;

smooth_picture_edges_filter_1 = @(data) ...
    setelement(data, PICTURE_MARKER, ...
    smooth_picture_edges_filter_1_filter(data), 1, 2);
smooth_picture_edges_filter_2 = mirror_filter(smooth_picture_edges_filter_1, 2);
smooth_picture_edges_filter_3 = transpose_filter(smooth_picture_edges_filter_1);
smooth_picture_edges_filter_4 = mirror_filter(smooth_picture_edges_filter_3, 1);

smooth_picture_edges_filters = @(data) ...
    smooth_picture_edges_filter_1( ...
    smooth_picture_edges_filter_2( ...
    smooth_picture_edges_filter_3( ...
    smooth_picture_edges_filter_4(data))));

destructive_filter_1_filter = @(data) ...
    getelement(data, 1, 1) == BACKGROUND_MARKER & ...
    getelement(data, 1, 3) == BACKGROUND_MARKER;
destructive_filter_1 = @(data) setelement(data, ...
    BACKGROUND_MARKER, destructive_filter_1_filter(data), 1, 2);

destructive_filter_2 = transpose_filter(destructive_filter_1);

destructive_filters = @(data) destructive_filter_2( ...
    destructive_filter_1(data));

for limit = [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512]
    masks_applied = simple_classified;
    for i = 1 : limit
        masks_applied_new = expand_corners_filters(majority_filters(masks_applied));
        if(any(any(masks_applied_new ~= masks_applied)))
            masks_applied = masks_applied_new;
        else
            break;
        end
    end
    for i = 1 : limit
        masks_applied_new = expand_corners_filters( ...
            smooth_picture_edges_filters( ...
            destructive_filters(masks_applied)));
        if(any(any(masks_applied_new ~= masks_applied)))
            masks_applied = masks_applied_new;
        else
            break;
        end
    end
    imwrite(masks_applied, ...
    [inFile '.masks_applied_' int2str(limit) '.png'], 'png')
end








fprintf(1, 'Will use %d files for train and %d for validation');

for fileId = 1 : length(originalFiles)
    inFile = [originalDir originalFiles{fileId}];
    outFile = [outDir originalFiles{fileId}];
    gtFile = [gtDir originalFiles{fileId} '.ground_truth.png'];
    
    fprintf(1, 'Processing %s\n', originalFiles{fileId});

    bw = makeBW(imread(inFile));
    
    imwrite(bw, [outFile  '.bw.png'], 'png');
    
    % enhance image
    cc = bwconncomp(~bw, 4);
    originalCc = cc;
    fprintf(1, 'Connected components in original image: %d, after filtering: ', cc.NumObjects);

    components = getComponents(cc);
    originalComponents = components;

    for id = find( ...
            components.areas < 5 | ...
            components.heights > 512 | ...
            components.widths > 512)
        bw(cc.PixelIdxList{id}) = true;
    end

    imwrite(bw, [outFile  '.bw.filtered.png'], 'png');

    cc = bwconncomp(~bw, 4);
    fprintf(1, '%d.\n', cc.NumObjects);

    components = getComponents(cc);

    %colored = double(~bw) + 1;

    labels = labelmatrix(cc);
    border_pixels = histc(labels(labels ~= 0 & bwperim(~bw)), 1 : max(labels(:)))';
    perims = makePerims(labels);
    features1 = perims .^ 2 ./ components.areas;
    features2 = border_pixels ./ components.areas;

    %imwrite(colored, cmap, [outFile  '.size.png'], 'png');

    %for i = 1 : cc.NumObjects
    %    colored(cc.PixelIdxList{i}) = min(2 + features1(i) / 2, size(cmap, 1));
    %end

    %imwrite(colored, cmap, [outFile  '.feature.png'], 'png');

    %imwrite(colored, cmap, [outFile  '.feature.filtered.png'], 'png');
    
    if exist(gtFile, 'file')
        gt = imread(gtFile);
    else
        fprintf(1, '%s not found, skipping\n', gtFile);
        continue;
    end

    gt_red = gt(:, :, 1);
    gt_green = gt(:, :, 2);
    gt_blue = gt(:, :, 3);
    
    isText = gt_red > 0 & gt_green == 0 & gt_blue == 0;
    isPicture = gt_red == 0 & gt_green == 0 & gt_blue == 0;

    gt_classes = zeros(1, cc.NumObjects);
    gt_classes(cellfun(@(list) isText(list(1)), cc.PixelIdxList)) = 1;
    gt_classes(cellfun(@(list) isPicture(list(1)), cc.PixelIdxList)) = 2;
    
    ok = bw;
    ok(isText) = 1;
    ok(isPicture) = 1;
    
    if(~isempty(find(ok == 0, 1)))
        imwrite(ok, [outFile  '.bw_fail.png'], 'png');
        assert(false);
    end
    assert(isempty(find(gt_classes == 0, 1)));
    NumObjects = NumObjects + cc.NumObjects;
    gComponents = mergeComponents(gComponents, components);
    gFeatures1 = [gFeatures1, features1]; %#ok<AGROW>
    gFeatures2 = [gFeatures2, features2]; %#ok<AGROW>
    gGt_classes = [gGt_classes, gt_classes]; %#ok<AGROW>
    
    % do segmentation
    %features = [features1; features2]';
    %prediction = rpredict(learned, features);
    
    % 5 == unknown
    %segmentated = uint8(~originalBw) * 5;
    
    % mark large areas as images
    %for id = find( ...
    %        originalComponents.heights > 512 | ...
    %        originalComponents.widths > 512)
    %    segmentated(originalCc.PixelIdxList{id}) = 2;
    %end
    
    %for i = 1 : cc.NumObjects
    %    segmentated(cc.PixelIdxList{i}) = 2 - (prediction(i) > 0.5);
    %end
    %imwrite(segmentated, bgtextpicturecmap, [outFile '.segmentated.png']);
end

fprintf(1, 'Got %d components\n', length(gComponents.areas));

%imwrite(~demonstrate(cc.NumObjects, components, features1, true(1, cc.NumObjects), 4, @false), [outFile '.by_complexity.png'], 'png');
%imwrite(crop(demonstrate(cc.NumObjects, components, features1, uint8(gt_classes), 5, @(h, w) u w) zeros(h, w, 'uint8')), 5000), bgtextpicturecmap, [outFile '.by_border_pixels_colored.png'], 'png');
%imwrite(crop(demonstrate(cc.NumObjects, components, perims, uint8(gt_classes), 2, @(h, w) zeros(h, w, 'uint8')), 5000), bgtextpicturecmap, [outFile '.by_perim_colored.png'], 'png');

%imwrite(crop(demonstrate(cc.NumObjects, components, features2, uint8(gt_classes), 0.01, @(h, w) zeros(h, w, 'uint8')), 6000), bgtextpicturecmap, [outFile '.by_percent_of_border_colored.png'], 'png');
%imwrite(demonstrate2d(NumObjects, gComponents, gFeatures1, gFeatures2, uint8(gGt_classes), 5000, @(h, w, ~) zeros(h, w, 'uint8')), bgtextpicturecmap, [outDir 'report.by_complexity_and_percent_of_border_colored.png'], 'png');
%imwrite(demonstrate2d(NumObjects, dotComponents(NumObjects), gFeatures1, gFeatures2, uint8(gGt_classes), 2000, @(h, w, ~) zeros(h, w, 'uint8')), bgtextpicturecmap, [outDir 'report.by_complexity_and_percent_of_border_colored.dots.png'], 'png');
%imwrite(~demonstrate(cc.NumObjects, components, features2, true(1, cc.NumObjects), 0.01, @false), [outFile '.by_percent_of_border.png'], 'png');
%imwrite(~demonstrate(cc.NumObjects, components, features2, true(1, cc.NumObjects), 0.01, @false), [outFile '.by_complexity2.png'], 'png');

%learned = learnRegression([gFeatures1; gFeatures2]', gGt_classes' == 1, gComponents.areas');
%imwrite(demonstrate2d(NumObjects, gComponents, gFeatures1, gFeatures2, uint8(gGt_classes), 5000, @(h, w, q) prepareBackground(h, w, q, learned)), bgtextpicturecmap, [originalDir 'report.by_complexity_and_percent_of_border_colored_learned.png'], 'png');

