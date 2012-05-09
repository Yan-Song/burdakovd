function adj = boundaryLength(map)

    if min(map(:)) < 1 || size(map, 3) ~= 1
        error('Bad map');
    end
    
    map = double(map);
    
    h = size(map, 1);
    w = size(map, 2);
    
    n = max(map(:));
    
    vertical = (map(1 : h - 1, :) - 1) * n + map(2 : h, :);
    horizontal = (map(:, 1 : w - 1) - 1) * n + map(:, 2 : w);
    
    adj = zeros(n);
    adj(:) = vl_binsum(adj(:), 1, vertical(:));
    adj(:) = vl_binsum(adj(:), 1, horizontal(:));
    adj = adj + adj';
    adj = adj .* (ones(n) - eye(n));
end
