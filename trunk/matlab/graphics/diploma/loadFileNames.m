function names = loadFileNames(source)
    fid = fopen(source);
    names = textscan(fid, '%s');
    names = names{:};
    fclose(fid);
end
