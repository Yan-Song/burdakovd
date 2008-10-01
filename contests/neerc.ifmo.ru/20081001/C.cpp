#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int cols[101000], rows[101000], qrow[21000], sqrow[21000], ssrow[21000];
    int m, n, c, C, maxcol=0, maxrow=0, minimum, maximum;
    
    for(int i=0; i<21000; i++)
        qrow[i]=sqrow[i]=ssrow[i]=0;
    
    cin>>m>>n>>c>>C;
    
    for(int i=0; i<m; i++)
    {
        scanf("%d", &cols[i]);

        if(cols[i]>maxcol) maxcol=cols[i];
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &rows[i]);
        qrow[rows[i]] += 1;
        if(rows[i]>maxrow) maxrow=rows[i];
    }
    
    if(maxcol!=maxrow)
    {
        cout<<"Impossible\n";
        return 0;
    }

    // o_O так вот
    sqrow[0] = qrow[0];
    
    // интегральчики
    for(int i=1; i<21000; i++)
    {
        sqrow[i]=sqrow[i-1]+qrow[i];
        ssrow[i]=ssrow[i-1]+i*qrow[i];
    }
    
    maximum = 0;
    for(int i=0; i<m; i++)
        maximum += ssrow[cols[i]] + cols[i] * (n - sqrow[cols[i]]);


    // теперь придётся искать минимум......
    // это оказалось проще чем я предполагал
    minimum = 0;
    for(int i=0; i<21000; i++)
        minimum += i * max(qcol[i], qrow[i]);
    
    cout<<"Minimum: "<<minimum*c<<", maximum: "<<maximum*C<<endl;
    
    return 0;
}
