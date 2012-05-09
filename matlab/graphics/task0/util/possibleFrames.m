function frames = possibleFrames(segmentation, chancesByClass, binSize)
    % ���������� ������� 4xN

    h = size(segmentation, 1);
    w = size(segmentation, 2);

    % �� ����� ������ ����� ����������
    h = max(0, h + 1 - 4 * binSize);
    w = max(0, w + 1 - 4 * binSize);
    
    mx = ones(h, 1) * (2 * binSize + 0.5 + (0 : w - 1));
    my = (2 * binSize + 0.5 + (0 : h - 1))' * ones(1, w);
    
    % ���������� ���������. ����������.
    positions = int32(my) + size(segmentation, 1) * int32(mx - 1);
    labels = segmentation(positions);
    good = labels ~= 255;
    labels = labels(good);
    mx = mx(good);
    my = my(good);
    chances = chancesByClass(labels);
    
    % �������� ����� ��� SIFT, ������ ��� ������ ����� ����������� ����
    % ��������� ������� �� � ������
    chosen = rand(1, size(chances, 2)) < chances;
    
    X = mx(chosen);
    Y = my(chosen);
    n = size(X, 1);
    scale = ones(n, 1) * binSize / 3;
    orientation = zeros(n, 1);
    
    frames = [X Y scale orientation]';
end
