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
	string path, table, filename, meta;
	static string encode(const string&);
	static string decode(const string&);
	static string vencode(const vector<string>&);
	static vector<string> vdecode(const string&);
    void filenames();
public:
    vector<string> fields, fieldtypes;
    vector<vector<Field> > rows;
	Table(string _path, string tablename); // загрузить таблицу в память
	
	// создать новую таблицу
    Table(string _path, string tablename, vector<string> _fields, vector<string> _fieldtypes);
	
    void save(); // save to file
    void removeIt(); // remove all files of this table
};

class Database
// управляет всеми таблицами
{
private:
    string path;
public:
    Database(const string& _path);
    Table meta();
    vector<string> listTables();
    Table createTable(string tablename, vector<string> _fields, vector<string> _fieldtypes);
    void deleteTable(string tablename);
    ~Database();
};

#endif
