#include "sdlapplication.h"
#include "life.h"

int main(int, char**) // наличие аргументов важно, без них не компилится под Visual Studio
{
	LifeApplication app;
	app.Run();
	return 0;
}
