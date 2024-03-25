#include "../includes/client.hpp"
#include "../includes/server.hpp"


Client::Client(): nickname(""), username(""), fd(1), isConnected(false){

}

Client::Client(int fd):nickname(""), username(""), fd(fd), isConnected(false){
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
}

string& Client::getNickName(void){
	return this->nickname;
}

string& Client::getUser(void){
	return this->username;
}

vector<string> &Client::getInChannel(){
	return this->inChannel;
}

int Client::get_fd(){
	return this->fd;
}

void Client::setFd(int fd){
	this->fd = fd;
}

void Client::setInChannel(string &str){
	inChannel.push_back(str);
}

void Client::setNickName(string nick){
	this->nickname = nick;
}

void Client::setUser(string nick){
	this->username = nick;
}

void Client::setHost(string nick){
	this->hostname = nick;
}

void Client::setRName(string nick){
	this->r_name = nick;
}


