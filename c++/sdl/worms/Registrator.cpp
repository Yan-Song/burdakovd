#include "Registrator.h"
#include "Factory.h"

// include custom worms
#include "Statue.h"
#include "Manual.h"
#include "MouseAvoiders.h"
#include "MouseFollowers.h"
#include "Random.h"
#include "RandomEater.h"

#define REGISTER(worm) Register(SharedFactory(new Factory<worm>(#worm)))

// тут проходит регистрация всех червей
Registrator::Registrator() : factories()
{
	//REGISTER(Statue);
	REGISTER(Manual);
	REGISTER(Random);
	REGISTER(RandomEater);
	REGISTER(MouseAvoider);
	REGISTER(MouseFollower);
}
