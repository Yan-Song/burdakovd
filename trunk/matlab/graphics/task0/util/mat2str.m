function s = mat2str(A)
    % ��������� ����� ����� ��������� � �������, ����� �� ���� ��������
    s = ['[ dims = ' str(ndims(A)) '; size = ' str(size(A)) '; content = ' str(double(A)) ' ]'];
end

function s = str(A)
    % �������������� ����������� ������� � �������������� ������
    s = num2str(A(:)', 20);
end
