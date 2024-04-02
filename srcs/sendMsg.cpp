#include "../includes/server.hpp"

map<int, string> msgs(Client& client, string channel, string cmd){
	map<int, string> msg;
	// CHANNEL
	msg[IN_CHANNEL] = nbtoString(IN_CHANNEL) + " " + channel + " :You have joined too many channels";
	msg[JOIN_NO_TOPIC] = nbtoString(JOIN_NO_TOPIC) + " " + channel + " :No topic is set";
	msg[ERR_NOTONCHANNEL] = nbtoString(ERR_NOTONCHANNEL) + " " + channel + ":You're not on that channel";
	msg[ERR_NOSUCHCHANNEL] = nbtoString(ERR_NOSUCHCHANNEL) + " " + channel + " :No such channel";

	// NICK
	msg[NICK_NOT_GIVEN] = nbtoString(NICK_NOT_GIVEN) + " :Nickname not given";
	msg[NICK_IN_USE] =  nbtoString(NICK_IN_USE) + " " + client.getNickName() + " :Nickname is already in use";

	// PASS
	msg[NOT_REGISTRED] = nbtoString(NOT_REGISTRED) +  " :You have not registered";
	msg[NOT_ENOUGH_PARA] =  nbtoString(NOT_ENOUGH_PARA) + " " + cmd + " :Not enough parameters";
	msg[ALREADY_REGISTERED] = nbtoString(ALREADY_REGISTERED) +  " :You may not reregister";
	msg[INCORRECT_PWD] = nbtoString(INCORRECT_PWD) + " :Password is incorrect";

	// GENERAL
	msg[UNKNOW_CMD] = nbtoString(UNKNOW_CMD) + " " + cmd +  " :Unknown command";

	return msg;
}

void sendMsg(Client& client, string str){
    str = str + "\r\n";
    send(client.get_fd(), getTime().c_str(), getTime().length(), 0);
    send(client.get_fd(), getLocalhost(client).c_str(), getLocalhost(client).length(), 0);
    send(client.get_fd(), str.c_str(), str.length() + 1, 0);
}

string getLocalhost(Client &client){
    return ":" + client.getNickName() + "!" + client.getUser() +"@localhost ";
}

void ft_unknownCmd(Client &client, int fd, string &line){


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

    fd++;
    if (channel.getChannelTopic().empty())
        msg = msgs(client, channel.getChannelName(), line)[JOIN_NO_TOPIC];
    else
        msg = channel.getChannelTopic();

    clearScreen(fd);
    sendMsg(client, localhost  + " " + client.getNickName() + " " + line + msg);
    sendMsg(client, localhost + "353" + " " + client.getNickName() + " = "+ line + " :@" + client.getNickName()); //!353
    sendMsg(client, localhost + "366" + " " + client.getNickName() + " " + line + " :End of /NAMES list."); //! 366
}