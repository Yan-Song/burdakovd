function [blockwise, windows] = makeBlockwiseGroundTruthFromPixelwise(blockSize, pixelwise, bw, original, outFile)
    assert(min(pixelwise(:)) > 0);
    assert(isempty(find(pixelwise == 5, 1)));
    pixelwise(bw) = 5;
    clear bw;

    windows = window_id(size(pixelwise, 1), size(pixelwise, 2), blockSize);
    
    nClasses = double(max(pixelwise(:)));
    nWindows = max(windows(:));
    
    indices = windows + nWindows * (double(pixelwise) - 1);
    clear pixelwise;
    
    counts = zeros(1, nWindows * nClasses);
    counts = vl_binsum(counts, ones(1, length(indices(:))), indices(:));
    clear indices;
    counts = reshape(counts, nWindows, nClasses);
    counts(:, 1) = counts(:, 1) + 0.5 * counts(:, 3);
    counts(:, 2) = counts(:, 2) + 0.5 * counts(:, 3);
    counts(:, 3) = 0;
    counts = counts / (blockSize ^ 2);
    blockwise = zeros(nWindows, 1);
    blockwise(counts(:, 1) > counts(:, 2) + counts(:, 4)) = 1;
    blockwise(counts(:, 2) > counts(:, 1) + counts(:, 4)) = 2;
    blockwise(counts(:, 4) > counts(:, 1) + counts(:, 2)) = 4;
    blockwise(blockwise == 0) = 6;
    
    if false
        votes = zeros(nWindows, 6);
        votes((1 : nWindows)' + (blockwise - 1) * nWindows) = 1;
        imwrite(vizualiseBlockwiseSegmentation(original, windows, blockwise, votes), [outFile  '.blockwise_ground_truth.png'], 'png');
    end
    
    blockwise(blockwise == 6 & sum(counts(:, [1 2 4]), 2) == 0) = 7;
end
