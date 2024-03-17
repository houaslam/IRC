#include "../includes/client.hpp"

client::client(string nickname, int id): nickname(nickname), id(id){
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

