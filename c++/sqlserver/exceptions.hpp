#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

using namespace std;

class CorruptedData: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Data files are not valid.";
	}
	CorruptedData() {};
};

class QueryError: public exception {};

class UnknownField: public QueryError {};

class TableNotFound: public QueryError {};
class TableDataNotFound: public QueryError {};

class TableAlreadyExists: public QueryError {};

class FileError: public QueryError {};

class TokenizeError
{
    string wh;
public:
    TokenizeError(string s): wh(s) {};
    virtual const char* what() const throw()
    {
        return wh.c_str();
    }
};

class SocketError: public exception {};
class BindError: public SocketError {};
class ListenError: public SocketError {};
class AcceptError: public SocketError {};

class GrammarError
{
    string wh;
public:
    GrammarError(string s): wh(s) {};
    virtual const char* what() const throw()
    {
        return wh.c_str();
    }
};

class InternalError: public exception {};

class UnknownOperator: public InternalError {};

#endif
