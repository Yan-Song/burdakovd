function this = applyExtendedCRF(Y_hat, votes, good, original, labels, boundaries)
    % Y_hat - выход классификатора, Mx1
    % votes - выход классификатора, количество голосов для каждого
    % суперпикселя за каждую метку, MxC
    % good - логический вектор, равен true если для этого суперпикселя есть
    % ответ в Y_hat, Nx1, содержит ровно M значений true
    % original - исходное изображение, HxW
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

    % среднесуперпиксельные значения цвета
    original = double(original);
    original = original - min(original(:));
    original = original / max(original(:));
    I = vl_xyz2luv(vl_rgb2xyz(original));
    I(isnan(I)) = 0;
    [l, u, v] = getSuperPixelColor(I, labels);
    
    l = single(l);
    u = single(u);
    v = single(v);

    colorDifferences = pairwiseDifferences2(l);
    colorDifferences = colorDifferences + pairwiseDifferences2(u);
    colorDifferences = colorDifferences + pairwiseDifferences2(v);
    colorDifferences = sqrt(double(colorDifferences));
    
    % нормализация
    colorDifferences = colorDifferences / max(colorDifferences(:));

    % парные потенциалы для суперпикселей
    pairwise = boundaries ./ (1 + colorDifferences);
    pairwise = sparse(pairwise);

    % и для меток
    labelcost = ones(C) - eye(C);

    % индексация в GCMex с 0
    this.start = start' - 1;
    this.unary = single(unary');
    
    % свой sparse o_O. Стандартный чото память не экономит.
    pairwise = full(pairwise(:));
    this.pairwise_indexes = uint32(find(pairwise ~= 0));
    this.pairwise_values = pairwise(this.pairwise_indexes);
    
    this.labelcost = single(labelcost);
    this.n = n;
    this.do = @doer;
    
    if ~isempty(find(isnan(this.unary), 1)) || ~isempty(find(isnan(this.pairwise_values), 1)) || ~isempty(find(isnan(this.labelcost), 1)) || ~isempty(find(isnan(this.start), 1))
        error('NaN detected');
    end
end

function labelBySuperPixel = doer(this, value)
    pairwise = sparse(this.n, this.n);
    pairwise(this.pairwise_indexes) = value * this.pairwise_values;
    [labelBySuperPixel, ~, ~] = GCMex(this.start, this.unary, pairwise, this.labelcost);
    labelBySuperPixel = reshape(labelBySuperPixel + 1, this.n, 1);
end

function colorDifferences = pairwiseDifferences2(colors)
    % считаем квадраты попарных разниц
    n = length(colors);
    vertical = reshape(colors, [n, 1]);
    horizontal = reshape(colors, [1, n]);
    colorDifferences = repmat(vertical, [1, n]) - repmat(horizontal, [n, 1]);
    colorDifferences = colorDifferences .* colorDifferences;
end
