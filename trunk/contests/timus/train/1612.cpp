#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

bool isLetter(char c)
{
    return (c>='a')&&(c<='z');
}

int getWordCount(string s, string x)
{
    int ans=0, pos=0, f, l=x.size();
    do
    {
        f = s.find(x, pos);
        if(f==string::npos) return ans;
        pos = f+l; // первый символ после этого вхождения
        if(((f==0)||!isLetter(s[f-1])) && // до этого слова нет букв и..
             ((pos>=s.size())||!isLetter(s[pos]))) // ...и после него
            ans++;
    }
    while(true);
}

int main()
{
    int trams=0, trolls=0;
    string line;

    // проверяем как работает >> - оказывается читает до пробела, знаки препинания тоже читает
    //cin>>line;
    //cout<<"line="<<line<<endl;

    while(cin>>line)
    {
        trams += getWordCount(line, "tram");
        trolls += getWordCount(line, "trolleybus");
    }

    //cout<<"trams="<<trams<<" trolls="<<trolls<<endl;
    
    if(trams>trolls) line="Tram";
    else if(trams<trolls) line="Trolleybus";
    else line="Bus";
    
    cout<<line<<" driver"<<endl;
    
    return 0;
}
