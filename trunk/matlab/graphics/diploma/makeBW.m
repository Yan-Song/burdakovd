function bw = makeBW( original )
    if size(original, 3) == 3
        gray = rgb2gray(original);
    elseif size(original, 3) == 1
        gray = original;
    else
        error('Bad image');
    end
    bw = im2bw(gray, graythresh(gray));
end
