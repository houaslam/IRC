#include "../includes/server.hpp"

void sendMsg(int fd, string str){
    str = str + "\r\n";
    send(fd, str.c_str(), str.length() + 1, 0);
}

string getMsg(string msgNumber){
    string msg = "";

    std::string numbers[] = {"405", "421", "431", "433", "451", "461", "462", "464", "332"};
    int i = 0;
    while (i < 9 && numbers[i].compare(msgNumber))
        i++;

    switch (i){
    case (0):
        msg = " :You have joined too many channels";
        break;
    case (1):
        msg = " :Unknown command";
        break;
    case (2):
        msg = " :Nickname not given";
        break;
    case (3):
        msg = " :Nickname is already in use";
        break;
    case (4):
        msg = " :You have not registered";
        break;
    case (5):
        msg = " :Not enough parameters";
        break;
    case (6):
        msg = " :You may not register";
        break;
    case (7):
        msg = " :Password is incorrect";
        break;
    case (8):
        msg = " :No topic is set";
        break;   
    default:
        break;
    }
    
    return msg;
}

string getLocalhost(Client &client){
    return ":" + client.getNickName() + "!" + client.getUser() +"@localhost ";
}

void ft_unknownCmd(Client &client, int fd, string &line){

    // vector<string> first = split(line, " ");

    string msg = getMsg(UNKNOW_CMD);
    string localhost = getLocalhost(client);

    sendMsg(fd, localhost + UNKNOW_CMD + " " + client.getNickName() + " " + line + msg);

}

void justJoined(Client &client, channel &channel, int fd, string &line){

    string msg;
    string localhost = getLocalhost(client);

    if (channel.getChannelTopic().empty())
        msg = getMsg(JOIN_NO_TOPIC);
    else
        msg = channel.getChannelTopic();

    // sendMsg(fd, localhost + client.getNickName() + " " + line + msg); // RECHECK
    sendMsg(fd, localhost + JOIN_NO_TOPIC + " " + client.getNickName() + " " + line + msg);
    sendMsg(fd, localhost + "353" + " " + client.getNickName() + " = "+ line + " :@" + client.getNickName());
    sendMsg(fd, localhost + "366" + " " + client.getNickName() + " " + line + " :End of /NAMES list.");

}