#include <iostream>
#include <algorithm>
#include "./Server.h"
using namespace std;
//g++ -o server my_server.cpp

bool is_number(const string& s)
{
    return !s.empty() && find_if(s.begin(),
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

int main(int argc, char *argv[])
{
    if(argc == 2){
        if (!is_number(argv[1])) {
			cout << "Invalid port number!" << endl;
			return 0;
		}
        int port = atoi(argv[1]);
        Server server;
        server.start_server(port);
    }else{
        cout << "Invalid command. Command to run the server: \"" << argv[0] << " <port number> \"" << endl;
    }
    return 0;
}
