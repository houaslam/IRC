#include "../includes/client.hpp"
#include "../includes/server.hpp"

map<int, string> msgs(Client& client, string channel, string cmd){
	map<int, string> msg;
	// CHANNEL
	msg[IN_CHANNEL] = nbtoString(client.get_fd()) + " " + channel + " :You have joined too many channels";
	msg[JOIN_NO_TOPIC] = nbtoString(client.get_fd()) + " " + channel + " :No topic is set";
	msg[ERR_NOTONCHANNEL] = nbtoString(client.get_fd()) + " " + channel + ":You're not on that channel";
	msg[ERR_NOSUCHCHANNEL] = nbtoString(client.get_fd()) + " " + channel + " :No such channel";

	// NICK
	msg[NICK_NOT_GIVEN] = nbtoString(client.get_fd()) + " :Nickname not given";
	msg[NICK_IN_USE] =  nbtoString(client.get_fd()) + " " + client.getNickName() + " :Nickname is already in use";

	// PASS
	msg[NOT_REGISTRED] = nbtoString(client.get_fd()) +  " :You have not registered";
	msg[NOT_ENOUGH_PARA] =  nbtoString(client.get_fd()) + " " + cmd + " :Not enough parameters";
	msg[ALREADY_REGISTERED] = nbtoString(client.get_fd()) +  " :You may not reregister";
	msg[INCORRECT_PWD] = nbtoString(client.get_fd()) + " :Password is incorrect";

	// GENERAL
	msg[UNKNOW_CMD] = nbtoString(client.get_fd()) + " " + cmd +  " :Unknown command";

	return msg;
}


Client::Client(): nickname(""), username(""), fd(1), inChannel(""), isConnected(false){

}

Client::Client(int fd):nickname(""), username(""), fd(fd), inChannel(""), isConnected(false){
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

string &Client::getInChannel(){
	return this->inChannel;
}

int Client::get_fd(){
	return this->fd;
}

void Client::setFd(int fd){
	this->fd = fd;
}

void Client::setInChannel(string &inChannel){
	this->inChannel = inChannel;
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


