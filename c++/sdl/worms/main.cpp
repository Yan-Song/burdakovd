#include "SDLApplication.h"
#include "WormsApplication.h"

#pragma comment(linker, "/STACK:167772160")

int main(int , char **) // argc/argv важны, без них не компилится
{
	WormsApplication app;
	app.Run();
	return 0;
}
