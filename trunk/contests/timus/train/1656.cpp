#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#define height int
// или double? в условии ничего не сказано

using namespace std;

int abs(int x)
{
    if(x>0) return x;
    else return -x;
}

int main()
{
    /*
        по сути надо расставить так:
    
    GFEDEFG
    FEDCDEF
    EDCBCDE
    DCBABCD
    EDCBCDE
    FEDCDEF
    GFEDEFG
    
    Солдаты разбиты на группы, так чтобы в A - самый высокий солдат, в B - менее высокие и т.д.
    Заполнить квадрат можно в один проход n^2, но т.к. n мало то не буду париться и сделаю n^3
    */
    
    int n;
    height a[100];
    cin>>n;
    for(int i=0; i<n*n; i++)
        cin>>a[i];
    // сортировать по убыванию роста
    for(int i=0; i<n*n; i++)
        for(int j=0; j<i; j++)
            if(a[j]<a[i])
            {
                height _ = a[i];
                a[i] = a[j];
                a[j] = _;
            }
    int m = n/2; // центр
    height q[10][10]; // итоговая таблица
    int snum=0; // номер текущего солдата
    /* изменение dist - это изменение букв A..G на картинке выше.
    Начиная с буквы A и дальше, ищем в квадрате клетки,
    где должна стоять эта буква и ставим туда самого высокого
    из оставшихся солдатов */
    for(int dist=0; dist<n; dist++) 
        for(int x=0; x<n; x++)
            for(int y=0; y<n; y++)
                if(abs(x-m)+abs(y-m)==dist)
                    q[x][y] = a[snum++];
    // вывод
    for(int y=0; y<n; y++)
    {
        for(int x=0; x<n; x++)
            cout<<q[x][y]<<" ";
        cout<<endl;
    }
    return 0;
}
