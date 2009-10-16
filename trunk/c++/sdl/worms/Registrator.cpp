#include "Registrator.h"
#include "Factory.h"
#include "Statue.h"

#define REGISTER(w) Register(new Factory<w>(#w))

// ��� �������� ����������� ���� ������
Registrator::Registrator()
{
	REGISTER(Statue);
}
