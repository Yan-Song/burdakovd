#include <iostream>
#include <vector>
#include <string>

#include "table.hpp"
#include "macro.hpp"
#include "socket.hpp"
#include "fields.hpp"
#include "exceptions.hpp"

using namespace std;

int main()
{
    vector<string> fields, ft;
    fields.push_back("A");
    fields.push_back("B");
    fields.push_back("Q");
    ft.push_back("integer");
    ft.push_back("string");
    ft.push_back("integer");
    Table test(".", "testtable");
    test.save();
    
    return 0;
}
