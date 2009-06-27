#ifndef FORMATTER_H
#define FORMATTER_H

#include "grammar.hpp"
#include <string>

using namespace std;

string format_table(int width, Rows data);
// получает набор строк таблицы  и ширину экрана
// возвращает строку которую можно напрямую вывести на cout

#endif