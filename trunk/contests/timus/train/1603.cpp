#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

string table[4];

bool dfs(int i, int j, const char *c)
{
    if(*c==0) return true;
    if(i<0||j<0||i>3||j>3) return false;
    if(table[i][j]!=*c) return false;
    table[i][j] = '*'; // чтоб исключить самопересечения
    bool ans=dfs(i+1,j,c+1)||dfs(i-1,j,c+1)||dfs(i,j+1,c+1)||dfs(i,j-1,c+1);
    table[i][j] = *c;
    return ans;
}

bool solve(const string& word)
{
    const char* c=word.c_str();
    fo(i,0,4)
        fo(j,0,4)
            if(dfs(i,j,c)) return true;
    return false;
}

int main()
{
    fo(i,0,4)
        cin>>table[i];
    int n;
    cin>>n;
    vector<string> words;
    fo(i,0,n)
    {
        string s;
        cin>>s;
        words.push_back(s);
    }
    foreach(i, words)
        cout<<words[i]<<": "<<(solve(words[i])?"YES":"NO")<<endl;
    return 0;
}
