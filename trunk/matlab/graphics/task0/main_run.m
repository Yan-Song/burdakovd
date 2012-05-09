main_setup;

dbs = {'p07full'};%, 'p07s6', 'p07s2', 'p07s'};
%dbs = {'msrcocidv2grasscow'}; %{'msrcocidv2grasscow', 'msrcocidv2grasscowsheep'};

colorImportances = [50];

trees = 200; %[20 20 200];
mTrees = 0;
precedentsPerCategory = 1000; %[Inf 1000 1000];

learnClassifierWeighted = false; % [false true]
crfTypes = {'none', 'simple'};
%crfTypes = {'extended'};
options.crfParameterType = 'gridsearch'; % gridsearch, fixed, fakegridsearch
crfParameterValues = 1;%[0.0078125 0.015625 0.03125 0.0625 0.125 0.25 0.5 1];

for i = 1 : length(dbs)
    for dictionarySize = 200 %[200 100 400]
        options.dictionarySize = dictionarySize;
        for colorImportance = colorImportances
            options.featuresSIFT = colorImportance < 1000;
            options.featuresColor = colorImportance > 0;
            options.colorImportance = colorImportance;
            if ~options.featuresSIFT
                options.colorImportance = 1;
            end
            for j = 1 : length(trees)
                options.classifierTreeCount = trees(j);
                options.precedentsPerCategory = precedentsPerCategory(j);
                for mTree = mTrees
                    options.mTree = mTree;
                    for k = 1 : length(learnClassifierWeighted)
                        options.learnClassifierWeighted = learnClassifierWeighted(k);
                        for m = 1 : length(crfTypes)
                            options.crfType = crfTypes{m};
                            for crfParameterValue = crfParameterValues
                                options.crfParameterValue = crfParameterValue;
                                runSegmentation(VOCopts, MSRC, options, dbs{i});
                            end
                        end
                    end
                end
            end
        end
    end
end
