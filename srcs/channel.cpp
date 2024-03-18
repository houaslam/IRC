#include "../includes/channel.hpp"

channel::channel(string name): name(name){
    cout << "NEW CHANNEL UNDER " << name << " NAME WAS CREATED\n";
}

channel::channel(channel& src){
    *this = src;
}

channel::~channel(){
    cout << name << " CHANNEL HAS BEEN DELETED\n";
}

channel& channel::operator=(channel& src){
    if (this != &src){
        this->name = src.name;
        this->clients = src.clients;
    }
    return *this;
}

void    channel::add_user(client client_){
    clients.push_back(client_);
    cout << "WELCOME TO " << this->name << " CHANNEL\n";
}
