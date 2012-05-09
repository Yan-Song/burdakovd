function result = makeIndexes(I, dictionary)
    % заменяет в индексированном изображении пиксели на их номера в словаре
    % 255 - не заменяется
    % результат - double
    
    if size(I, 3) ~= 1
        error 'Need indexed image, got RGB?';
    end
    
    if max(I(:)) > 255 || min(I(:)) < 0 || not(strcmp(class(I), 'uint8'))
        % класс uint8 - это важно!
        error 'Bad image'
    end
    
    if max(dictionary(:)) > 253 || min(dictionary(:)) < 0
        error 'Bad dictionary'
    end
    
    % таблица, отображающая [0:255] в индексы словаря
    % пользуемся тем, что 255 + 1 == 255 и словарь не содержит 254
    % поэтому 254 и 255 отображаются в одно и то же число
    % transformationTable(255)
    transformationTable = [-ones(1, 254) 255];
    
    for i = 1 : length(dictionary)
        transformationTable(dictionary(i) + 1) = i;
    end
    
    % тут пользуемся тем, что uint8(255) + 1 = 255
    result = transformationTable(I + 1);
    
    if min(result(:)) < 1
        error('Image didn''t match dictionary.');
    end
end
