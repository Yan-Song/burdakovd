#include <iostream>
#include <string>

using namespace std;

int main()
{
    string text;
    getline(cin, text);
    string phone="abcdefghijklmnopqrstuvwxyz#.,! ##";
    int cost=0;
    for(int i=0; i<text.length(); i++)
        cost=cost+phone.find(text[i])%3+1;
    cout<<cost<<endl;
    return 0;
}
