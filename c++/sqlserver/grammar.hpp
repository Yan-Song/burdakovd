#ifndef FIELDS_H
#define FIELDS_H

#include <string>
#include <vector>

using namespace std;

enum tokenid {CONSTSTRING, CONSTNUM, SELECT, INSERT, UPDATE, FROM,
        WHERE, SET, INTO, STAR, EQ, MORE, LESS, MOREEQ, LESSEQ, NOTEQ, PLUS,
        MINUS, UMINUS, DIV, VAR, COMMA, OPEN, CLOSE, DELIMITER};

struct token
{
    string text;
    tokenid id;
    token(string t, tokenid i): text(t), id(i) {};
};

// get string and split it to tokens
vector<token> tokenize(string);

#endif
