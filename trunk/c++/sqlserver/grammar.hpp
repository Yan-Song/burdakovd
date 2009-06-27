#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>
#include "fields.hpp"

using namespace std;

enum tokenid { CONSTSTRING, CONSTNUM, SELECT, INSERT, UPDATE, FROM,
        WHERE, SET, INTO, STAR, EQ, MORE, LESS, MOREEQ, LESSEQ, NOTEQ, PLUS,
        MINUS, UMINUS, DIV, VAR, COMMA, OPEN, CLOSE, DELIMITER, AND, OR, NOT,
        CREATE, DELETE, TABLE, BOOLEAN, STRING, NUM, TABLES, FIELDS, DROP,
        VALUES };

typedef vector<Field> Row;
typedef vector<Row> Rows;

struct token
{
    string text;
    tokenid id;
    double value;
    token(string t, tokenid i): text(t), id(i) {};
};

ostream& operator<<(ostream&, const token&);

// get string and split it to tokens
vector<token> tokenize(string);

class Query
{
protected:
    tokenid action; // select || ...
    vector<token> query;
    string table;
    vector<token> statements;
    vector<token> poliz;
    token top();
    void pop();
    void Expect(string);
    void pop(bool, string);
    void pop(tokenid, string);
    void Where();
    void make_poliz();
    bool Evaluate(Row); // проверяет, соответствует ли строка условию where
public:
    Rows Execute(string path);
    virtual ~Query() {};
};

class SelectQuery: public Query
// SELECT <selections> FROM <table> WHERE <statements>;
{
    vector<string> selections;
    bool Evaluate(Row);
public:
    SelectQuery(vector<token>);
    Rows Execute(string path);
};

class CreateQuery: public Query
// CREATE TABLE <tablename> (<type1> <field1>, <type2> <field2>, ...)
{
    vector<string> types;
    vector<string> names;
    void get_type_and_name();
public:
    CreateQuery(vector<token>);
    virtual Rows Execute(string path);
};

class InsertQuery: public Query
// INSERT
{
    Row values;
    void get_value();
public:
    InsertQuery(vector<token>);
    virtual Rows Execute(string path);
};

class TablesQuery: public Query
// TABLES
{
public:
    TablesQuery(vector<token>);
    virtual Rows Execute(string path);
};

class FieldsQuery: public Query
// FIELDS
{
public:
    FieldsQuery(vector<token>);
    virtual Rows Execute(string path);
};

class DropQuery: public Query
// DROP
{
public:
    DropQuery(vector<token>);
    virtual Rows Execute(string path);
};

Rows ExecuteQuery(string path, string query);

#endif
