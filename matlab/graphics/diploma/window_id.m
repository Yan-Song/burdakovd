function ids = window_id(height, width, window_size)
    rows = repmat((1:height)', 1, width);
    cols = repmat(1:width, height, 1);
    window_rows = floor((rows - 1) / window_size) + 1;
    window_cols = floor((cols - 1) / window_size) + 1;
    window_grid_height = max(window_rows(:));
    ids = window_rows + (window_cols - 1) .* window_grid_height;
end
