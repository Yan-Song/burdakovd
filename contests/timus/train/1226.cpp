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

#define LETTER(c) (((c)<='z'&&(c)>='a')||((c)>='A'&&(c)<='Z'))

using namespace std;

typedef long long i64;
typedef vector<int> VI;


int main()
{
    stack<char> word;
    char c;
    while(scanf("%c", &c)!=EOF)
    {
        if(LETTER(c)) word.push(c);
        else
        {
            while(!word.empty())
            {
                printf("%c", word.top());
                word.pop();
            }
            printf("%c", c);
        }
    }
    while(!word.empty())
    {
        printf("%c", word.top());
        word.pop();
    }
    return 0;
}
