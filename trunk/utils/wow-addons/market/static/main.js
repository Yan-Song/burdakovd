gdata = {}

function toggle_visibility(id) {
    var e = document.getElementById(id);
    if(e.style.display == 'block')
        e.style.display = 'none';
    else
        e.style.display = 'block';
};

drawGraph =
    function(selector, columns, data, options) {
        var answers = [];

        for(var j=0; j<columns.length; j++)
        {
            answers.push(columns[j][1]);
            answers[j].data = [];
        }

        for(var i=0; i<data.length; i++)
        {
            for(var j=0; j<columns.length; j++)
            {
                if ((null == data[i]) || (null==data[i][1][j]))
                    answers[j].data.push(null);
                else
                    answers[j].data.push([data[i][0]*1000, data[i][1][columns[j][0]]]);
            }

            gdata.answers = answers;
        }
        gdata.answers = answers;
        $.plot($(selector), answers, options);
    };

division = function(a,b)
{
    if(0==b) return null;
    else return a/b;
}
    
itemhelper = function(g)
    {
        for(var j=0; j<g.length; j++)
        {
            if(null==g[j]) continue;
            g[j][1].push(division(g[j][1][2], g[j][1][0]));
            g[j][1].push(division(g[j][1][3], g[j][1][1]));
            g[j][1].push(division(100.0*g[j][1][0], (g[j][1][4]+g[j][1][0])));
        }
        return g;
    };

goldformatter = function (v, axis) {
    return v.toFixed(axis.tickDecimals) +"г";
}

pformatter = function (v, axis) {
    return v.toFixed(axis.tickDecimals) +"%";
}
