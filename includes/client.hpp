# pragma once

#include "server.hpp"
using namespace std;

class client{
    private:
        string nickname;
        int id;
    public:
        client(string nickname, int id);
        client(client& src);
        client& operator=(client& client_);
        ~client();
};