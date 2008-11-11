#include <iostream>
#include <string>

using namespace std;

int main()
{
    // соль в том, что так как _известно_, что каких-то купюр больше половины,
    // то можно искать каждую цифру ответа отдельно (т.к. для i-й позиции
    // также будет верно, что какая-то цифра в этой позиции будет встречаться более половины раз,
    // и это будет i-я цифра искомого числа)
    // // пользуюсь двоичной системой
    int n;
    cin>>n;
    int dig[32];
    for(int i=0; i<32; i++) dig[i]=0;
    for(int i=0; i<n; i++)
    {
        int _;
        cin>>_;
        for(int j=0; j<32; j++)
            if((_>>j)&1) dig[j]++;
    }
    int res=0;
    for(int i=31; i>=0; i--)
    {
        res<<=1;
        //printf("dig[%d]=%d\n", i, dig[i]);
        //cout<<"[i="<<i<<"] res="<<res;
        if(dig[i]*2>n) // если в i-й позиции преобладала единица
            res+=1;
        //cout<<", now res="<<res<<endl;
    }
    cout<<res<<endl;
    return 0;
}
