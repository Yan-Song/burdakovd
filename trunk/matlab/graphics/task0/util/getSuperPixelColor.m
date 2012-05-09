function [ r, g, b ] = getSuperPixelColor(original, labels)
    % возвращает вертикальные вектора
    
    if(min(labels(:)) < 1)
        error('Bad labels.');
    end
    
    n = max(labels(:));
    
    % нормализуем исходное изображение
    original = double(original);
    original = original - min(original(:));
    original = original / max(original(:));
    
    r = original(:, :, 1);
    r = vl_binsum(zeros(n, 1), r(:), double(labels(:)));
    g = original(:, :, 2);
    g = vl_binsum(zeros(n, 1), g(:), double(labels(:)));
    b = original(:, :, 3);
    b = vl_binsum(zeros(n, 1), b(:), double(labels(:)));
    
    counts = vl_binsum(zeros(n, 1), 1, double(labels(:)));
    
    r = r ./ counts;
    g = g ./ counts;
    b = b ./ counts;
end
