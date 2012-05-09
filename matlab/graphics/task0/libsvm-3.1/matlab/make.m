% This make.m is used under Windows

% add -largeArrayDims on 64-bit machines

mex -g -I..\ -c ..\svm.cpp
mex -g -I..\ -c svm_model_matlab.c
mex -g -I..\ svmtrain.c svm.obj svm_model_matlab.obj
mex -g -I..\ svmpredict.c svm.obj svm_model_matlab.obj
mex -g libsvmread.c
mex -g libsvmwrite.c
