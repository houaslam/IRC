#include "../includes/channel.hpp"

channel::channel(): name(""), topic(""){
 //itkol
	modes['i'] = 0;
	modes['t'] = 0;
	modes['k'] = 0;
	modes['o'] = 0;
	modes['l'] = 0;
}

channel::channel(string name): name(name){}

channel::channel(const channel& src){
    *this = src;
}

channel::~channel(){}

channel& channel::operator=(const channel& src){
    if (this != &src){
        this->name = src.name;
        this->clients = src.clients;
    }
    return *this;
}

            /*SETTERS*/
void    channel::setUser(Client &client_){
    clients.push_back(client_);
}
void channel::setChannelTopic(string &topic){
	this->topic = topic;
}

            /*GETTERS*/
string &channel::getChannelName(){
    return this->name;
}
string &channel::getChannelTopic(){
    return this->topic;
}