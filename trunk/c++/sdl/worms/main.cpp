#include "sdlapplication.h"
#include "WormsApplication.h"

#pragma comment(linker, "/STACK:167772160")

int main(int argc, char *argv[]) // argc/argv �����, ��� ��� �� ����������
{
	WormsApplication app;
	app.Run();
	return 0;
}
