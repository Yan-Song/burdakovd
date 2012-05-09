% setup VOC
addpath('VOCdevkit/VOCcode/');
VOCinit();


% setup vlfeat
addpath('vlfeat-0.9.9/toolbox/');
vl_setup();


% setup GCMex
addpath('GCMex');


% setup libsvm
addpath('libsvm-3.1/matlab');


% setup blocks
addpath('blocks');
blocks_setup();


% self setup
options.classesPath = [VOCopts.datadir '/VOC2007/SegmentationClass/%s.png'];
options.imagesPath = VOCopts.imgpath;

addpath('util/');
