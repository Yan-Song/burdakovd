#ifndef IBODY_H
#define IBODY_H

#include "sdlapplication.h"
#include <vector>

class IBody
{
public:
    
    // ���������� ������� ������ �� ������ �����, [0] - ������
    const std::vector<pii>& Position() const = 0;
    
    // ��� �������
    int Energy() const = 0;
    
    // �������������, ���������� ��� ������� ���������� �����
    int GetID() const = 0;

    // �������������, ���������� ��� ������� ������ �����
    int GetClassID() const = 0;
};

#endif
