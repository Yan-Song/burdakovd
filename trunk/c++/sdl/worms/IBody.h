#ifndef IBODY_H
#define IBODY_H

#include "sdlapplication.h"
#include <vector>

class IBody
{
public:
    
    // ���������� ������� ������ �� ������ �����, [0] - ������
    virtual const std::vector<pii>& Position() const = 0;
    
    // ��� �������
    virtual int Energy() const = 0;
    
    // �������������, ���������� ��� ������� ���������� �����
    virtual int GetID() const = 0;

    // �������������, ���������� ��� ������� ������ �����
    virtual int GetClassID() const = 0;
};

#endif
