#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>      // std::ifstream
#include "./Request.h"

using namespace std;
class Client
{
    public:
       void start_client(int port, char *server_ip, string file);

    private:
    // list of all openining connections
    // key is IP + portNo of server, value is client socket
    map <string, int> connections;

    void create_Socket(int *sockfd, struct sockaddr_in *serverAdd, struct in_addr * hostAdd, string key, int port);
    string socketisOpen(int *sockfd, Request req);
    bool connect_server(int sockfd,struct sockaddr_in serverAdd );
    bool send_request(int sockfd, struct sockaddr_in serverAdd, Request req);
};

#endif // CLIENT_H
