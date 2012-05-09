function perims = makePerims(labels)
    t = labels';
    perims = (f(labels) + f(t) + f(flipdim(labels, 1)) + f(flipdim(t, 1)))';
end

function perims = f(labels)
    bottoms = [labels(2:end, :); zeros(1, size(labels, 2))];
    markers = labels(bottoms == 0 & labels ~= 0);
    perims = histc(markers, 1:max(labels(:)));
end
