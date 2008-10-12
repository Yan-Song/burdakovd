#include <iostream>

using namespace std;

// The first line of input contains integer N (1 ≤ N ≤ 31).
// The other N successive lines contain integers D1, D2, …, DN. 1 ≤ D1, D2, …, DN ≤ 3.

int D[40];

int count(int n)
// можно оптимизировать кэшированием, но в данной задаче это не нужно
{
    if(n==0) return 0;
    else return 1+2*count(n-1);
}

int solve(int n, int source, int destination, int tmp) // recursive
// функция возвращает количество ходов, за которые при оптимальной стратегии игры "Ханой"
// кольца (с n-го до 1-го) бы оказались в положении, описанном в D[], при условии что сначала они были на source,
// должны попасть на destination, и в качестве временного стержня используется tmp
// рекурсивный вызов только один, и n-- на каждом вызове, => число запусков ф-ии = n.
{
    if(n==0) return 0; // очевидно
    else if(D[n]==source)
        // если нижнее кольцо ещё не перенесено, значит мы пока только переносили верхние на tmp
        return solve(n-1, source, tmp, destination);
    else if (D[n]==destination)
        // бОльшее кольцо уже перенесено, значит уже возвращаем мелкие на него
        {
            int t=solve(n-1, tmp, destination, source);
            // если такая ситуация могла возникнуть, то считаем, иначе -1
            return (t==-1) ? t : count(n-1)+1+t;
        }
    // нижний диск каким-то образом попал на tmp, такого не должно было быть
    else return -1;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++) cin>>D[i];
    cout<<solve(n, 1, 2, 3)<<endl;
    return 0;
}