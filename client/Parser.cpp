#include "Parser.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

bool Parser::parse_commands(string file){
    ifstream ifstr;
        ifstr.open(file);
	if (!ifstr) {
		return false;
	}
	string line, s="";

	while (getline(ifstr, line)) {
        string tmp;
        stringstream ss(line);
        vector<string> words;
        //split line by space
        while(getline(ss, tmp, ' ')){
            words.push_back(tmp);
        }
        //command: client_get file-path host-name (port-number) --> length = 3 or 4
		if (!(words.size() == 4 || words.size() == 3)){
			cout << "Invalid command format: "<< line << endl;
			continue;
		}
		//handle GET and POST only
		if (words[0] == "GET" || words[0] == "POST"){
			Request req;
			req.setType(words[0]);
			req.setUrl(words[1]);
			req.setProtocol("HTTP/1.1");
			req.addHeader("host",words[2]);
			if(words.size() == 3)
                req.setPort("80");
			else
                req.setPort(words[3]);
            requests.push_back(req);
		}else cout << "Invalid command format: "<< line << endl;
	}
	return true;
}
