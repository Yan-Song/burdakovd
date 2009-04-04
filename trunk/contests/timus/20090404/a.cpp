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
#include <cassert>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

typedef string htype;

htype hash(const string& s) {return s;}

// htype hash(const string& s)
// {
//     i64 ans=0;
//     foreach(i,s)
//         ans += s[i]*(i+91)*113;
//     return ans;
// }

vector<string> readlist()
{
    char tt[1000];
    cin.getline(tt,300);
    scanf("\n");
    string ass(tt); ass=" "+ass+" ";
    //char* tk=strtok(ass,": ");
    vector<string> ans;
    int prev=ass.find_first_of(" "),found=ass.find_first_of(" \n",prev+1);
    while (found!=string::npos)
    {
        string ss=ass.substr(prev+1,found-prev-1);
        if(ss.size())
        {
            //cout<<(ass.substr(prev+1,found-prev-1))<<endl;
            ans.push_back((ass.substr(prev+1,found-prev-1)));
        }
        prev=found;
        found=ass.find_first_of(' ',found+1);
    }
    return ans;
}

bool cmp(const vector<htype>&a, const vector<htype>&b)
{
    return a.size()<b.size();
}

int main()
{
    map<string,vector<htype> > Q;
    int n,m;
    scanf("%d %d\n", &n);
    fo(i,0,n)
    {
        string word;
        cin>>word;
        word.resize(word.size()-1); // :
        //cout<<"W: "<<word<<endl;
        //cout<<word.size()<<endl;
        vector<string> slst=readlist();
        vector<htype> lst(slst.size());
        foreach(i,lst)
            lst[i]=hash(slst[i]);
        sort(ALL(lst));
        Q[word].resize(lst.size());
        copy(ALL(lst), Q[word].begin());
    }
    //cout<<"----------"<<endl;
    //cin>>m;
    scanf("%d\n", &m);
    fo(i,0,m)
    {
        //scanf("\n");
        vector<string> lst=readlist();
        scanf("\n");
        //showv(lst);
        sort(ALL(lst));
        //cout<<"------ solution begin"<<endl;
        vector<vector<htype> > t;

        foreach(i,lst)
            t.push_back(Q[lst[i]]);

        sort(ALL(t),cmp);
        assert(t.size()>0);
        vector<htype>& l0=t[0];
        //return 0;
        //cout<<l0.size()<<endl;
        //return 0;
        vector<htype> ans;
        vector<int> poss(t.size(),0);
        foreach(i,l0)
        {
            bool ok=true;
            foreach(j,t)
            {
                while(poss[j]<t[j].size() && t[j][poss[j]]<l0[i]) ++poss[j];
                
                if(poss[j]<t[j].size() && t[j][poss[j]]==l0[i])
                    continue;
                ok=false;
                break;
            }

            
            if(ok) ans.push_back(l0[i]);
            //if(ok) cout<<"l0["<<i<<"]="<<l0[i]<<endl;
            
            
        }
        if(ans.size()==0)
            cout<<"No solution.";
        else
            showv(ans);
        //cout<<"------ solution end"<<endl;
    }
    //cout<<"---------- solution begins"<<endl;

    return 0;
}
