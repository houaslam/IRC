#include "../includes/client.hpp"
#include "../includes/server.hpp"


bool check_users(Server& server,string line){
    map<int , class Client> save = server.getCLients();
    for(map<int, class Client>::iterator it = save.begin(); it != save.end(); it++){
        if (!line.compare(it->second.getNickName()))
            return true;
    }
    return false;
}

void user(vector<string> line){
    (void)line;
}

void nick(Server& server, string line, int fd){
    line = line.substr(4);
    line = strtrim(line);
    if (line.empty()){
        if(server.getCLients()[fd].getNickName().compare("\v"))
            send(fd, "NICKNAME ALREADY SET\n", 22, 0);
        else
            send(fd, "No nickname is given\n", 21, 0);
    }
    else
    {
        if (check_users(server, line))
            send(fd, "nickname alredy used by another user\n", 38, 0);
        else{
            server.getCLients()[fd].setNickName(line);
            string send = "ur nickname was set to " + server.getCLients()[fd].getNickName();
            sendMsg(fd,send+ "\n");
        }
    }
}


Client::Client(): nickname("\v"), fd(1), id(0){

}

Client::Client(int fd):nickname("\v"), fd(fd), id(0) {
    // cout << "CLIENT WAS CREATED\n";
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
    // cout << "BYE BYE\n";
}

string& Client::getNickName(void){
    return this->nickname;
}

int Client::get_fd(){
    return this->fd;
}

int Client::getId(){
    return this->id;
}

void Client::setFd(int fd){
	this->fd = fd;
}

void Client::setId(int id){
	this->id = id;
}

void Client::setNickName(string nick){
    this->nickname = nick;
}