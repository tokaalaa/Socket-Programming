#include "Request.h"

using namespace std;

string Request::getData(){
			return data;
}
void Request::setData(string data) {
			this->data = data;
}

map<string, string> Request::getHeaders() {
			return headers;
}

bool Request::hasHeader(string key) {
	return this->headers.find(key) != this->headers.end();
}

void Request::setHeaders(map<string, string> headers) {
			this->headers = headers;
}
void Request::addHeader(string key, string value){
            this->headers[key] = value;
}

string Request::getProtocol() {
			return protocol;
}

void Request::setProtocol(string protocol) {
			this->protocol = protocol;
}

string Request::getType() {
			return type;
}

void Request::setType(string type) {
			this->type = type;
}

string Request::getUrl() {
			return url;
}

void Request::setUrl(string url) {
			this->url = url;
}
void Request::setPort(string serverPort){
            this->serverPort = serverPort;
}
string Request::getPort(){
            return this->serverPort;
}

string Request::getHeaderByKey(string key) {
	return this->headers.find(key)->second;
}
string Request::get_request() {
	string s = "";
	s += this->type + " ";
	s +=  this->url + " ";
    s += this->protocol+"\r\n";
	map<string, string>::iterator it;
	for (it = this->headers.begin(); it != this->headers.end(); it++) {
		s += it->first + " : " + it->second + "\r\n";
	}
	s += "\r\n";
	return s;
}
