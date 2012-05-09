function cropped = crop(a, limit)
    cropped = a(max(1, size(a, 1) - limit + 1):end, 1:min(limit, size(a, 2)));
end
