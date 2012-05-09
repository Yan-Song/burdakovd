function learned = learnRegression(features, classes, weights)
    learned = struct();
    learned.mean = mean(features);
    features = bsxfun(@minus, features, learned.mean);
    learned.sigma = mean(features .^ 2) .^ 0.5;
    features = bsxfun(@rdivide, features, learned.sigma);
    
    learned.degree = 2;
    features = polynomialFeatures(features, learned.degree);
    
    initialTheta = zeros(size(features, 2), 1);
    options = optimset('GradObj', 'on');
    classes = classes * 2 - 1;
    j = @(theta) costFunction(features, classes, weights, theta);
    [learned.theta, ~, e] = fminunc(j, initialTheta, options);
    %assert(e == 1 || e == 3);
end

function [cost, grad] = costFunction(features, classes, weights, theta)
    predictions = features * theta;
    cost = sum(weights .* l1exp(-classes .* predictions));
    grad = -(f1m11e(-classes .* predictions) .* classes .* weights)' * features;
    %fprintf('Cost = %f\n', cost);
end

function e = f1m11e(x)
    ex = exp(x);
    e = ex ./ (1 + ex);
    e(isinf(ex)) = 1;
end

function e = l1exp(x)
    e = log(1 + exp(x));
    e(isinf(e)) = x(isinf(e));
    e(e == 0) = exp(x(e == 0));
end
