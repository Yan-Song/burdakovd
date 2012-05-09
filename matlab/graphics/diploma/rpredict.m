function prediction = rpredict(learned, features)
    features = bsxfun(@minus, features, learned.mean);
    features = bsxfun(@rdivide, features, learned.sigma);
    
    features = polynomialFeatures(features, learned.degree);
    
    % todo
    scale = 18;
    prediction = 1 ./ (1 + exp(-features * learned.theta * scale));
end
