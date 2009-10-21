#include "SDLApplication.h"
#include "Mandelbrot.h"

#pragma comment(linker, "/STACK:167772160")

int main(int argc, char** argv)
{
	Mandelbrot app;
	app.Run();
	return 0;
}
