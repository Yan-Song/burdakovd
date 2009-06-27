#include <iostream>
#include "table.hpp"
#include "socket.hpp"
#include "fields.hpp"
#include "exceptions.hpp"
#include "grammar.hpp"
#include "macro.hpp"
#include "formatter.hpp"
#include <string>
#include <vector>

using namespace std;

string path = "./data"; // где хранятся файлы базы данных
int screenwidth = 100;

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
            try
            {
                s.Write("ready> ");

                Rows results = ExecuteQuery(path, s.Read());
                s.Write(format_table(screenwidth, results));

                s.Write("\n");
            }
            catch(TokenizeError e)
            {
                s.Write("TokenizeError: ");
                s.Write(e.what());
                s.Write("\n");
            }
            catch(GrammarError e)
            {
                s.Write("GrammarError: ");
                s.Write(e.what());
                s.Write("\n");
            }
            catch(InternalError e)
            {
                s.Write("InternalError: ");
                s.Write(e.what());
                s.Write("\n");
            }
            catch(TableNotFound e)
            {
                s.Write("ERROR: Table not found\n");
            }
            catch(TableAlreadyExists e)
            {
                s.Write("ERROR: Table already exists\n");
            }
            catch(QueryError e)
            {
                s.Write("Error while executing query: ");
                s.Write(e.what());
                s.Write("\n");
            }
            catch(SocketError)
            {
                s.Close();
                break;
            }
        }
        cout<<"Connection closed."<<endl;
    }
	return 0;
}
