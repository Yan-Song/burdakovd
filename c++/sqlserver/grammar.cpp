#include "grammar.hpp"
#include <string>
#include <stack>
#include "macro.hpp"
#include "table.hpp"
#include "exceptions.hpp"
#include <cassert>

#include <iostream>
using namespace std;
#define debugprint(s) cout<<s<<endl

using namespace std;


////////// general tools ////////////////

inline bool is_value(tokenid s)
{
    return s==BOOLEAN || s==NUM || s==STRING;
}

bool check_in(string text, vs v)
{
    foreach(i, v)
        if(text == v[i]) return true;
    return false;
}

string caps(string text)
{
    string ans = text;
    foreach(i, ans)
        if(ans[i]<='z' && ans[i]>='a')
            ans[i] += 'A' - 'a';
    return ans;
}

int priority(tokenid op)
{
    if(op==UMINUS) return 0;
    if(op==DIV) return -1;
    if(op==STAR) return -1;
    if(op==PLUS) return -2;
    if(op==MINUS) return -2;
    if(op==EQ) return -3;
    if(op==NOTEQ) return -3;
    if(op==MORE) return -3;
    if(op==MOREEQ) return -3;
    if(op==LESS) return -3;
    if(op==LESSEQ) return -3;
    if(op==NOT) return -4;
    if(op==AND) return -5;
    if(op==OR) return -6;
    cerr<<op<<endl;
    throw UnknownOperator();
}

inline bool is_operator(tokenid sid)
{
    return sid==MORE || sid==LESS || sid==MOREEQ || sid==LESSEQ ||
        sid==NOTEQ || sid==PLUS || sid==MINUS || sid==UMINUS ||
        sid==DIV || sid==STAR || sid==AND || sid==OR || sid==NOT ||
        sid==EQ;
}

inline bool is_fieldtype(tokenid sid)
{
    return sid==NUM || sid==STRING;
}

inline bool isalpha(char c)
{
    return (c<='z')&&(c>='a') || (c<='Z')&&(c>='A');
}

inline bool isdigit(char c)
{
    return (c<='9')&&(c>='0');
}

ostream& operator<<(ostream& os, const token& t)
{
    os<<"token(id="<<t.id<<", text=`"<<t.text<<"`)";
    return os;
}

////// Tokenizer //////////////

