#ifndef FIELDS_H
#define FIELDS_H

#include <string>

using namespace std;

class Field
{
public:
    string type, data;
    Field(const string& t, const string& v);
    // show
    string dump();
    string show();
};


#endif
