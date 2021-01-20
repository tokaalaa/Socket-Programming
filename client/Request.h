#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Request
{
    public:
        string getData();
        void setData(string data);
        map<string, string> getHeaders();
        bool hasHeader(string key);
        void setHeaders(map<string, string> headers);
        void addHeader(string key, string value);
        string getProtocol();
        void setProtocol(string protocol);
        string getType();
        void setType(string type);
        string getUrl();
        void setUrl(string url);
        string get_request();
        string getHeaderByKey(string key);
        void setPort(string serverPort);
        string getPort();
    private:
        string type;
		string protocol;
		string url;
		string serverPort;
		map<string, string> headers;
		string data;
};

#endif // REQUEST_H
