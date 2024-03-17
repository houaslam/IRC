#include "../includes/client.hpp"

client::client(): id(0),nickname(""){}

client::client(string nickname, int id):id(id) ,nickname(nickname){
    cout << "CLIENT WAS CREATED\n";
}

client::client(client& src){
    *this = src;
}

client& client::operator=(client& client_){
    if (this != &client_){
        this->id = client_.id;
        this->nickname = client_.nickname;
    }
    return *this;
}

client::~client(){
    cout << "BYE BYE\n";
}

string& client::getNickName(void){
    return this->nickname;
}