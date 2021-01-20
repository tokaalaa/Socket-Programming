#include "server_thread.h"
#include <string.h>
#define MAX_BUF_SIZE	1024
server_thread::server_thread(int socket, unsigned long timeout)
{
    this->socket = socket;
	this->timeout = timeout;
}
void serveClient(int sockfd, server_thread *serverthread);
void server_thread::start_thread(){
    this->thd = thread(serveClient, this->socket, this);
}
void serveClient(int sockfd, server_thread *serverthread){
char buffer[MAX_BUF_SIZE];
buffer[MAX_BUF_SIZE] = '\0';
int recvMsgSize;
if ((recvMsgSize = recv(sockfd, buffer, MAX_BUF_SIZE, 0)) < 0) {
			perror("Could not recieve request msg!" );
			return;
}

cout<<buffer;

return;
}

unsigned long server_thread::getTimeout() {
	return this->timeout;
}
