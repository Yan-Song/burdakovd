#include <iostream>
#include <assert.h>

using namespace std;

long a[30000], dp[30000];

#define D //cout

int main()
{
    long n, d;
    cin>>n>>d;
    for(long i=0; i<n; i++)
        cin>>a[i];
    long z=0, p=0;
    for(long i=0; i<n; i++)
    {
        z+=d;
        dp[i]=min(z,a[i]);
        z-=dp[i];
        p+=dp[i];
    }
    long long g=0, plan=0, dd;
    for(long i=n-1; i>=0; i--)
    {
        assert(plan>=0);
        // нам надо после этого месяца иметь готовыми `plan` яхт, понадобятся в будущих месяцах
        // продать в этом месяце dp[i] яхт
        // вроде как это возможно
        //D<<"plan="<<plan<<endl;
        plan += dp[i];
        //D<<"dp["<<i<<"]="<<dp[i]<<endl;
        // изготовим dd яхт
        dd = min(plan, d);
        // делаем заказ предыдущему месяцу
        plan -= dd;
        //D<<"next plan="<<plan<<endl;
        // оплачиваем хранение
        g += plan;
    }
    assert(plan==0);
    cout<<p<<" "<<g<<endl;
    return 0;
}
