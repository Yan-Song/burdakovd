#include "sdlapplication.h"
#include "radar.h"

#pragma comment(linker, "/STACK:167772160")

int main(int argc, char *argv[]) // argc/argv важны, без них не компилится
{
	Radar app;
	app.Run();
	return 0;
}
