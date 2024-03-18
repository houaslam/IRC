#include "../includes/client.hpp"
#include "../includes/server.hpp"


Client::Client():fd(1), nickname(""){}

Client::Client(string nickname,  int fd):fd(fd) , nickname(nickname){
    cout << "CLIENT WAS CREATED\n";
}

Client::Client(Client& src){
    *this = src;
}

Client& Client::operator=(Client& Client_){
    if (this != &Client_){
        this->fd = Client_.fd;
        this->nickname = Client_.nickname;
    }
    return *this;
}

Client::~Client(){
    // cout << "BYE BYE\n";
}

string& Client::getNickName(void){
    return this->nickname;
}

int Client::get_fd(){
    return this->fd;
}