function cached = cacheGet(functionName, args, key, policy)
    
    assert(policy.use, 'Cache disabled');

    hash = num2str(str2hash(key));
    fileName = [policy.path functionName '.' hash '.mat'];
    
    if fileExists(fileName)
        loaded = load(fileName);
        if isequal(loaded.key, key) && isequal(loaded.args, args)
            cached = loaded.value;
            return;
        else
            fprintf(1, 'File %s is corrupted or hash collision detected.\n', fileName);
        end
    end
    
    cached = {};
end

function exists = fileExists(name)
    exists = exist(name, 'file') == 2;
end
