#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main ()
{
    pid_t pid=fork();
    if(pid==0)
        cout << "[ребёнок] Йа родился!" << endl;
    else
    {
        cout << "[родитель] Ну-ка.... родили ребёнка номер " << pid << endl;
        cout << "[родитель] Йа тебя породил..." << endl;
        cout << "[родитель] Йа тебя и убью..." << endl;
        kill(pid, 9); // 9 - реально убийство
        int status;
        waitpid(pid, &status, 0);
        cout << "[родитель] готов... диагноз: " << status << endl;
    }
    return 0;
}
