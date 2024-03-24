#include "../includes/channel.hpp"

channel::channel(): name(""), topic(""){
 //itkol
	modes['i'] = 0;
	modes['t'] = 0;
	modes['k'] = 0;
	modes['o'] = 0;
	modes['l'] = 0;
	cout << "NEW CHANNEL UNDER " << name << " NAME WAS CREATED\n";
}

channel::channel(string name): name(name){}

channel::channel(const channel& src){
    *this = src;
}

channel::~channel(){
    cout << name << " CHANNEL HAS BEEN DELETED\n";
}

channel& channel::operator=(const channel& src){
    if (this != &src){
        this->name = src.name;
        this->clients = src.clients;
    }
    return *this;
}

void    channel::addUser(Client &client_){
    clients.push_back(client_);
    cout << "WELCOME TO " << this->name << " CHANNEL\n";
}

string &channel::getChannelName(){
    return this->name;
}
string &channel::getChannelTopic(){
    return this->topic;
}