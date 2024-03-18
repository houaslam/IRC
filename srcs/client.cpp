#include "../includes/client.hpp"
#include "../includes/server.hpp"

Client::Client():fd(1), nickname(""){}

Client::Client(string nickname,  Server server):nickname(nickname){
    socklen_t add_size = sizeof(server.get_addr_len());
    fd = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);
	if (fd <= 0)
		ft_error("CLIENT : ");
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