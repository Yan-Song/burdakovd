#ifndef SOCKET_H
#define SOCKET_H

#include <string>

using namespace std;

class Socket
{
    int sock;
public:
    Socket(int s): sock(s) {};
    string Read();
    void Write(string);
    void Close();
};

class Listener
{
    int domain, type, protocol;
    int sock;
public:
    Listener(string ip, uint16_t port); // create and bind socket, and listen
    Socket Accept();
};

/*
Usage:
    Listener l("127.0.0.1", 5555);
    while(true)
    {
        Socket s = l.Accept();
        string t = s.Read();
        cout<<t<<endl;
        s.Write("Good bye.\n");
        s.Close();
    };
*/

#endif
