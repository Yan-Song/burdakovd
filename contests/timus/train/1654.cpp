#include <iostream>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

int main()
{
    char msg[250000];
    stack<char*> s;
    cin>>msg;
    char* q=msg;
    while(*q != 0) // пока не конец строки
    {
        if( !s.empty() && (*(s.top())==*q) ) // если на вершине стека есть пара текущему символу
            {
                *q = '-';
                *(s.top()) = '-'; // вычёркиваем оба, 
                s.pop(); // и убираем из стека
            }
        else s.push(q); // иначе сохраняем текущий символ в стек
        q++; // переход к следующему символу
    }
    // cout<<msg<<endl; // в таком виде даже красивее получается и нагляднее
    q=msg;
    while(*q != 0)
    {
        if(*q != '-') cout<<(*q);
        q++;
    }
    cout<<endl;
    return 0;
}
