function graph = makeGraph(original, blockSize, distance)
    if (size(original, 3) == 1)
        original = repmat(original, [1 1 3]);
    end

    assert(size(original, 3) == 3);
    
    if(isa(original, 'uint8'))
        original = double(original) / 255;
    end
    
    assert(isa(original, 'double'));
    
    hBlocks = ceil(size(original, 1) / blockSize);
    wBlocks = ceil(size(original, 2) / blockSize);
    
    graph = ones( ...
        size(original, 1) + (hBlocks - 1) * distance, ...
        size(original, 2) + (wBlocks - 1) * distance, ...
        3);
    
    graph((distance + blockSize) * (0 : (hBlocks - 1)) + blockSize / 2, :, [1 2 3]) = 0.2;
    graph(:, (distance + blockSize) * (0 : (wBlocks - 1)) + blockSize / 2, [1 2 3]) = 0.2;
    
    rows = repmat((1 : size(original, 1))', [1 size(original, 2)]);
    cols = repmat(1 : size(original, 2), [size(original, 1) 1]);
    
    rows = rows + distance * floor((rows - 1) / blockSize);
    cols = cols + distance * floor((cols - 1) / blockSize);
    
    indices = rows + (cols - 1) * size(graph, 1);
    indices = indices(:);
    indices = [indices; indices + size(graph, 1) * size(graph, 2); indices + 2 * size(graph, 1) * size(graph, 2)];
    
    graph(indices) = original(:) * 1;
end
