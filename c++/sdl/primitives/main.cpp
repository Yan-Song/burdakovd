#include "sdlapplication.h"
#include "primitives.h"

#pragma comment(linker, "/STACK:167772160")

int main(int argc, char *argv[]) // argc/argv �����, ��� ��� �� ����������
{
	PrimitivesApplication app;
	app.Run();
	return 0;
}
