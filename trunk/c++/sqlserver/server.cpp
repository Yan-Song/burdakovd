#include <iostream>
#include "table.hpp"
#include "socket.hpp"
#include "fields.hpp"
#include "exceptions.hpp"
#include "grammar.hpp"
#include "macro.hpp"
#include <string>

using namespace std;

int main()
{
    Listener l("0.0.0.0", 5555);
    while(true)
    {
        cout<<"Accepting connections..."<<endl;
        Socket s = l.Accept();
        cout<<"Accepted connection."<<endl;
        while(true)
        {
            string query;
            try
            {
                query = s.Read();
            }
            catch(SocketError)
            {
                s.Close();
                break;
            }
            debug(query);
            
        }
        cout<<"Connection closed."<<endl;
    }
	return 0;
}
