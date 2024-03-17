# pragma once

#include "irc.hpp"

using namespace std;

class client{
    private:
        int id;
        string nickname;
    public:
        client();
        client(string nickname, int id);
        client(client& src);
        client& operator=(client& client_);
        ~client();
        
        // GETTERS
        string& getNickName(void);
};