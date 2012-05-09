function s = mat2str(A)
    % сохраняем также число измерений и размеры, чтобы не было коллизий
    s = ['[ dims = ' str(ndims(A)) '; size = ' str(size(A)) '; content = ' str(double(A)) ' ]'];
end

function s = str(A)
    % предварительно преобразуем матрицу в горизонтальный вектор
    s = num2str(A(:)', 20);
end
