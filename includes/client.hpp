# pragma once

#include "server.hpp"
using namespace std;

class Server;

class Client{
    private:
        string nickname;
        int fd;
    public:
        Client();
        Client(string nickname, int fd);
        Client(Client& src);
        Client& operator=(Client& client_);
        ~Client();
        
        // GETTERS
        string& getNickName(void);
        int get_fd();
};