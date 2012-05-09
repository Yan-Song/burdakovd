function this = applySimpleCRF(Y_hat, votes, good, boundaries)
    % Y_hat - выход классификатора, Mx1
    % votes - выход классификатора, количество голосов для каждого
    % суперпикселя за каждую метку, MxC
    % good - логический вектор, равен true если для этого суперпикселя есть
    % ответ в Y_hat, Nx1, содержит ровно M значений true
    % labels - разметка исходного ихображения на суперпиксели, HxW
    % crfParameterValue - параметр CRF, вес парных потенциалов
    % возвращает this
    % this.do(this, crfParameterValue) возвратит разметку суперпикселей на классы, Nx1
    
    n = length(good);
    C = size(votes, 2);

    % унарный потенциал для CRF
    unary = zeros(n, C);
    unary(good, :) = -log(votes + 1e-9);

    % начальные значения меток
    start = ones(n, 1);
    start(good) = Y_hat;
    start(~good) = mode(Y_hat);

    % парные потенциалы для суперпикселей
    pairwise = boundaries;
    pairwise(pairwise > 0) = 1.0;

    % и для меток
    labelcost = ones(C) - eye(C);

    % индексация в GCMex с 0
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
