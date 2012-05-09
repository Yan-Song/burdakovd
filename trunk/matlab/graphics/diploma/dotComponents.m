function Components = dotComponents(n)
    Components = struct();
    Components.rows = num2cell(ones(1, n));
    Components.cols = Components.rows;
    Components.areas = Components.rows;
    Components.heights = ones(1, n);
    Components.widths = ones(1, n);
end
