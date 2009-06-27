#ifndef FORMATTER_CPP
#define FORMATTER_CPP

#include "formatter.hpp"
#include "macro.hpp"
#include <algorithm>

char filler = ' ';

string stretch(string text, int width)
{
    if(text.size()<=width)
        return text + string(width-text.size(), filler);
    else
        return (text.substr(0, width-3) + "...").substr(0, width);
}

string format_table(int width, Rows data)
{
    if(data.empty()) return "(Empty result)";
    int nrows = data.size();
    int ncols = data[0].size();
    if(ncols==0) return "(Empty result)";

    vi colwidths(ncols, 0);
    foreach(i, data)
        foreach(j, data[i])
        {
            colwidths[j] = max(colwidths[j], int(data[i][j].show().size()));
        }
    
    int required = width - 3 * ncols - 1;
    
    vi v = colwidths;
    sort(ALL(v), greater<int>());
    
    int sum = 0;
    foreach(i,v)
        sum += v[i];
    int lim = v[0], pos = 0;
    while(sum>required)
    {
        --lim;
        while(pos<ncols && v[pos]>lim) ++pos;
        sum -= pos;
    }
    
    sum += 3 * ncols + 1;
    
    string line(sum, '=');
    char border = '|';
    char br = '\n';
    string ans = line + br;
    foreach(i, data)
    {
        Row& row = data[i];
        ans += border;
        foreach(j, row)
        {
            Field& field = row[j];
            ans += filler + stretch(field.show(), min(colwidths[j], lim)) + filler;
            ans += border;
        }
        ans += br;
    }
    ans += line;
    return ans;
}


#endif
