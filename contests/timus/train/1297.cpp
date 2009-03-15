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

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;


int main()
{
    string s;
    int start,maxlen=0;
    cin>>s;
    foreach(mid,s)
    {
        // с центром в символе mid
        int left,right;
        left=right=mid;
        while(left>0 && right<s.size()-1 && s[left-1]==s[right+1])
        {
            left--;
            right++;
        }
        if(maxlen<right-left+1)
        {
            maxlen=right-left+1;
            start=left;
        }

        left=mid+1;
        right=mid;
        while(left>0 && right<s.size()-1 && s[left-1]==s[right+1])
        {
            left--;
            right++;
        }
        if(maxlen<right-left+1)
        {
            maxlen=right-left+1;
            start=left;
        }
    }
    cout<<s.substr(start,maxlen)<<endl;
    return 0;
}
