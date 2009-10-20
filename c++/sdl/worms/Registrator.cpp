#include "Registrator.h"
#include "Factory.h"

// include custom worms 
#include "Statue.h"
#include "Manual.h"
#include "Random.h"

#define REGISTER(worm) Register(new Factory<worm>(#worm))

// ��� �������� ����������� ���� ������
Registrator::Registrator()
{
	REGISTER(Statue);
	REGISTER(Manual);
	REGISTER(Random);
}
