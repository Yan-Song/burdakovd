% setup VOC
addpath('VOCdevkit/VOCcode/');
VOCinit();


% setup vlfeat
run('vlfeat-0.9.9/toolbox/vl_setup');


% setup random forest
addpath('randomforest-matlab/RF_Class_C/');
addpath('randomforest-matlab/RF_Reg_C/');


% setup GCMex
addpath('GCMex');


% path to MSRC images
MSRC.originals = 'F:/var/dropbox/My Dropbox/shared.kreved.org/MSRC_ObjCategImageDatabase_v2/Images/';
MSRC.groundTruth = 'F:/var/dropbox/My Dropbox/shared.kreved.org/MSRC_ObjCategImageDatabase_v2/GroundTruth/';


% self setup
clear options;
options.descriptorsForDictionary = 100000;
%options.dictionarySize = 200;
options.sift.binSize = 3; % размер ОДНОЙ корзины sift
%options.learnClassifierWeighted = true;
%options.classifierTreeCount = 20;
%options.precedentsPerCategory = Inf;

options.resultsPath = 'F:/var/reports/';

options.cachingPolicy.use = true;
options.cachingPolicy.path = 'F:/var/cache/matlab/';

addpath('util/');
