function [ correctRatio, totalBlocks, totalCheckableBlocks, correctBlocks ] = rawBlockwiseValidate( gt, prediction )
    assert(length(prediction) == length(gt));
    totalBlocks = length(prediction);
    totalCheckableBlocks = length(find(gt ~= 6 & gt ~= 7));
    correctBlocks = length(find(gt(gt ~= 6 & gt ~= 7) == prediction(gt ~= 6 & gt ~= 7)));
    correctRatio = correctBlocks / totalCheckableBlocks;
end
