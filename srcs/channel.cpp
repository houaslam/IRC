#include "../includes/channel.hpp"

channel::channel(): name(""), topic(""), admin(1){
 //itkol
	modes['i'] = "";
	modes['t'] = "+t";
	modes['k'] = "";
	modes['o'] = "";
	modes['l'] = "";
}

channel::channel(string name): name(name), topic(""), admin(1), adminName(""){
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
        this->name = src.name;
        this->clients = src.clients;
    }
    return *this;
}

            /*SETTERS*/
void    channel::setChannelUser(Client &client_){
    clients.push_back(client_);
}
void channel::setChannelTopic(string &topic){
	this->topic = topic;
}
void channel::setChannelAdmin(int admin){ /// use int fd 
    this->admin = admin;
}

void channel::setChannelAdminName(string &admin){ /// use int fd 
    this->adminName = admin;
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
string &channel::getChannelAdminName(){
    return this->adminName;
}