#include "../includes/client.hpp"
#include "../includes/server.hpp"


Client::Client(): nickname("\v"), fd(1), id(0){}

Client::Client(int fd):nickname("\v"), fd(fd), id(0) {
    cout << "CLIENT WAS CREATED\n";
}

Client::Client(const Client& src){
    *this = src;
}

Client& Client::operator=(const Client& Client_){
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

int Client::getId(){
    return this->id;
}

void Client::setFd(int fd){
	this->fd = fd;
}

void Client::setId(int id){
	this->id = id;
}