class Tokenizer
{
    string s, buf;
    int pos;
    char top()
    {
        if(pos>s.size()) throw TokenizeError("Unexpected end of line");
        return pos<s.size() ? s[pos] : 0;
    }
    void pop(char c)
    {
        if(c!=top())
        {
            string hc = c==0 ? "end of line" : string("`")+c+"`";
            string hs = top()==0 ? "end of line" : "`"+s.substr(pos)+"`";
            throw TokenizeError((hc + " expected near " + hs).c_str());
        }
        ++pos;
    }
    void spaces()
    {
        for(char c=top(); c==' '||c==10||c=='\t'||c==13; c=top())
        {
            //cout<<"spaces("<<int(c)<<")"<<endl;
            pop(c);
        }
    }
public:
    vector<token> v;
    Tokenizer(string _s): s(_s), pos(0), buf("")
    {
        spaces();
        while(top()!=0)
        {
//             CONSTSTRING, CONSTNUM, SELECT, INSERT, UPDATE, FROM,
//                 WHERE, SET, INTO, STAR, EQ, MORE, LESS, MOREEQ, LESSEQ, NOTEQ, PLUS,
//                 MINUS, UMINUS, DIV, VAR, COMMA, OPEN, CLOSE
            spaces();
            if(top()=='"') // CONSTSTRING
            {
                buf = "";
                pop('"');
                while(top()!='"')
                {
                    buf += top();
                    pop(top());
                }
                pop('"');
                v.push_back(token(buf, CONSTSTRING));
            }
            else if(top()=='-')
            {
                pop('-');
                // обычный минус может быть после переменной, числа или закрывающей скобки
                // в остальных случаях - унарный
                if(!v.empty() && (v[v.size()-1].id==CONSTNUM || v[v.size()-1].id==VAR || v[v.size()-1].id==CLOSE))
                    v.push_back(token("-", MINUS));
                else
                    v.push_back(token("-", UMINUS));
            }
            else if(top()=='*')
            {
                pop('*');
                v.push_back(token("*", STAR));
            }
            else if(top()==';')
            {
                pop(';');
                v.push_back(token(";", DELIMITER));
            }
            else if(top()=='=')
            {
                pop('=');spaces();
                v.push_back(token("=", EQ));
            }
            else if(top()=='>')
            {
                pop('>');
                if(top()=='=')
                {
                    pop('=');
                    v.push_back(token(">=", MOREEQ));
                }
                else v.push_back(token(">", MORE));
            }
            else if(top()=='<')
            {
                pop('<');
                if(top()=='=')
                {
                    pop('=');
                    v.push_back(token("<=", LESSEQ));
                }
                else if(top()=='>')
                {
                    pop('>');
                    v.push_back(token("<>", NOTEQ));
                }
                else v.push_back(token("<", LESS));
            }
            else if(top()=='!')
            {
                pop('!');
                pop('=');
                v.push_back(token("!=", NOTEQ));
            }
            else if(top()=='+')
            {
                pop('+');
                v.push_back(token("+", PLUS));
            }
            else if(top()=='/')
            {
                pop('/');
                v.push_back(token("/", DIV));
            }
            else if(top()==',')
            {
                pop(',');
                v.push_back(token(",", COMMA));
            }
            else if(top()=='(')
            {
                pop('(');
                v.push_back(token("(", OPEN));
            }
            else if(top()==')')
            {
                pop(')');
                v.push_back(token(")", CLOSE));
            }
            else if(isalpha(top()))
            {
                buf = "";
                while(isalpha(top()))
                {
                    buf += top();
                    pop(top());
                }
                tokenid tid;
                string capsed = caps(buf);
                if(capsed=="SELECT") tid = SELECT;
                else if(capsed=="INSERT") tid = INSERT;
                else if(capsed=="UPDATE") tid = UPDATE;
                else if(capsed=="FROM") tid = FROM;
                else if(capsed=="WHERE") tid = WHERE;
                else if(capsed=="SET") tid = SET;
                else if(capsed=="INTO") tid = INTO;
                else if(capsed=="OR") tid = OR;
                else if(capsed=="AND") tid = AND;
                else if(capsed=="NOT") tid = NOT;
                else if(capsed=="CREATE") tid = CREATE;
                else if(capsed=="DELETE") tid = DELETE;
                else if(capsed=="TABLE") tid = TABLE;
                else if(capsed=="TABLES") tid = TABLES;
                else if(capsed=="FIELDS") tid = FIELDS;
                else if(capsed=="NUM") tid = NUM;
                else if(capsed=="STRING") tid = STRING;
                else if(capsed=="BOOLEAN") tid = BOOLEAN;
                else if(capsed=="DROP") tid = DROP;
                else if(capsed=="VALUES") tid = VALUES;
                else tid = VAR;
                v.push_back(token(buf, tid));
            }
            else if(isdigit(top()))
            {
                double ans=0;
                string buf="";
                while(isdigit(top()))
                {
                    buf += top();
                    ans = ans*10 + (top()-'0');
                    pop(top());
                }
                if(top()=='.')
                {
                    pop('.');
                    buf += '.';
                    double k=0.1;
                    while(isdigit(top()))
                    {
                        buf += top();
                        ans += k * (top()-'0');
                        k /= 10;
                        pop(top());
                    }
                }
                token tt(buf, CONSTNUM);
                tt.value = ans;
                v.push_back(tt);
            }
            else
            {
                //debugprint(int(s[pos]));
                throw TokenizeError("Unexpected "+s.substr(pos));
            }
            spaces();
        }
        pop(0);
    };
    //
};

vector<token> tokenize(string s)
{
    Tokenizer t(s);
    //vdebug(t.v);
    return t.v;
}

///////////////// general Query ///////////////////

token Query::top()
{
    if(query.empty()) throw GrammarError("top(): Unexpected end of query");
    return query[0];
}

void Query::pop()
{
    if(query.empty()) throw GrammarError("pop(): Unexpected end of query");
    query.erase(query.begin());
}

void Query::Expect(string s)
{
    throw GrammarError(s+" expected, but "+top().text+" found.");
}

void Query::pop(bool statement, string description)
{
    if(statement) pop();
    else Expect(description);
}

void Query::pop(tokenid id, string description)
{
    pop(top().id==id, description);
}

