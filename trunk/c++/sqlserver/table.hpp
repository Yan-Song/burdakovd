#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "fields.hpp"

using namespace std;

class Table
// заботится о хранении таблиц (на диске, в памяти, etc.)
{
private:
	string table,filename,meta,path;
	vector<string> fields, fieldtypes;
	static string encode(const string&);
	static string decode(const string&);
	static string vencode(const vector<string>&);
	static vector<string> vdecode(const string&);
    vector<vector<Field> > rows;
    void filenames();
public:
	Table(string _path, string tablename); // загрузить таблицу в память
	
	// создать новую таблицу
    Table(string _path, string tablename, vector<string> _fields, vector<string> _fieldtypes);
	
    void save(); // save to file
};

class Database
// управляет всеми таблицами
{
private:
    string path;
public:
    Database(const string& _path);
    vector<string> listTable();
    Table& createTable(string tablename, vector<string> _fields, vector<string> _fieldtypes);
    void deleteTable(string tablename);
    
};

#endif
