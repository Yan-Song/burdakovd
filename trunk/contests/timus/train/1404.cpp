#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin>>s;
    char key=5;
    for(int i=0; i<s.size(); i++)
    {
        char c=s[i]-'a';
        c+=26-key;
        c%=26;
        printf("%c", c+'a');
        key=s[i]-'a';
    }
    cout<<endl;
    return 0;
}
