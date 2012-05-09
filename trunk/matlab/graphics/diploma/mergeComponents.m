function Components = mergeComponents(c1, c2)    
    Components = struct();
    Components.areas = [c1.areas, c2.areas];
    Components.heights = [c1.heights, c2.heights];
    Components.widths = [c1.widths, c2.widths];
end
