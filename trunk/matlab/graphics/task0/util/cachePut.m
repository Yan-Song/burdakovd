function cachePut(functionName, args, key, value, policy)
    
    assert(policy.use, 'Cache disabled');

    hash = num2str(str2hash(key));
    fileName = [policy.path functionName '.' hash '.mat'];
    
    saved.args = args;
    saved.key = key;
    saved.value = value; %#ok<STRNU>
    
    
    if exist(fileName, 'file')
        delete(fileName);
    end
    
    fileNameTmp = [fileName '.tmp'];
    save(fileNameTmp, '-struct', 'saved', 'args', 'key', 'value');
    movefile(fileNameTmp, fileName);
    
    fprintf(1, '#');
end
