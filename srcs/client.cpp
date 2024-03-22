#include "../includes/client.hpp"
#include "../includes/server.hpp"

bool check_users(Server& server,string line , int ref){
    map<int , class Client> save = server.getCLients();
    for(map<int, class Client>::iterator it = save.begin(); it != save.end(); it++){
        if (!line.compare(it->second.getNickName()) && it->second.get_fd() != ref)
            return true;
    }
    return false;
}

bool checkChannels(Server& server,string line){
    for (vector<channel>::iterator i = server.getChannels().begin(); i < server.getChannels().end(); i++){
        if (i->getChannelName() == line){
            return false;
        }
    }
    return true;
}

void user(Server& server, string line, int fd){
    line = line.substr(4);
    line = strtrim(line);
    if (line.empty()){
        server.get_addr();
    fd = 0;
    }

}

void nick(Server& server, string line, int fd){ //done
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
        if (check_users(server, line, fd))
            send(fd, "nickname alredy used by another user\n", 38, 0);
        else{
            server.getCLients()[fd].setNickName(line);
            string send = "ur nickname was set to " + server.getCLients()[fd].getNickName();
            sendMsg(fd, send + "\n");
        }
    }
}

void join(Server& server, string line, int fd){ // [X]
    server.getServerName();
    line = line.substr(4);
    line = strtrim(line);

    if (line.empty()){
        sendMsg(fd,":"+ server.getCLients()[fd].getNickName() + "!" /*getfirstuser*/ + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters\n");
    }
    else{
        // if (isChannelExist(&line))
    }
        // send(fd, "Your nickname is fadermou\n", 26, 0);
    // if (server.getUser)
    
        
}

Client::Client(): nickname("\v"), fd(1), id(0), inChannel(false){

}

Client::Client(int fd):nickname("\v"), fd(fd), id(0), inChannel(false){
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

bool Client::getInChannel(){
    return this->inChannel;
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

void Client::setInChannel(bool inChannel){
    this->inChannel = inChannel;
}

void Client::setNickName(string nick){
    this->nickname = nick;
}