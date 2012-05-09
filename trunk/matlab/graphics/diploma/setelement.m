function result = setelement(data, replacement, where, index1, index2)
    % if replacement is scalar
    if (size(replacement, 1) == 1 && size(replacement, 2) == 1)
        replacement = ones(size(data, 1), size(data, 2)) * replacement;
    end

    assert(size(data, 1) == size(replacement, 1));
    assert(size(data, 2) == size(replacement, 2));
    assert(size(data, 1) == size(where, 1));
    assert(size(data, 2) == size(where, 2));
    
    replacement = replacement(1 : end - index1 + 1, 1 : end - index2 + 1);
    replacement = horzcat(nan(size(data, 1) - index1 + 1, index2 - 1), replacement);
    replacement = vertcat(nan(index1 - 1, size(data, 2)), replacement);
    
    tmp1 = where(end - index1 + 2 : end, :);
    tmp2 = where(:, end - index2 + 2 : end);
    assert(not(any(tmp1(:))) && not(any(tmp2(:))));
    
    where = where(1 : end - index1 + 1, 1 : end - index2 + 1);
    where = horzcat(false(size(data, 1) - index1 + 1, index2 - 1), where);
    where = vertcat(false(index1 - 1, size(data, 2)), where);
    
    result = data;
    result(where) = replacement(where);
end
