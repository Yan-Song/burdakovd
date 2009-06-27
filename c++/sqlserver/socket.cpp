#include "socket.hpp"
#include "exceptions.hpp"
#include "macro.hpp"
#include <cassert>
#include <string>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // ip protocol
#include <arpa/inet.h>
#include <unistd.h> // read

using namespace std;

Listener::Listener(string ip, uint16_t port) // create and bind socket, and listen
{
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock==-1) throw SocketError();
    // bind
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    assert(inet_aton(ip.c_str(), &addr.sin_addr)!=0);
    int e = bind(sock, (const sockaddr*)(&addr), sizeof(addr));
    if(e!=0) throw BindError();
    // listen
    e = listen(sock, 100);
    if(e!=0) throw ListenError();
}

Socket Listener::Accept()
{
    sockaddr_in addr;
    int newsock, laddr;
    newsock = accept(sock, (sockaddr*)(&addr), (socklen_t*)(&laddr));
    if(newsock==-1) throw AcceptError();
    return Socket(newsock);
}

string Socket::Read()
{
    while(buffer.find('\n')==string::npos)
    // пока в буфере нет целой строки
    // читаем из сокета
    {
        char cc[11000];
        int r = recv(sock, cc, 10000, 0);
        if(r==-1) throw SocketError();
        if(r==0) throw SocketError();
        /*debug(r);
        fo(i, 0, r)
            debug(int((unsigned char)cc[i]));*/
        cc[r] = 0; // конец строки
        buffer += string(cc);
    }
    // есть строка, вытаскиваем из буфера и возвращаем
    int br = buffer.find('\n');
    string line = buffer.substr(0, br);
    buffer = buffer.substr(br+1, string::npos);
    //debug(line);
    //debug(buffer);
    //vdebug(line);
    return line;
}

void Socket::Write(string text)
{
    //debug(text);
    if(send(sock, text.c_str(), text.size(), 0)!=text.size()) throw SocketError();
}

void Socket::Close()
{
    if(shutdown(sock, 2)==-1) throw SocketError();
    if(close(sock)==-1) throw SocketError();
}
