#include <iostream>

using namespace std;

#define N 65536


int main()
{
    int n1, n2, _;
    cin>>n1;
//     \todo: почему первым способом WA 5?
//     bool x[N*2];
//     for(int i=-N; i<N; i++) x[i+N] = false;
//     for(int i=0; i<n1; i++)
//     {
//         cin>>_;
//         x[_+N] = true;
//     }
//     cin>>n2;
//     for(int i=0; i<n2; i++)
//     {
//         cin>>_;
//         _=10000-_;
//         if((_>=-N)&&(_<N)&&x[_+N])
//         {
//             cout<<"YES"<<endl;
//             return 0;
//         }
//     }
    //******
    int x[50000];
    for(int i=0; i<n1; i++)
        cin>>x[i];
    cin>>n2;
    int p=0;
    for(int i=0; i<n2; i++)
    {
        cin>>_;
        while((p<n1)&&(x[p]+_<=10000))
        {
            //cout<<x[p]<<"+"<<_<<endl;
            if(x[p]+_==10000)
            {
                cout<<"YES"<<endl;
                return 0;
            }
            p++;
        }
    }
    //******
    cout<<"NO"<<endl;
    return 0;
}