void Query::Where()
{
    if(!query.empty())
    {
        pop(WHERE, "WHERE");
        statements = query;
    }
    else
    {
        // 1=1, always True
        statements.clear();
        token tt("1", CONSTNUM);
        tt.value = 1;
        statements.push_back(tt);
        token tz("=", EQ);
        statements.push_back(tz);
        statements.push_back(tt);
    }
    make_poliz();
}

void Query::make_poliz()
{
    // make poliz from statements
    stack<token> S;
    //vdebug(statements);
    foreach(i, statements)
    {
        token s = statements[i];
        if(s.id==CONSTNUM || s.id==CONSTSTRING || s.id==VAR)
            poliz.push_back(s); // значение
        
        else if(is_operator(s.id))
        {
            // оператор
            // левоассоциативен ли он?
            bool lassoc = s.id!=UMINUS && s.id!=NOT;
            // вытесняем из стека операторы с большим приоритетом
            // или с равным если он левоассоциативен
            while(!S.empty() && is_operator(S.top().id) &&
                  (priority(s.id)<priority(S.top().id) || lassoc && priority(s.id)==priority(S.top().id)))
            {
                poliz.push_back(S.top());
                S.pop();
            }
            // добавляем его в стек
            S.push(s);
        }
        else if(s.id==OPEN)
            S.push(s);
        else if(s.id==CLOSE)
        {
            while(!S.empty() && S.top().id!=OPEN)
            {
                poliz.push_back(S.top());
                S.pop();
            }
            if(S.empty())
                throw GrammarError("MismatchedParentheses");
            S.pop();
        }
        else throw GrammarError("WTF: "+s.text);
    }
    while(!S.empty())
    {
        if(S.top().id==OPEN) throw GrammarError("MismatchedParentheses");
        poliz.push_back(S.top());
        S.pop();
    }
    //vdebug(poliz);
}


/////////////// SELECT /////////////////////

SelectQuery::SelectQuery(vector<token> v)
{
    query = v;
    pop();
    
    // selections - список полей, перечисленных через запятую
    if(top().id==STAR)
    {
        selections.push_back("*");
        pop();
    }
    else if(top().id==VAR)
    {
        selections.push_back(top().text);
        pop();
        while(top().id==COMMA)
        {
            pop();
            if(top().id==VAR)
            {
                selections.push_back(top().text);
                pop();
            }
            else
                Expect("Field name");
        }
    }
    else
        Expect("Field name or *");
    
    // from
    pop(FROM, "FROM");

    // from which table
    if(top().id==VAR)
    {
        table = top().text;
        pop();
    }
    else
        Expect("Table name");

    Where();
}


bool SelectQuery::Evaluate(Row row)
{
    
}

Rows SelectQuery::Execute(string path)
{
    Table t(path, table);

    if(selections.size()==1 && selections[0]=="*")
        selections = t.fields;
    
    foreach(i, poliz)
        if(poliz[i].id==VAR && !check_in(poliz[i].text, t.fields))
            throw GrammarError("Unknown field: "+poliz[i].text);
    
    foreach(i, selections)
        if(!check_in(selections[i], t.fields))
            throw GrammarError("Unknown field: "+selections[i]);

    Rows result;
    
    foreach(i, t.rows)
        if(Evaluate(t.rows[i]))
            result.push_back(t.rows[i]);
    
    return result;
}

////////////////////////// CREATE //////////////////////////////

void CreateQuery::get_type_and_name()
{
    if(is_fieldtype(top().id))
    {
        types.push_back(top().text);
        pop();
    }
    else Expect("Field type");
    
    if(top().id==VAR)
    {
        names.push_back(top().text);
        pop();
    }
    else Expect("Field name");
}

CreateQuery::CreateQuery(vector<token> v)
{
    query = v;
    pop(CREATE, "CREATE");

    pop(TABLE, "TABLE");

    // table name to create
    if(top().id==VAR)
    {
        table = top().text;
        pop();
    }
    else
        Expect("Table name");

    pop(OPEN, "(");

    get_type_and_name();
    
    while(top().id==COMMA)
    {
        pop();
        get_type_and_name();
    }
    pop(CLOSE, ")");

    if(!query.empty())
        Expect("end of query");
}

Rows CreateQuery::Execute(string path)
{
    Database d(path);
    d.createTable(table, names, types);
    Rows result;
    result.push_back(Row());
    result[0].push_back(Field("STRING", "Table successfully created"));
    return result;
}

