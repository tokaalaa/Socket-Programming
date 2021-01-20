#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <vector>
#include "./Request.h"
using namespace std;

class Parser
{
    public:
        bool parse_commands(string file);
        vector<Request> get_requests(){
            return this->requests;
        }
    protected:

    private:
    vector<Request> requests;
};

#endif // PARSER_H
