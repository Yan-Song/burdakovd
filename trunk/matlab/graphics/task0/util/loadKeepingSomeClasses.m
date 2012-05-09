function I = loadKeepingSomeClasses(filename, classes)
    % читает индексированное изображение
    % изображение должно быть 8-битным
    % все пиксели, кроме 255 и указанных в classes заменяет на 0
    
    I = imread(filename);
    
    % изначально сохраняем только 255, остальное - нули
    transformationTable = [zeros(1, 254) 255];
    
    for i = 1 : length(classes)
        if classes(i) > 0
            % сохраняем некоторые другие классы
            transformationTable(classes(i)) = classes(i);
        end
    end

    % применяем таблицу замен к ненулевым пикселям
    locs = I > 0;
    I(locs) = transformationTable(I(locs));
end
