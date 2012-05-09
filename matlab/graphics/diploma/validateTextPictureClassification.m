function result = validateTextPictureClassification(db, predictor)
    result = 0;
    
    for i = 1 : db.size()
        bw = db.bw(i);
        prediction = predictor.predict(bw, db.name(i));
        gt = db.groundTruth(i);
        
        totalPixels = length(find(~bw));

        isText = gt == 1;
        isPicture = gt == 2;
        
        correctPixels = ...
            length(find(~bw(:) & isText(:) & prediction(:) == 1)) + ...
            length(find(~bw(:) & isPicture(:) & prediction(:) == 2));
        
        gtInvalidPixels = ...
            length(find(~bw & ~isText & ~isPicture));
        
        invalidPixels = ...
            length(find(~bw(:) & prediction(:) ~= 1 & prediction(:) ~= 2));
        
        fprintf(...
            'Validated image %s: %d pixels total, %.2f%% pixels correct, %.2f%% pixels invalid, %.2f%% pixels invalid in ground truth\n', ...
            db.name(i), ...
            totalPixels, ...
            correctPixels / (totalPixels - gtInvalidPixels) * 100, ...
            invalidPixels / (totalPixels - gtInvalidPixels) * 100, ...
            gtInvalidPixels / totalPixels * 100);
        result = result + correctPixels / totalPixels;
    end
    
    result = result / db.size();
end
