#include <iostream>
#include <vector>
#include <string>

#include "table.hpp"
#include "macro.hpp"
#include "socket.hpp"
#include "fields.hpp"
#include "exceptions.hpp"
#include "formatter.hpp"
#include <stdlib.h>
#include <sstream>

int randint(int min, int max)
// random x: min <= x < max
{
    if(min==max) return min;
    return min + abs(random()) % abs(max - min);
}

using namespace std;

int main()
{
    cout<<string("abcd").substr(2, string::npos)<<endl;
    return 0;
    srandom(getpid());
    int ncols = randint(0,10);
    int nrows = randint(0,30);
    int z = randint(1000,2000);
    Rows testdata;
    fo(i,0,nrows)
    {
        Row testrow;
        fo(j,0,ncols)
            if(z*j%1001%11%3)
            {
                int len = randint(0,20);
                string ans = "";
                fo(k,0,len)
                    ans += 'a'+randint(0,26);
                testrow.push_back(Field("STRING", ans));
            }
            else
            {
                double v = 1.0 / z * randint(0,1000000);
                stringstream s;
                s<<v;
                testrow.push_back(Field("NUM", s.str()));
            }
        testdata.push_back(testrow);
    }
    cout<<format_table(100, testdata)<<endl;
    return 0;
}
