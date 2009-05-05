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

class UnknownField: public exception {};

class TableNotFound: public exception {};
class TableDataNotFound: public exception {};

class TableAlreadyExists: public exception {};

class FileError: public exception {};

class TokenizeError//: public exception //\\todo
{
    const char* wh;
public:
    TokenizeError(const char* s): wh(s) {};
    virtual const char* what() const throw()
    {
        return wh;
    }
};

class SocketError: public exception {};
class BindError: public SocketError {};
class ListenError: public SocketError {};
class AcceptError: public SocketError {};

#endif
