function new = addLegend(image)
    h = size(image, 1);
    new = [(h - 1 : -1 : 0)' / (h - 1) * ones(1, 4), 0.5 * ones(h, 2), image];
end
