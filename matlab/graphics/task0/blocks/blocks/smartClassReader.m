function I = smartClassReader(seg)
    if(isfield(seg, 'classseg'))
        I = imread(seg.classseg);
    else
        I = seg.classsegReader();
    end
end

