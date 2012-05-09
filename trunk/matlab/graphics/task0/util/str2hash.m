function hash = str2hash(s)
    hash = int64(1000007);
    n = size(s, 2);
    
    for i = 1 : n
        hash = mod(hash * int64(1031) + int64(s(1, i)), 1000000007);
    end
end
