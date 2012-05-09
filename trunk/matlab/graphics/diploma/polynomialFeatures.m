function features = polynomialFeatures(original, n)
    if n == 0
        features = ones(size(original, 1), 1);
    else
        m = size(original, 2);
        combs = sort(combnk(1 : n + m, m), 2);
        d = [combs(:, 1) diff(combs, 1, 2)] - 1;

        features = zeros(size(original, 1), size(d, 1));
        for i = 1 : size(d, 1)
            features(:, i) = prod(bsxfun(@power, original, d(i, :)), 2);
        end
    end
end
