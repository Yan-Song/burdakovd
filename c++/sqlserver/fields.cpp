#ifndef FIELDS_CPP
#define FIELDS_CPP
#include "fields.hpp"
#include "exceptions.hpp"
#include <sstream>
#include <cassert>
#include <iostream>


Field::Field(const string& t, const string& v): type(t), data(v) {};

string Field::dump()
{
    return data;
}

string Field::show()
{
    if(type=="STRING")
    {
        return data;
    }
    else if(type=="NUM")
    {
        stringstream s(data);
        double v;
        s>>v;
        stringstream ans;
        ans<<v; // \todo: манипуляторы
        return ans.str();
    }
    else
        throw InternalError();
}
#endif
