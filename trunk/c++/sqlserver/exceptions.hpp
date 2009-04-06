#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

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

class TableNotFound {};
class TableDataNotFound {};

class TableAlreadyExists {};

class FileError {};

#endif
