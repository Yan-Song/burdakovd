#ifndef IBODY_H
#define IBODY_H

#include "sdlapplication.h"
#include <vector>

class IBody
{
public:
    
    // возвращает позиции каждой из клеток черв€, [0] - голова
    virtual const std::vector<pii>& Position() const = 0;
    
    // его энерги€
    virtual int Energy() const = 0;
    
    // »дентификатор, уникальный дл€ каждого экземпл€ра черв€
    virtual int GetID() const = 0;

    // »дентификатор, уникальный дл€ каждого класса черв€
    virtual int GetClassID() const = 0;
};

#endif
