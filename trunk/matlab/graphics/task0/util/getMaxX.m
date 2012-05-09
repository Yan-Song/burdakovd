function M = getMaxX(x, y)
    % получает вертикальные вектора x и y
    % возвращает вертикальный вектор длины length(unique(x)) с ответами
    % ans(i) содержит элемент из y, который наиболее часто встречается
    % напротив (unique(x))(i)
    
    x = sort(bitshift(uint32(x), 5) + uint32(y));
    y = bitand(x, 31);
    x = bitshift(x, -5);

    % indexes of ends of blocks
    ends = [0; find(diff(x)); length(x)];
    
    % pre-allocation
    M = zeros(length(ends) - 1, 1);

    % going through blocks
    for i = 2 : length(ends)
        yblock = y(ends(i - 1) + 1 : ends(i));
        
        % Now only need to find most frequent element in yblock
        yends = [0; find(diff(yblock)); length(yblock)];
        [~, imax] = max(diff(yends));
        M(i - 1) = yblock(yends(imax + 1));
    end
end
