function demonstration = demonstrate2d(~, components, features1, features2, values, n, background)
    % features1 - row
    % features2 - col

    mWidth = max(components.widths);
    mHeight = max(components.heights);
    
    min1 = min(features1); min2 = min(features2);

    features1 = features1 - min1;
    features2 = features2 - min2;
    
    good = features1 < max(features1) / 16;
    
    max1 = max(features1(good));
    max2 = max(features2);
    
    k1 = max1 / (n - mHeight);
    k2 = max2 / (n - mWidth);
    
    features1 = round(features1 / k1);
    features2 = round(features2 / k2);
    
    canvas = background(n, n, @(r, c) [(r - mHeight / 2) * k1 + min1, (c - mWidth / 2) * k2 + min2]);

    for i = find(good)
        rdelta = - min(components.rows{i}) + features1(i) + floor((mHeight - components.heights(i)) / 2);
        rows = components.rows{i} + rdelta;
        cdelta = - min(components.cols{i}) + features2(i) + floor((mWidth - components.widths(i)) / 2);
        cols = components.cols{i} + cdelta;
        indexes = rows + n * cols + 1;
        canvas(indexes) = values(i);
    end
    
    demonstration = canvas;
end
