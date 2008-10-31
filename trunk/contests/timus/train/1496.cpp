#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<string,int> t;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        string s;
        cin>>s;
        // If x does not match the key of any element in the container, the function inserts a new element with that
        // key and returns a reference to its mapped value. Notice that this always increases the map size by one,
        // even if no mapped value is assigned to the element (the element is constructed using its default constructor).
        // http://www.cplusplus.com/reference/stl/map/operator%5B%5D.html
        // вроде как "default constructor" для int это 0, хотя нигде не видел пока этого утверждения.
        t[s]++;
    }
    for (map<string,int>::iterator it=t.begin(); it!=t.end(); it++)
        if(it->second > 1)
            cout<<it->first<<endl;
    return 0;
}
