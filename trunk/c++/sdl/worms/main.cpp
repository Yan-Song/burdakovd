#include "SDLApplication.h"
#include "WormsApplication.h"

int main(int , char **) // argc/argv важны, без них не компилится
{
	WormsApplication app;
	app.Run();
	return 0;
}
