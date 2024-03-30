#include "../includes/channel.hpp"


channel::channel():name(""), topic(""){
 //itkol
	modes['i'] = "+i";
	modes['t'] = "+t";
	modes['k'] = "+k";
	modes['o'] = "+o";
	modes['l'] = "+l";
}

channel::channel(string name):name(name), topic(""){
    modes['i'] = "+i";
	modes['t'] = "+t";
	modes['k'] = "+k";
	modes['o'] = "+o";
	modes['l'] = "+l";
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
        this->admins = src.admins;
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
	this->admins.push_back(admin);
}

            /*GETTERS*/
string &channel::getChannelName(){
    return this->name;
}
string &channel::getChannelTopic(){
    return this->topic;
}
vector<int> channel::getChannelAdmins(){
    return this->admins;
}
map<char, string> &channel::getChannelModes(){
    return this->modes;
}