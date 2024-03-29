#include "../includes/server.hpp"

void sendMsg(Client& client, string str){
    str = str + "\r\n";
    send(client.get_fd(), getLocalhost(client).c_str(), getLocalhost(client).length(), 0);
    send(client.get_fd(), str.c_str(), str.length() + 1, 0);
}

string getLocalhost(Client &client){
    return ":" + client.getNickName() + "!" + client.getUser() +"@localhost ";
}

void ft_unknownCmd(Client &client, int fd, string &line){

    // vector<string> first = split(line, " ");

    (void)fd;
    // string msg = getMsg(UNKNOW_CMD);
    string msg = msgs(client, "", line)[UNKNOW_CMD];
    string localhost = getLocalhost(client);
    fd++;
    sendMsg(client, localhost  + " " + client.getNickName() + " " + line + msg);

}

void justJoined(Client &client, channel &channel, int fd, string &line){

    string msg;
    string localhost = getLocalhost(client);

    (void)fd;
    if (channel.getChannelTopic().empty())
        msg = msgs(client, channel.getChannelName(), line)[JOIN_NO_TOPIC];
    else
        msg = channel.getChannelTopic();

    // sendMsg(fd, localhost + client.getNickName() + " " + line + msg); // RECHECK
    sendMsg(client, localhost  + " " + client.getNickName() + " " + line + msg);
    sendMsg(client, localhost + "353" + " " + client.getNickName() + " = "+ line + " :@" + client.getNickName()); //!353
    sendMsg(client, localhost + "366" + " " + client.getNickName() + " " + line + " :End of /NAMES list."); //! 366
}