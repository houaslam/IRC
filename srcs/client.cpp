#include "../includes/client.hpp"
#include "../includes/server.hpp"

bool isAdmin(string admin, channel &channel){
	
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++){
		if (channel.getChannelAdmins()[i] == admin)
			return true;
	}
	return false;
}

bool isInvited(string invited, channel &channel){
	
	for (size_t i = 0; i < channel.getChannelInvited().size(); i++){
		if (channel.getChannelInvited()[i] == invited)
			return true;
	}
	return false;
}


map<int, string> msgs(Client& client, string channel, string cmd){
	map<int, string> msg;
	// CHANNEL
	msg[IN_CHANNEL] = nbtoString(IN_CHANNEL) + " " + channel + " :You have joined too many channels";
	msg[JOIN_NO_TOPIC] = nbtoString(JOIN_NO_TOPIC) + " " + channel + " :No topic is set";
	msg[ERR_NOTONCHANNEL] = nbtoString(ERR_NOTONCHANNEL) + " " + channel + ":You're not on that channel";
	msg[ERR_NOSUCHCHANNEL] = nbtoString(ERR_NOSUCHCHANNEL) + " " + channel + " :No such channel";
	msg[MODE_PLUS_I] = nbtoString(MODE_PLUS_I) + " " + channel + " :Cannot join channel (+i)";
	msg[ERR_CHANNELISFULL] = nbtoString(ERR_CHANNELISFULL) + " " + channel + " :Cannot join channel (+l)";
	msg[ERR_BADCHANNELKEY] = nbtoString(ERR_BADCHANNELKEY) + " " + channel + " :Cannot join channel (+k)";

	// NICK
	msg[NICK_NOT_GIVEN] = nbtoString(NICK_NOT_GIVEN) + " :Nickname not given";
	msg[NICK_IN_USE] =  nbtoString(NICK_IN_USE) + " " + client.getNickName() + " :Nickname is already in use";

	// PASS
	msg[NOT_REGISTRED] = nbtoString(NOT_REGISTRED) +  " :You have not registered";
	msg[NOT_ENOUGH_PARA] =  nbtoString(NOT_ENOUGH_PARA) + " " + cmd + " :Not enough parameters";
	msg[ALREADY_REGISTERED] = nbtoString(ALREADY_REGISTERED) +  " :You may not reregister";
	msg[INCORRECT_PWD] = nbtoString(INCORRECT_PWD) + " :Password is incorrect";

	// GENERAL
	msg[UNKNOW_CMD] = nbtoString(UNKNOW_CMD) + " " + cmd +  " :Unknown command";

	return msg;
}


Client::Client(): nickname("user"), username(""), fd(1), isConnected(false){

}

Client::Client(int fd):nickname("user"), username(""), fd(fd), isConnected(false){
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


