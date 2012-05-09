function this = predictClasses(good, Y_hat, votes, original, labels, classes, options, boundaries)
    % возвращает this
    % this.do(this, learned) возвратит разметку пикселей на классы, HxW
     
    [fromOptions, fromLearned, const] = makeFunctions(labels, classes, options);
    
    if strcmp(options.crfType, 'simple')
        if strcmp(options.crfParameterType, 'fixed')
            this.crf = applySimpleCRF(Y_hat, votes, good, boundaries);
            this.do = fromOptions;
        elseif strcmp(options.crfParameterType, 'fakegridsearch')
            this.crf = applyNoCRF(Y_hat, good);
            this.do = const;
        elseif strcmp(options.crfParameterType, 'gridsearch')
            this.crf = applySimpleCRF(Y_hat, votes, good, boundaries);
            this.do = fromLearned;
        else
            error('Unsupported simple CRF parameter type');
        end
    elseif strcmp(options.crfType, 'extended')
        if strcmp(options.crfParameterType, 'fixed')    
            this.crf = applyExtendedCRF(Y_hat, votes, good, original, labels, boundaries);
            this.do = fromOptions;
        elseif strcmp(options.crfParameterType, 'gridsearch')
            this.crf = applyExtendedCRF(Y_hat, votes, good, original, labels, boundaries);
            this.do = fromLearned;
        else
            error('Unsupported extended CRF parameter type');
        end
    elseif strcmp(options.crfType, 'none')
        this.crf = applyNoCRF(Y_hat, good);
        this.do = const;
    else
        error('Unsupported CRF type');
    end
end

function [fromOptions, fromLearned, const] = makeFunctions(labels, classes, options)
    fromOptions = @(this, learned) postProcess(this.crf.do(this.crf, options.crfParameterValue), labels, classes);
    fromLearned = @(this, learned) postProcess(this.crf.do(this.crf, learned.crfParameterValue), labels, classes);
    const = @(this, learned) postProcess(this.crf, labels, classes);
end

function predicted = postProcess(labelBySuperPixel, labels, classes)
    % замена внутренних классов на классы бд
    labelBySuperPixel = uint8(classes(labelBySuperPixel));
    predicted = labelBySuperPixel(labels);
end

function labelBySuperPixel = applyNoCRF(Y_hat, good)
    % без использования CRF
    labelBySuperPixel(good) = Y_hat;
    labelBySuperPixel(~good) = mode(Y_hat);
end
