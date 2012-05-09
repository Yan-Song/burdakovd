function result = makeIndexes(I, dictionary)
    % �������� � ��������������� ����������� ������� �� �� ������ � �������
    % 255 - �� ����������
    % ��������� - double
    
    if size(I, 3) ~= 1
        error 'Need indexed image, got RGB?';
    end
    
    if max(I(:)) > 255 || min(I(:)) < 0 || not(strcmp(class(I), 'uint8'))
        % ����� uint8 - ��� �����!
        error 'Bad image'
    end
    
    if max(dictionary(:)) > 253 || min(dictionary(:)) < 0
        error 'Bad dictionary'
    end
    
    % �������, ������������ [0:255] � ������� �������
    % ���������� ���, ��� 255 + 1 == 255 � ������� �� �������� 254
    % ������� 254 � 255 ������������ � ���� � �� �� �����
    % transformationTable(255)
    transformationTable = [-ones(1, 254) 255];
    
    for i = 1 : length(dictionary)
        transformationTable(dictionary(i) + 1) = i;
    end
    
    % ��� ���������� ���, ��� uint8(255) + 1 = 255
    result = transformationTable(I + 1);
    
    if min(result(:)) < 1
        error('Image didn''t match dictionary.');
    end
end
