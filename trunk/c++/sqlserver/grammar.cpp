#include "grammar.hpp"
#include <string>
#include "macro.hpp"
#include "exceptions.hpp"
#include <cassert>

#include <iostream>
using namespace std;
#define debugprint(s) cout<<s<<endl

using namespace std;

inline bool isalpha(char c)
{
    return (c<='z')&&(c>='a') || (c<='Z')&&(c>='A');
}

class Tokenizer
{
    string s, buf;
    int pos;
    char top()
    {
        if(pos>s.size()) throw("Unexpected end of line");
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
        for(char c=top(); string(" \t\n").find(c)!=string::npos; c=top())
            pop(c);
    }
public:
    vector<token> v;
    Tokenizer(string _s): s(_s), pos(0), buf("")
    {
        do
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
                if(buf=="SELECT") tid = SELECT;
                else if(buf=="INSERT") tid = INSERT;
                else if(buf=="UPDATE") tid = UPDATE;
                else if(buf=="FROM") tid = FROM;
                else if(buf=="WHERE") tid = WHERE;
                else if(buf=="SET") tid = SET;
                else if(buf=="INTO") tid = INTO;
                else tid = VAR;
                v.push_back(token(buf, tid));
            }
            else throw TokenizeError(("Unexpected "+s.substr(pos)).c_str());
            spaces();
        }
        while(top()!=0);
        pop(0);
    };
};

vector<token> tokenize(string s)
{
    Tokenizer t(s);
    return t.v;
}
