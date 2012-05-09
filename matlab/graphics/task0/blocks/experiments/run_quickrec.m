clear param;
neighbors = [2 0]; %[4 3 2 1 0];
dict_sizes = [400 200]; % [200 400 1000 100 10];
classifiers = {'svm'};

globalparam = struct();
globalparam.prefix  = 'f:/var/fulk/' ;
%globalparam.crf = 1;
globalparam.crf_trainmethod = 'gridsearch';
globalparam.crf_restrict = 0;
globalparam.p09test = 0;

globalparam.detections = 1;

if 0
globalparam.qseg_sigma = 4;
globalparam.qseg_ratio = 0.5;
globalparam.qseg_tau = 6;
globalparam.qseg_tag = sprintf('s%dr%.1ft%d', globalparam.qseg_sigma, ...
  globalparam.qseg_ratio, globalparam.qseg_tau);
end


DB_TYPES = {'pascal07'; 'pascal07s'; 'pascal07s6'; 'pascal07official'};
DB_TAGS = {'p07'; 'p07s'; 'p07s6'; 'p07off'};
%%%%%%%%%%%%%% Pascal 07

for db_index = 1:length(DB_TYPES)
for cl = 1:length(classifiers)
for d = 1:length(dict_sizes)
for n = 1:length(neighbors)
for use_crf = [1 0]
  param = globalparam;
  param.crf = use_crf;
  param.crf_traingoal = 'meanacc';
  param.classifier = classifiers{cl};
  param.dict_size = dict_sizes(d);
  if param.dict_size ~= 400
    param.dict_tag = sprintf('ikm%d', param.dict_size);
  end
  param.db_type = cell2mat(DB_TYPES(db_index));
  param.db_path = 'f:/data/private/progr/burdakovd/matlab/graphics/task0/VOCdevkit';
  param.db_tag  = cell2mat(DB_TAGS(db_index));
  param.fg_cat  = '';
  param.testall = 1;
  param.feat_dsift_size = 3;
  param.feat_tag = sprintf('dsift%d', param.feat_dsift_size);
 
  param.hists_per_cat = 250;

  param.neighbors = neighbors(n);
  param.hists_per_image = 5;
  quickrec
  clear param;
end
end
end
end
end

return;

%%%%%%%%%%%%%% GRAZ 02
cats = {'bike', 'cars', 'person'}; %#ok<UNRCH>
for cl = 1:length(classifiers)
for d = 1:length(dict_sizes)
for n = 1:length(neighbors)
  for c = 1:length(cats)
    param = globalparam;
    param.db_path = '~/data/graz02/cats';
    param.seg_prefix = '~/data/graz02/segmentations/';
    param.obj_prefix = '~/data/graz02/objsegs/';
    param.db_type = 'graz02odds';
    param.db_tag  = 'gzodd';
    param.classifier = classifiers{cl};
    param.dict_size = dict_sizes(d);
    if param.dict_size ~= 400
      param.dict_tag = sprintf('ikm%d', param.dict_size);
    end
    param.testall = 1;
    param.neighbors = neighbors(n);
    param.hists_per_cat = 5*150;
    param.fg_cat = cats{c};
    param.feat_dsift_size = 3;
    param.feat_tag = sprintf('dsift%d', param.feat_dsift_size);

    %param.feat_dsift_size = 12;
    %param.feat_tag = 'dsift';
    quickrec;
    clear param;
  end
end
end
end

%%%%%%%%%%%%%% Pascal 09
for cl = 1:length(classifiers)
for d = 1:length(dict_sizes)
for n = 1:length(neighbors)
  param = globalparam;
  param.crf_traingoal = 'intersection-union';
  param.classifier = classifiers{cl};
  param.dict_size = dict_sizes(d);
  if param.dict_size ~= 400
    param.dict_tag = sprintf('ikm%d', param.dict_size);
  end
  param.db_type = 'pascal09';
  param.db_path = '/data/pascal-09';
  param.db_tag  = 'p09';
  param.fg_cat  = '';
  param.testall = 1;
  param.feat_dsift_size = 3;
  param.feat_tag = sprintf('dsift%d', param.feat_dsift_size);
 
  param.hists_per_cat = 250;

  param.neighbors = neighbors(n);
  param.hists_per_image = 5;
  quickrec
  clear param;
end
end
end
