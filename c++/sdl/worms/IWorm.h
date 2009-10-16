#ifndef IWORM_H
#define IWORM_H

#include <vector>
#include <utils.h>

// методы, общие дл€ логики черв€ и дл€ основной программы
class IWorm
{
public:
    // возвращает позиции каждой из клеток черв€, [0] - голова
    virtual const std::vector<pii>& Position() const = 0;
    
    // его энерги€
    virtual double Energy() const = 0;
    
    // »дентификатор, уникальный дл€ каждого экземпл€ра черв€
    virtual int GetID() const = 0;

    // »дентификатор, уникальный дл€ каждого класса черв€
    virtual int GetClassID() const = 0;
};

#endif
