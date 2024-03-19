# pragma once

#include "server.hpp"
using namespace std;

class Server;

class Client{
    private:
        string nickname;
        int fd;
        int id;
    public:
        Client();
        Client(int fd);
        Client(const Client& src);
        Client& operator=(const Client& client_);
        ~Client();

        //SETTERS
        void setId(int id);
        void setFd(int fd);

        // GETTERS
        string& getNickName(void);
        int get_fd();
        int getId();
};


void user(vector<string> line);
void nick(string &nickname,string line, int fd);
string &withoutNewLine(string &line);
