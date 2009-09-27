#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cassert>
 
#pragma comment(linker, "/STACK:16777216")
 
#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cerr<<(#x)<<" = "<<(x)<<endl
#define adebug(x,n) fo(i,0,n) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()
 
using namespace std;
 
typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<i64> v64;
typedef vector<i64> vv64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
 
const double pi=2*acos(0.0);
const int inf=1<<25;

int main()
{
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int t;
    cin>>t;
    for(int cas=1; cas<=t; ++cas)
    {
        int r,c,f;
        cin>>r>>c>>f;

        vector<string> a;

        vvi nh(r+3, vi(c+2));

        a.push_back(string(c+2, '#'));

        for(int i=0; i<r; ++i)
        {
            string _;
            cin>>_;
            assert(_.size() == c);
            a.push_back('#' + _ + '#');
        }

        a.push_back(string(c+2, '#'));
        a.push_back(string(c+2, '#'));

        vdebug(a);

        for(int cc=0; cc<c+2; ++cc)
        {
            int inh = r+2;
            for(int hh=r+2; hh>=0; --hh)
            {
                nh[hh][cc] = inh;
                if(a[hh][cc] == '#')
                    inh = hh;
            }
        }
        
        vvi digs(r+2, vi(c+2, inf)); // за сколько копаний можно достичь этой клетки
        
        int startrow = nh[1][1]-1;
        digs[startrow][1] = 0;
        a[startrow][1] = 'x';

        queue<pii> q;
        q.push(pii(startrow,1));

        while(!q.empty())
        {
            int cur_r = q.front().first;
            int cur_c = q.front().second;
            q.pop();

            assert(a[cur_r][cur_c] == 'x');
            assert(a[cur_r+1][cur_c] != '.');


            // move left
            if(a[cur_r][cur_c-1]=='.')
            {
                int left_r = nh[cur_r][cur_c-1] - 1; // куда упаду
                assert(a[left_r][cur_c-1] != '#');
                int left_f = left_r - cur_r;
                if(left_f<=f)
                    if(a[left_r][cur_c-1] != 'x') // не был там
                    {
                        assert(a[left_r][cur_c-1] == '.');
                        a[left_r][cur_c-1] = 'x';
                        digs[left_r][cur_c-1] = digs[cur_r][cur_c];
                        q.push(pii(left_r, cur_c-1));
                    }
            }

            // move right
            if(a[cur_r][cur_c+1]=='.')
            {
                int right_r = nh[cur_r][cur_c+1] - 1; // куда упаду
                assert(a[right_r][cur_c+1] != '#');
                int right_f = right_r - cur_r;
                if(right_f<=f)
                    if(a[right_r][cur_c+1] != 'x') // не был там
                    {
                        assert(a[right_r][cur_c+1] == '.');
                        a[right_r][cur_c+1] = 'x';
                        digs[right_r][cur_c+1] = digs[cur_r][cur_c];
                        q.push(pii(right_r, cur_c+1));
                    }
            }

            // dig (downleft)

            if(a[cur_r+1][cur_c-1]=='#' && a[cur_r][cur_c-1]!='#' && (cur_r == r-1 || a[cur_r+2][cur_c-1]=='.'))
            {
                int down_r = nh[cur_r+1][cur_c-1] - 1;
                assert(cur_r == r-1 || a[down_r][cur_c-1] != '#');

                int down_f = down_r - cur_r;

                assert(cur_r == r-1 || down_f>1);

                if(down_f <= f)
                {
                    if(a[down_r][cur_c-1] != 'x')
                    {
                        assert(cur_r == r-1 || a[down_r][cur_c-1] == '.');
                        a[down_r][cur_c-1] = 'x';
                        digs[down_r][cur_c-1] = digs[cur_r][cur_c] + 1;
                        q.push(pii(down_r, cur_c-1));
                    }
                }

            }

             // dig (downright)

            if(a[cur_r+1][cur_c+1]=='#' && a[cur_r][cur_c+1]!='#' &&(cur_r == r-1 || a[cur_r+2][cur_c+1]=='.'))
            {
                int down_r = nh[cur_r+1][cur_c+1] - 1;
                assert(cur_r == r-1 || a[down_r][cur_c+1] != '#');

                int down_f = down_r - cur_r;

                assert(cur_r == r-1 || down_f>1);

                if(down_f <= f)
                {
                    if(a[down_r][cur_c+1] != 'x')
                    {
                        assert(cur_r == r-1 || a[down_r][cur_c+1] == '.');
                        a[down_r][cur_c+1] = 'x';
                        digs[down_r][cur_c+1] = digs[cur_r][cur_c] + 1;
                        q.push(pii(down_r, cur_c+1));
                    }
                }

            }

        }

        int mm = inf;
        for(int cc=0; cc<=c; ++cc)
            mm = min(mm, digs[r][cc]);

        if(mm!=inf)
            cout<<"Case #"<<cas<<": Yes "<<mm<<endl;
        else
            cout<<"Case #"<<cas<<": No"<<endl;


    }
    return 0;
}
