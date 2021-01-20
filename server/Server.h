#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include "server_thread.h"
class Server
{
    public:
		void start_server(int port);

    private:
    vector<server_thread *> serverthreads;
};

#endif // SERVER_H
