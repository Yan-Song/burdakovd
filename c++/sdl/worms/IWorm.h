#ifndef IWORM_H
#define IWORM_H

#include <list>
#include <utils.h>

struct SimplePoint
{
	int X, Y;
	SimplePoint(const int x, const int y) : X(x), Y(y) {};
	
	inline bool operator ==(const SimplePoint& other) const
	{
		return X == other.X && Y == other.Y;
	}

	inline bool operator !=(const SimplePoint& other) const
	{
		return X != other.X || Y != other.Y;
	}
};

typedef std::list<SimplePoint> TPosition;

// ������, ����� ��� ������ ����� � ��� �������� ���������
class IWorm
{
public:
    // ���������� ������� ������ �� ������ �����, [0] - ������
    virtual const TPosition& Position() const = 0;
    
    // ��� �������
    virtual double Energy() const = 0;
    
    // �������������, ���������� ��� ������� ���������� �����
    virtual unsigned int GetID() const = 0;

    // �������������, ���������� ��� ������� ������ �����
    virtual unsigned int GetClassID() const = 0;

	// ����� �� ������������� [0, x)
	virtual int Rand(const int x) const = 0;

	// �� ������� [x, y]
	virtual int Rand(const int x, const int y) const = 0;

	virtual ~IWorm()
	{
	}
};

#endif
