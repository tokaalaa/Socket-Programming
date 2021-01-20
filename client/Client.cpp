#include "Client.h"
#include <iostream>
#include <string>
#include "./Parser.h"
using namespace std;

void Client::start_client(int port, char *server_ip, string file){
    Parser parser;
    if(!parser.parse_commands(file)){
        cout << "Could not open Input File to read commands!" << endl;
        return;
    }

    vector<Request> requests = parser.get_requests(); // get the parsed requests
    int sockfd;
    struct sockaddr_in serverAdd;
    while(!(requests.empty())){
           Request req = requests.front();//get first request in the vector
           requests.erase(requests.begin()); // remove from requests vector
           //check if socket exists
           string msg = socketisOpen(&sockfd, req);
           if(msg == "NoHostName"){
               cout << "Failed to fetch host name!" << endl;
               return;
           }
           if(msg != "found"){
            string key = msg;
            hostent * host = gethostbyname(req.getHeaderByKey("host").c_str());
            struct in_addr * hostAdd = (struct in_addr *)host->h_addr_list[0];
            create_Socket(&sockfd, &serverAdd, hostAdd,key, stoi(req.getPort()));
           }
            if (req.getType() == "GET") {
                //try to send the http request to server
                if(!send_request(sockfd, serverAdd, req)){
                    return;
                }
            }
            if (req.getType() == "POST") {
			ifstream t("." + req.getUrl());
			string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
			req.addHeader("Content-Length", to_string(str.size()));
			if (!send_request(sockfd, serverAdd, req)) {
				return;
			}
			cout << "POST " << req.getUrl() << endl;
			int statusCode;
			/**
			receive_response(sockfd, serverAdd, true, "POST", req, &statusCode);
			if (statusCode == 200) {
				//send data
			}*/
		}

       }
       // close all connections when all requests are sent
       if (requests.empty()) {
			map<string, int>::iterator it = connections.begin();
			while(it != connections.end()) {
				close(it->second);
				it++;
			}
		}

}

string Client::socketisOpen(int *sockfd, Request req) {
	struct in_addr * hostAdd;
	if (!req.hasHeader("host")) {
		return "NoHostName";
	} else {
	//gethostbyname() simply copies host name into the h_name field and its struct in_addr equivalent
    //into the h_addr_list[0] field of the returned hostent structure.
    	hostent * host = gethostbyname(req.getHeaderByKey("host").c_str());
		hostAdd = (struct in_addr *)host->h_addr_list[0];
	}
	string ip(inet_ntoa((*hostAdd)));
	string key = ip + ":" + req.getPort();

	if (connections.find(key) != connections.end()) {
		*sockfd = connections.find(key)->second;
		cout << "Connection is Open at " + key << endl;
		return "found";
	}
	return key;
}

void Client::create_Socket(int *sockfd, struct sockaddr_in *serverAdd, struct in_addr * hostAdd, string key, int port) {

	if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Failed to create a new socket!");
	}

	memset(serverAdd, 0 , sizeof(sockaddr_in));
	serverAdd->sin_family = AF_INET;
	serverAdd->sin_addr.s_addr = inet_addr(inet_ntoa((*hostAdd)));
	serverAdd->sin_port = htons(port);

	if(!connect_server(*sockfd, *serverAdd)) return;
	cout << "new Connection is established " + key << endl;
	connections.insert(pair<string, int>(key, *sockfd));
}

bool Client::connect_server(int sockfd,struct sockaddr_in serverAdd ) {
	int success = connect(sockfd, (struct sockaddr *) &serverAdd, sizeof(serverAdd));
	if (success < 0) {
		perror("Could not connect to server!");
		return false;
	}
	return true;
}

bool Client:: send_request(int sockfd, struct sockaddr_in serverAdd, Request req) {
	string str = req.get_request();
	// get length of request.
	int stringLen = str.length();

	//c_str returns a const char*
	int success = send(sockfd, str.c_str() , stringLen, 0);
	cout<<success;
	if (success < 0) {
		if (connect_server(sockfd, serverAdd)) {
			 success = send(sockfd, str.c_str() , stringLen, 0);//try again!
			 if (success < 0) {
                 perror("Could not send request to server!");
                return false;
			 }
		} else {
			perror("Could not send request to server!");
			return false;
		}
	}
	return true;
}
