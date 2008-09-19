// null-terminated sequences of characters
#include <iostream>
using namespace std;

int main ()
{
    char question[] = "Please, enter your first name: ";
    char greeting[] = "Hello, ";
    /*
    тут кроютя великие траблы...
    во-первых если пользователь введёт >9 символов, то выйдем за пределы массива.
    возможен segfault, или, что ещё хуже - запись хз куда, и в дальнейшем мистические ошибки..
    к примеру если тут ввести длинное имя, то x изменится.
    */
    char yourname [10];
    int x=0;
    cout << question;
    cin >> yourname;
    cout << greeting << yourname << "!\n";
    if(x!=0)
        cout << "o_O Mysterious trouble!!! x=" << x << ", but must be 0" << endl;
    return 0;
}
