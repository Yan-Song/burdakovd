#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,container) fo(i,start,container.size())
#define foreach(i,container) forsz(i,0,container)
#define showv(v) foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(container) container.begin(),container.end()

using namespace std;

typedef long long i64;


int main()
{
    i64 n;
    cin>>n;
    vector<int> answer;
    while(n>1)
    {
        int l=n/2;
        answer.push_back(l);
        n-=l;
    }
    cout<<answer.size()<<endl;
    showv(answer);
    return 0;
}
