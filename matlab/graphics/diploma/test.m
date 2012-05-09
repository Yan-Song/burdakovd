% prepare

setup;

options = test_setup();
db = buildDb();

blockSize = 16;

runCrossValidation(...
    db, ...
    makeBlockwisePredictor(blockSize, @makeLinearRegressionPredictor), ...
    makeBlockwiseValidator(blockSize, @validateTextPictureClassification, options.outDir), ...
    options.outDir);
