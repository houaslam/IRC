# pragma once

#include "server.hpp"
using namespace std;

class Server;

class Client{
    private:
        int fd;
        string nickname;
    public:
        Client();
        Client(string nickname, Server server);
        Client(Client& src);
        Client& operator=(Client& client_);
        ~Client();
        
        // GETTERS
        string& getNickName(void);
        int get_fd();
};