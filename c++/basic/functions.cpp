// function example
#include <iostream>
using namespace std;

int subtraction (int a, int b)
{
    int r;
    r=a-b;
    return (r);
}

// первый способ, передаются указатели на a, b, c
// *a, *b, *c are int;
// передавать в функцию как duplicate(&z, &y, &z)
void duplicate (int *a, int *b, int *c)
{
    *a *= 2;
    *b *= 2;
    *c *= 2;
}

// второй способ, передаются a, b, c по ссылке, читать тут: http://faqs.org.ru/progr/c_cpp/cpp_lite.htm#s8p1
// но! работать с ними как с обычными переменными, не указателями.
// и передавать в функцию как duplicate2(z, y, z)
// работает только в C++ (не C)
void duplicate2 (int& a, int& b, int& c)
{
    a *= 2;
    b *= 2;
    c *= 2;
}

void printarray (int arg[], int length) {
    for (int n=0; n<length; n++)
        cout << arg[n] << " ";
    cout << "\n";
}

// In a function declaration it is also possible to include multidimensional arrays.
// The format for a tridimensional array parameter is:
// 
//         base_type[][depth][depth]
// 
// for example, a function with a multidimensional array as argument could be:
// 
//         void procedure (int myarray[][3][4])

int main ()
{
    int x=5, y=3, z;
    z = subtraction (7,2);
    cout << "The first result is " << z << '\n';
    cout << "The second result is " << subtraction (7,2) << '\n';
    cout << "The third result is " << subtraction (x,y) << '\n';
    z= 4 + subtraction (x,y);
    cout << "The fourth result is " << z << '\n';
    x=1; y=10; z=100;
    duplicate (&x, &y, &z);
    cout << "[duplicate] x=" << x << ", y=" << y << ", z=" << z << endl;
    duplicate2 (x, y, z);
    cout << "[duplicate2] x=" << x << ", y=" << y << ", z=" << z << endl;
    int firstarray[] = {5, 10, 15};
    int secondarray[] = {2, 4, 6, 8, 10};
    printarray (firstarray,3);
    printarray (secondarray,5);
    return 0;
}
