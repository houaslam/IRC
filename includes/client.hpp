# pragma once

#include "irc.hpp"

class client{
    private:
        int id;
        string nickname;
    public:
        client(string nickname, int id);
        client(client& src);
        client& operator=(client& client_);
        ~client();
};