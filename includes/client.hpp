# pragma once

#include "server.hpp"
using namespace std;

class Server;

class Client{
    private:
        string nickname;
        string user;
        int fd;
        int id;
        string inChannel;
    public:
        Client();
        Client(int fd);
        Client(const Client& src);
        Client& operator=(const Client& client_);
        ~Client();

        //SETTERS
        void setId(int id);
        void setFd(int fd);
        void setNickName(string nick);
        void setInChannel(string &inChannel);

        // GETTERS
        string& getNickName(void);
        string& getUser(void);
        string &getInChannel(void);
        int get_fd();
        int getId();
};


void user(Server& server, string line, int fd);
void nick(Server& server ,string line, int fd);
string &withoutNewLine(string &line);
void join(Server& server, string line, int fd);
