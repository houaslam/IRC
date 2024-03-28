#include "../includes/channel.hpp"

channel::channel(): admin(1), name(""), topic(""){
 //itkol
	modes['i'] = "";
	modes['t'] = "+t";
	modes['k'] = "";
	modes['o'] = "";
	modes['l'] = "";
}

channel::channel(string name):admin(1), name(name), topic(""){
    modes['i'] = "";
	modes['t'] = "+t";
	modes['k'] = "";
	modes['o'] = "";
	modes['l'] = "";
}

channel::channel(const channel& src){
    *this = src;
}

channel::~channel(){}

channel& channel::operator=(const channel& src){
    if (this != &src){
        this->users = src.users;
        this->name = src.name;
        this->topic = src.topic;
        this->admin = src.admin;
        this->modes = src.modes;
    }
    return *this;
}


            /*SETTERS*/
void    channel::setChannelUser(Client &client_){
    users.push_back(client_);
}
void channel::setChannelTopic(string &topic){
	this->topic = topic;
}
void channel::setChannelAdmin(int admin){
	this->admin = admin;
}

            /*GETTERS*/
string &channel::getChannelName(){
    return this->name;
}
string &channel::getChannelTopic(){
    return this->topic;
}
int channel::getChannelAdmin(){
    return this->admin;
}
map<char, string> &channel::getChannelModes(){
    return this->modes;
}