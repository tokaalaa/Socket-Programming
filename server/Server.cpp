#include "Server.h"
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <string.h> // for htons & memset
#include <unistd.h> // for close function
#include <sys/time.h>
#include <ctime>

using namespace std;

#define BACKLOG_QUEUE_SIZE 20	//MAX CONNECTIONS=20
#define TIMEOUT	120

void Server::start_server(int port)
{   // make a socket:
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// creation returns -1 on error
	if (sockfd < 0) {
		perror("Socket Creation Failed!");
		return;
	}

	/* setup the host_addr structure for use in bind call */
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0 , sizeof(sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;// automatically be filled with current host's IP address
	serverAddr.sin_port = htons(port); // htons used to convert into network byte order

	// binding returns -1 on error
	int success = bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (success < 0) {
		perror("Bind Failed!");
		return;
	}
    cout<<"server is running on port: "<<port<<endl;

    // listen returns -1 on error
	success = listen(sockfd, BACKLOG_QUEUE_SIZE);
	if (success < 0) {
		perror("Listen Failed!");
		return;
	}


    struct sockaddr_in clientAddr;
	int clientLen = sizeof(clientAddr);
	int newsockfd;//returns new socket for the accepted connection
	int enable = 1;
	while(1){
     if ((newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, (socklen_t*)&clientLen))<0)
        {
            perror("Accept failure");
            close(sockfd);
            return;
        }
        unsigned long new_timeout = (TIMEOUT * 1000) / (serverthreads.size() + 1);
		server_thread * serverthread = new server_thread(newsockfd, new_timeout);
		serverthreads.push_back(serverthread);
		serverthread->start_thread();

    }
}

