#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H
#include <sys/time.h>
#include <ctime>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <unistd.h> // for close function
#include <ctime>
using namespace std;

class server_thread
{
    public:
        server_thread(int socket, unsigned long timeout);
        void start_thread();
	unsigned long getTimeout();

    private:
        int socket;
        unsigned long timeout;
	thread thd;

};

#endif // SERVER_THREAD_H
