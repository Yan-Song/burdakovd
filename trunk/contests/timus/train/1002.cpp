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

#define inf 1000
#define mset(block,value) memset(block,value,sizeof(block))

using namespace std;

int main()
{
    while(true)
    {
        string number;
        cin>>number;
        if(number=="-1") return 0;
        int n;
        cin>>n;
        string letters[10] = {"oqz", "ij", "abc", "def", "gh", "kl", "mn", "prs", "tuv", "wxy"};
        int invletters[260];
        mset(invletters, -1);
        for(int i=0; i<10; i++)
            for(int j=0; j<letters[i].size(); j++)
                invletters[letters[i][j]]=i;
        vector<string> words;
        for(int i=0; i<n; i++)
        {
            string word;
            cin>>word;
            words.push_back(word);
        }
        ////////
        int dp[200], used_words[200];
        dp[0] = 0;
        for(int i=1; i<=number.size(); i++)
        {
            dp[i] = inf;
            for(int j=0; j<words.size(); j++)
                if(words[j].size()<=i)
                {
                    int offset = number.size()-i;
                    bool ok=true;
                    for(int k=0; k<words[j].size(); k++)
                        if(number[offset+k]-'0'!=invletters[words[j][k]])
                        {
                            ok = false;
                            break;
                        }
                    //cout<<"ok="<<ok<<" for dp["<<i<<"] and word "<<words[j]<<endl;
                    if(ok&&dp[i-words[j].size()]+1<dp[i])
                    {
                        dp[i] = dp[i-words[j].size()]+1;
                        used_words[i] = j;
                    }
                }
        }
        n = number.size();
        if(dp[n]<1000)
        {
            //cout<<dp[n]<<endl; //DEBUG
            while(n>0)
            {
                int j=used_words[n];
                n-=words[j].size();
                cout<<words[j]<<" ";
            }
            cout<<endl;
            if(n<0)
                cout<<"O_o?"<<endl;
        }
        else cout<<"No solution."<<endl;
    }
}
