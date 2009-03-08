#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,x) fo(i,start,x.size())
#define foreach(i,x) forsz(i,0,x)
#define showv(v) foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

#define UNDEFINED 0

int main()
{
    /*
    очевидно, что если в графе есть изолированные вершины, то ответ - 0

    рассмотрим случай, когда изолированных нет.
    
    определившаяся вершина - это человек, которому назначена группа.
    изначально никому ничего не назначено
    
    ИНВАРИАНТ1: нет определившихся вершин,
    все ребра из которых ведут в вершины той же группы
    что и они сами
    ИНВАРИАНТ2:
    любая вершина группы 2 имеет связь хотя бы с одной вершиной группы 1
    
    изначально оба верны, т.к. нет определившихся вершин.
    
    для каждой неопределившейся вершины i:
        если можно отправить её в первую группу,
        и инвариант1 при этом не нарушится - делаем это,                (1)
        иначе отправляем её во вторую группу.

        покажем, что в случае "иначе" инварианты не нарушатся.
    
        все вершины соседние с i уже насыщены
        (второй группы т.к. был верен инвариант2,
        а первой группы т.к. они соединены с вершиной i,
        которую только что отнесли к группе 2) и для них инвариант1 верен
        для текущей вершины инвариант2 верен, так как иначе все её соседи
        принадлежали бы к группе 2, и мы бы отнесли её к первой группе по (1)

        инвариант1 для этой вершины следует из выполненности инварианта2

        таким образом, вершина i определена, и при этом оба инварианта сохранены

    в конце, если все вершины определились, и выполнены оба инварианта
    то разбиение удовлетворяет заданию

    ///////////////////////////////

    тут ещё и какая-то муть при вводе,
    то есть что-то типа того, что если в вводе указано что первый друг второго,
    а обратное не указано, то оно всё равно подразумевается
    */
    int n;
    cin>>n;
    vector< vector<int> > f(n);
    vector<bool> happy(n,false);
    vector<int> left(n,0);
    vector<int> left2(n,0);
    vector<int> group(n,UNDEFINED);
    vector< vector<bool> > A(n, vector<bool>(n, false));
    foreach(i,A)
    {
        while(true)
        {
            int _;
            cin>>_;
            if(_==0) break;
            A[i][_-1]=A[_-1][i]=true;
        }
    }
    foreach(i,A)
        foreach(j,A[i])
            if(A[i][j])
            {
                f[i].push_back(j);
                ++left[i];
            }
    foreach(i,f)
    {
        if(f[i].empty())
        {
            cout<<0<<endl;
            return 0; // есть изолированный человек
        }
    }
    vector<int> ans;
    foreach(i,f)
    {
        group[i]=1;
        // проверяем [1]
        foreach(j,f[i])
            if(!happy[f[i][j]]&&group[f[i][j]]==1&&left[f[i][j]]==1)
            {
                group[i]=2;
                break;
            }
        if(left[i]==0&&group[i]==1)
        {
            group[i]=2;
            foreach(j,f[i])
                if(group[f[i][j]]==2)
                {
                    group[i]=1;
                    break;
                }
        }
        foreach(j,f[i])
        {
            --left[f[i][j]];
            if(group[f[i][j]]&&group[f[i][j]]!=group[i])
            {
                happy[f[i][j]]=true;
                happy[i]=true;
            }
        }
        if(group[i]==1)
            ans.push_back(i);
    }
    foreach(i, happy) if(!happy[i]) throw i;
    foreach(i, left) if(left[i]) throw i;
    cout<<ans.size()<<endl;
    foreach(i,ans)
        cout<<(i?" ":"")<<ans[i]+1;
    cout<<endl;
    return 0;
}
