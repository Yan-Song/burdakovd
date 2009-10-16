#ifndef IWORM_H
#define IWORM_H

#include <vector>
#include <utils.h>

// ������, ����� ��� ������ ����� � ��� �������� ���������
class IWorm
{
public:
    // ���������� ������� ������ �� ������ �����, [0] - ������
    virtual const std::vector<pii>& Position() const = 0;
    
    // ��� �������
    virtual double Energy() const = 0;
    
    // �������������, ���������� ��� ������� ���������� �����
    virtual int GetID() const = 0;

    // �������������, ���������� ��� ������� ������ �����
    virtual int GetClassID() const = 0;
};

#endif
