#include "sdlapplication.h"
#include "radar.h"

#pragma comment(linker, "/STACK:167772160")

int main(int argc, char *argv[]) // argc/argv �����, ��� ��� �� ����������
{
	Radar app;
	app.Run();
	return 0;
}
