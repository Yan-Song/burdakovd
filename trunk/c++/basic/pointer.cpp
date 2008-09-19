// my first pointer
#include <iostream>
using namespace std;

// When declaring pointers we may want to explicitly specify which variable we want them to point to:
// 
// int number;
// int *tommy = &number;
// 
// The behavior of this code is equivalent to:
// 
// int number;
// int *tommy;
// tommy = &number;
// 
// When a pointer initialization takes place we are always assigning the reference value to where
// the pointer points (tommy), never the value being pointed (*tommy). You must consider that at the moment of
// declaring a pointer, the asterisk (*) indicates only that it is a pointer, it is not the dereference operator
// (although both use the same sign: *). Remember, they are two different functions of one sign.
// Thus, we must take care not to confuse the previous code with:
// 
// int number;
// int *tommy;
// *tommy = &number;

// As in the case of arrays, the compiler allows the special case that we want to initialize the content at
// which the pointer points with constants at the same moment the pointer is declared:
// 
// char * terry = "hello";
// In this case, memory space is reserved to contain "hello" and then a pointer to the first character of
// this memory block is assigned to terry.
// *(terry+4) is equal to terry[4]

int main ()
{
    int firstvalue, secondvalue;
    // put one asterisk per pointer!!
    int *mypointer, *anotherpointer;
    // next line can segfault, because mypointer has not been initialized
    // cout << "mypointer=" << mypointer << ", *mypointer=" << *mypointer << endl;
    mypointer = &firstvalue;
    *mypointer = 10;
    mypointer = &secondvalue;
    *mypointer = 20;
    cout << "firstvalue is " << firstvalue << endl;
    cout << "secondvalue is " << secondvalue << endl;
    return 0;
}
