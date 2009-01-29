#include <iostream>
#include <string>
#include <cmath>
#define M 1000
#define FC 4

using namespace std;

int main()
{
    int n;
    cin>>n;
    string names[M];
    string fac[M];
    getline(cin, names[0]); // trash
    for(int i=0; i<n; i++)
    {
        getline(cin, names[i]);
        //cout<<"name: "<<names[i]<<endl;
        getline(cin, fac[i]);
        //cout<<"fac: "<<fac[i]<<endl;
    }
    string fl[FC] = {"Slytherin", "Hufflepuff", "Gryffindor", "Ravenclaw"};
    for(int i=0; i<FC; i++)
    {
        cout<<fl[i]<<":"<<endl;
        for(int j=0; j<n; j++)
            if(fac[j]==fl[i])
                cout<<names[j]<<endl;
        cout<<endl;
    }

    //string nn[4] = {"one1", "two2", "three3", "four4"};
    //for(int i=0; i<4; i++)
    //    cout<<nn[i]<<endl;
    return 0;
}
