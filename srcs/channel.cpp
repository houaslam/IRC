#include "../includes/channel.hpp"


channel::channel():name(""), topic(""){
 //itkol
	modes['i'] = "+i";
	modes['t'] = "+t";
	modes['k'] = "";
	modes['o'] = "+o";
	modes['l'] = "";
    TopicSetter = "";
    TopicTime = "";
}

channel::channel(string name):name(name), topic(""){
    modes['i'] = "-i"; // only the guys who got invited and set the channel to +i
	modes['t'] = "+t"; //
	modes['k'] = ""; //password
	modes['o'] = "+o"; //admins kicking and banning ...
	modes['l'] = ""; 
    TopicSetter = "";
    TopicTime = "";
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
        this->TopicSetter = src.TopicSetter;
        this->TopicTime = src.TopicTime;
    }
    return *this;
}


            /*SETTERS*/
void    channel::setChannelUser(Client &client_){
    users.push_back(client_);
}void   channel::setChannelTopic(string &topic){
	this->topic = topic;
}void   channel::setChannelAdmin(string &admin){
	this->admins.push_back(admin);
}void   channel::setChannelInvited(string &invited){
	this->invited.push_back(invited);
}

            /*GETTERS*/
string          &channel::getChannelName(){
    return this->name;
}string         &channel::getChannelTopic(){
    return this->topic;
}vector<string> &channel::getChannelAdmins(){
    return this->admins;
}vector<Client> &channel::getChannelUsers(){
    return this->users;
}vector<string> &channel::getChannelInvited(){
    return this->invited;
}map<char, string>  &channel::getChannelModes(){
    return this->modes;
}
