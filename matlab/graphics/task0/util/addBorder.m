function result = addBorder(rgb, height, width)
    h = size(rgb, 1);
    w = size(rgb, 2);
    dh = height - h;
    dw = width - w;
    top = fix(dh / 2);
    bottom = dh - top;
    left = fix(dw / 2);
    right = dw - left;
    
    intensity = 255;
    
    result = [
        uint8(ones(top, width, 3) * intensity);
        uint8(ones(h, left, 3) * intensity) rgb uint8(ones(h, right, 3) * intensity);
        uint8(ones(bottom, width, 3) * intensity)
        ];
end
