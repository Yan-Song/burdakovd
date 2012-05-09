function [vizualization, probabilisticVizualization] = vizualiseBlockwiseSegmentation(original, windows, classification, votes)    
    assert(isempty(find(sum(votes, 2) ~= sum(votes(:, [1 2 6 4]), 2), 1)));
    votes = votes(:, [1 2 6 4]);
    votes = votes ./ repmat(sum(votes, 2), [1 size(votes, 2)]);
    
    classification(classification == 6) = 3;
    assert(isempty(find(classification ~= 4 & classification ~= 1 & classification ~= 2 & classification ~= 3, 1)));
    
    img = original;
    
    if isa(img, 'uint8')
        img = double(img) / 255;
    end
    
    if isa(img, 'logical')
        img = double(img);
    end
    
    assert(isa(img, 'double'));
    
    if size(img, 3) == 3
        img = rgb2gray(img);
    end
      
    img = reshape(img, size(img, 1) * size(img, 2), 1);
    
    base = [0.5, 0, 0, 0; % r
            0,   0, 0, 0; % g
            0, 0.5, 0, 0]'; % b
    multiplier = [0.5, 0.5, 0.5, 1]';
    
    votes = votes(windows(:), :);
    probabilisticVizualization = bsxfun(@plus, votes * base, (votes * multiplier) .* img);
    clear votes;
    probabilisticVizualization = reshape(probabilisticVizualization, [size(original, 1), size(original, 2), 3]);
    
    classes = classification(windows(:));
    vizualization = bsxfun(@plus, base(classes, :), multiplier(classes) .* img);
    vizualization = reshape(vizualization, [size(original, 1), size(original, 2), 3]);
end
