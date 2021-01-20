#include <iostream>
#include <algorithm>
#include "./Client.h"
using namespace std;
//g++ -o client my_client.cpp

bool is_number(const string& s)
{
    return !s.empty() && find_if(s.begin(),
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

int main(int argc, char *argv[])
{
    if(argc == 3){
        if (!is_number(argv[2])) {
			cout << "Invalid port number!" << endl;
			return 0;
		}

        char *server_ip = argv[1];
        int port = atoi(argv[2]);
        string file;
        cout << "Enter Input File path to read commands: " << endl;
       // cin >> file;
        Client client;
        client.start_client(port, server_ip, "./commands");
    }else{
        cout << "Invalid command. Command to run the client: \"" << argv[0] << " <server_ip> <port number> \"" << endl;
    }
    return 0;
}
