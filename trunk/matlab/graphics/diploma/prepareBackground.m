function background = prepareBackground(h, w, q, learned)
    background = zeros(h, w, 'uint8');
    step = 16;
    rows = repmat((1 : floor(h/step)-1)', [1 floor(w/step)-1]) * step;
    cols = repmat(1 : floor(w/step)-1, [floor(h/step)-1 1]) * step;
    indexes = rows(:) + (cols(:) - 1) * h;
    prediction = rpredict(learned, q(rows(:), cols(:)));
    
    cmps = {@(p) p > 0.5, @(p) p < 0.5};
    values = [3 4];
    
    for class = [1 2]
        xs = indexes(cmps{class}(prediction));
        for i = 0 : step - 1
            for j = 0 : step - 1
                %fprintf(1, 'Preparing background, class=%d, i=%d, j=%d\n', class, i, j);
                background(xs + i + h * j) = values(class);
            end
        end
    end
end
