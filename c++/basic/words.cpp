#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // для sort

using namespace std;

const string letters = "абвгдеёжзийклмнопртсуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРТСУФХЦЧШЩЪЫЬЭЮЯ";

inline bool isalpha(char c)
{
    return letters.find(c)!=string::npos;
}

int main()
{
    string text;
    getline(cin, text); // чтение текста

    vector<string> words;
    
    int pos = 0;
    
    while(pos<text.size() && !isalpha(text[pos])) ++pos; // пропустить всё кроме букв

    while(pos<text.size()) // пока не закончится строка
    {
        int wstart = pos; // начало слова
        while(pos<text.size() && isalpha(text[pos])) ++pos; // пока в тексте буквы - движемся вперёд

        string word = text.substr(wstart, pos-wstart); // вырезаем слово из строки, substr(начало_слова, длина_слова)
        words.push_back(word); // добавить слово в список
        
        while(pos<text.size() && !isalpha(text[pos])) ++pos; // снова пропустить всё кроме букв
    }
    
    sort(words.begin(), words.end()); // сортировка

    for(int i=0; i<words.size(); i++)
        cout<<words[i]<<endl;
    
    return 0;
}