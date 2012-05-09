function buildReports(options, dbloader, wildcard)
    
    reportFileName = 'report.txt';
    reportFileNameTmp = [reportFileName '.tmp'];
    
    rfid = fopen(reportFileNameTmp, 'w');
    
    report = @(varargin) tee(rfid, varargin{:});
    
    cases = dir([options.resultsPath '/' wildcard]);
    cases = sort({cases.name});
    inverted = cellfun(@(s) regexprep(s, '([^@]+)@(.+)', '$2_$1'), cases, 'UniformOutput', false);
    [~, perm] = sort(inverted);
    cases = cases(perm);
    
    for caseId = 1 : length(cases)
        caseName = cases{caseId};
        
        if(not(strcmp(caseName, '.') || strcmp(caseName, '..')))
            tagPath = sprintf('%s/%s/db_tag.txt', options.resultsPath, caseName);
            if exist(tagPath, 'file')
                fid = fopen(tagPath);
                tag = textscan(fid, '%s');
                tag = tag{1};
                tag = tag{:};
                fclose(fid);
            else
                report('Case %s has not db_tag.txt, assuming VOC-generic\n', caseName);
                tag = 'p07generic';
            end
            buildReport(options, dbloader(tag), caseName, strcmp(tag, 'p07generic'), report);
        end
    end
    
    fclose(rfid);
    if exist(reportFileName, 'file')
        delete(reportFileName);
    end
    movefile(reportFileNameTmp, reportFileName);
    
    fprintf(1, 'Report has been written into %s\n', reportFileName);
end


function tee(fid, varargin)
    for id = [1 fid]
        fprintf(id, varargin{:});
    end
end
