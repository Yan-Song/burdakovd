// i/o example

#include <iostream>
using namespace std;

// The endl manipulator produces a newline character, exactly as the insertion of '\n' does, but it also has an
//additional behavior when it is used with buffered streams: the buffer is flushed. Anyway, cout will be an unbuffered
//stream in most cases, so you can generally use both the \n escape character and the endl manipulator in order to
//specify a new line without any difference in its behavior.

int main ()
{
    int i;
    cout << "Please enter an integer value: ";
    cin >> i;
    cout << "The value you entered is " << i;
    cout << " and its double is " << i*2 << ".\n";

    string mystr;
    cout << "What's your name? ";
    cin >> mystr;
    cout << "Hello " << mystr << ".\n";
    cout << "What is your favorite team? ";
    cin >> mystr;
    cout << "I like " << mystr << " too!\n";
    if(true)
        cout << ":)\n";
    return 0;
}
