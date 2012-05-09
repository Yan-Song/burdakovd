function I = loadKeepingSomeClasses(filename, classes)
    % ������ ��������������� �����������
    % ����������� ������ ���� 8-������
    % ��� �������, ����� 255 � ��������� � classes �������� �� 0
    
    I = imread(filename);
    
    % ���������� ��������� ������ 255, ��������� - ����
    transformationTable = [zeros(1, 254) 255];
    
    for i = 1 : length(classes)
        if classes(i) > 0
            % ��������� ��������� ������ ������
            transformationTable(classes(i)) = classes(i);
        end
    end

    % ��������� ������� ����� � ��������� ��������
    locs = I > 0;
    I(locs) = transformationTable(I(locs));
end
