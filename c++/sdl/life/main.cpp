#include "sdlapplication.h"
#include "life.h"

int main(int argc, char *argv[]) // argc/argv важны, без них не компилится
{
	LifeApplication app;
	app.Run();
	return 0;
}