////////////////////////// INSERT //////////////////////////////

void InsertQuery::get_value()
{
    if(top().id==CONSTSTRING)
        values.push_back(Field("STRING", top().text));
    else if(top().id==CONSTNUM)
        values.push_back(Field("NUM", top().text));
    else
        Expect("String or Num value");
    debug(top().text);
    pop();
}

InsertQuery::InsertQuery(vector<token> v)
{
    query = v;
    pop(INSERT, "INSERT");
    
    pop(INTO, "INTO");
    
    // table name
    if(top().id==VAR)
    {
        table = top().text;
        pop();
    }
    else
        Expect("Table name");

    pop(VALUES, "VALUES");
    
    pop(OPEN, "(");
    
    get_value();
    
    while(top().id==COMMA)
    {
        pop();
        get_value();
    }
    pop(CLOSE, "`)` or `,`");
    
    if(!query.empty())
        Expect("end of query");
    debug("built");
}

Rows InsertQuery::Execute(string path)
{
    debug("executing...");
    debug(path);
    debug(table);
    Table t(path, table);
    debug("table loaded");
    vs fieldtypes = t.fieldtypes;
    
    if(fieldtypes.size()!=values.size())
        throw GrammarError("Count of values != count of fields in table");
    debug("count of fields checked");
    foreach(i, values)
        if(fieldtypes[i] != values[i].type)
            throw GrammarError("Type of value != type of field (for " + t.fields[i] +")");
    debug("types checked");
    // количество и типы значений в норме
    t.rows.push_back(values);
    debug("will save");
    t.save();
    debug("saved");
    
    return Rows(1, Row(1, Field("STRING", "OK")));
}

//////////////// TABLES //////////////////////////////////////////

TablesQuery::TablesQuery(vector<token> v)
{
    query = v;
    pop(TABLES, "TABLES");
    if(!query.empty())
        Expect("End of query");
}

Rows TablesQuery::Execute(string path)
{
    Database d(path);
    Rows rows;
    vs v = d.listTables();
    foreach(i, v)
        rows.push_back(Row(1, Field("STRING", v[i])));
    return rows;
}

//////////////// FIELDS //////////////////////////////////////////

FieldsQuery::FieldsQuery(vector<token> v)
{
    query = v;
    pop(FIELDS, "FIELDS");
    if(top().id==VAR)
        table = top().text;
    else
        Expect("Table name");
    pop();
    if(!query.empty())
        Expect("End of query");
}

Rows FieldsQuery::Execute(string path)
{
    Rows rows;
    Table t(path, table);
    
    foreach(i, t.fields)
    {
        Row row;
        row.push_back(Field("STRING", t.fields[i]));
        row.push_back(Field("STRING", t.fieldtypes[i]));
        rows.push_back(row);
    }
    return rows;
}

//////////////// DROP //////////////////////////////////////////

DropQuery::DropQuery(vector<token> v)
{
    query = v;
    pop(DROP, "DROP");
    pop(TABLE, "TABLE");
    if(top().id==VAR)
        table = top().text;
    else
        Expect("Table name");
    pop();
    if(!query.empty())
        Expect("End of query");
}

Rows DropQuery::Execute(string path)
{
    Rows rows;
    Database d(path);
    d.deleteTable(table);
    return Rows(1, Row(1, Field("STRING", "Successfully deleted")));
}

//////////////////////////////////////////////////////////////////

Rows ExecuteQuery(string path, string query)
{
    vector<token> tokens = tokenize(query);

    if(tokens.empty())
        throw GrammarError("Empty query");

    tokenid action = tokens[0].id;
    if(action==SELECT)
    {
        SelectQuery q(tokens);
        return q.Execute(path);
    }
    else if(action==CREATE)
    {
        CreateQuery q(tokens);
        return q.Execute(path);
    }
    else if(action==TABLES)
    {
        TablesQuery q(tokens);
        return q.Execute(path);
    }
    else if(action==FIELDS)
    {
        FieldsQuery q(tokens);
        return q.Execute(path);
    }
    else if(action==DROP)
    {
        DropQuery q(tokens);
        return q.Execute(path);
    }
    else if(action==INSERT)
    {
        InsertQuery q(tokens);
        return q.Execute(path);
    }
    else
        throw GrammarError("Unsupported action: "+tokens[0].text);
}
