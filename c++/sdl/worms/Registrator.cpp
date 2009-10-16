#include "Registrator.h"
#include "Factory.h"
#include "Statue.h"

#define REGISTER(w) Register(new Factory<w>(#w))

// тут проходит регистрация всех червей
Registrator::Registrator()
{
	REGISTER(Statue);
}
