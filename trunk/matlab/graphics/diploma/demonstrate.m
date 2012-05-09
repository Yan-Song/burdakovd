function demonstration = demonstrate(NumObjects, components, features, values, step, background)
    assert(size(features, 1) == 1);
    assert(size(features, 2) == NumObjects);
    
    elementToColumn = floor(features / step);
    elementToColumn = elementToColumn - min(elementToColumn) + 1;
    nColumns = max(elementToColumn);
    
    topBorder = 0; bottomBorder = 1;
    
    columnWidth = max(components.widths) + 1;
    
    heights = zeros(1, nColumns);
    for i = 1 : NumObjects
        heights(elementToColumn(i)) = ...
            heights(elementToColumn(i)) + ...
            components.heights(i) + topBorder + bottomBorder;
    end
    
    canvasHeight = max(heights);
    canvasWidth = columnWidth * nColumns;
    
    canvas = background(canvasHeight, canvasWidth);
    
    usedHeights = zeros(1, nColumns);
    
    for i = 1 : NumObjects
        columnId = elementToColumn(i);
        leftBorder = floor((columnWidth - components.widths(i)) / 2);
        rows = components.rows{i} + (- max(components.rows{i}) + ...
            canvasHeight - usedHeights(columnId) - bottomBorder);
        cols = components.cols{i} + ((columnId - 1) * columnWidth - min(components.cols{i}) + leftBorder);
        indexes = rows + canvasHeight * cols + 1;
        canvas(indexes) = values(i);
        usedHeights(columnId) = ...
            usedHeights(columnId) + ...
            components.heights(i) + topBorder + bottomBorder;
    end
    
    demonstration = canvas;
end
