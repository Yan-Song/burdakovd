function Components = getComponents(cc)
    h = cc.ImageSize(1);
    areas = cellfun(@numel, cc.PixelIdxList);
    [heights, widths] = cellfun(@(indexes) getHW(indexes, h), cc.PixelIdxList);
    
    Components = struct();
    Components.areas = areas;
    Components.heights = heights;
    Components.widths = widths;
end

function [height, width] = getHW(indexes, h)
    rows = rem(indexes - 1, h);
    height = max(rows) - min(rows) + 1;
    width = floor((max(indexes) - 1) / h) - floor((min(indexes) - 1) / h) + 1;
end
