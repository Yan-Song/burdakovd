function validator = makeBlockwiseValidator(blockSize, pixelwise, outDir)
    validator = @(db, predictor) impl(db, predictor, blockSize, pixelwise, outDir);
end

function result = impl(db, predictor, blockSize, ~, outDir)
    result = 0;
    
    for i = 1 : db.size()
        bw = db.bw(i);
        prediction = predictor.predict(bw, db.name(i));
        gt = makeBlockwiseGroundTruthFromPixelwise(blockSize, db.groundTruth(i), bw, db.original(i), [outDir db.name(i)]);
        
        [ correctRatio, totalBlocks, totalCheckableBlocks, correctBlocks ] = rawBlockwiseValidate( gt, prediction );
                
        fprintf(...
            'Validated image %s: %d blocks total, %.2f%% blocks checkable, %.2f%% of them is correct\n', ...
            db.name(i), ...
            totalBlocks, ...
            totalCheckableBlocks / totalBlocks * 100, ...
            correctRatio * 100);
        result = result + correctBlocks / totalCheckableBlocks;
    end
    
    result = result / db.size();
end
