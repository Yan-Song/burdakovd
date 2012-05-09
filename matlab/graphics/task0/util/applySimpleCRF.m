function this = applySimpleCRF(Y_hat, votes, good, boundaries)
    % Y_hat - ����� ��������������, Mx1
    % votes - ����� ��������������, ���������� ������� ��� �������
    % ������������ �� ������ �����, MxC
    % good - ���������� ������, ����� true ���� ��� ����� ������������ ����
    % ����� � Y_hat, Nx1, �������� ����� M �������� true
    % labels - �������� ��������� ����������� �� ������������, HxW
    % crfParameterValue - �������� CRF, ��� ������ �����������
    % ���������� this
    % this.do(this, crfParameterValue) ��������� �������� ������������� �� ������, Nx1
    
    n = length(good);
    C = size(votes, 2);

    % ������� ��������� ��� CRF
    unary = zeros(n, C);
    unary(good, :) = -log(votes + 1e-9);

    % ��������� �������� �����
    start = ones(n, 1);
    start(good) = Y_hat;
    start(~good) = mode(Y_hat);

    % ������ ���������� ��� �������������
    pairwise = boundaries;
    pairwise(pairwise > 0) = 1.0;

    % � ��� �����
    labelcost = ones(C) - eye(C);

    % ���������� � GCMex � 0
    this.start = start' - 1;
    this.unary = single(unary');
    this.pairwise = pairwise;
    this.labelcost = single(labelcost);
    this.n = n;
    this.do = @doer;
    if ~isempty(find(isnan(this.unary), 1)) || ~isempty(find(isnan(this.pairwise), 1)) || ~isempty(find(isnan(this.labelcost), 1)) || ~isempty(find(isnan(this.start), 1))
        error('NaN detected');
    end
end

function labelBySuperPixel = doer(this, value)
    [labelBySuperPixel, ~, ~] = GCMex(this.start, this.unary, value * this.pairwise, this.labelcost);
    labelBySuperPixel = reshape(labelBySuperPixel + 1, this.n, 1);
end
