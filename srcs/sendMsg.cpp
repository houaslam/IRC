#include "../includes/server.hpp"

map<int, string> msgs(Client& client, string channel, string cmd){
	map<int, string> msg;
	// CHANNEL
	msg[IN_CHANNEL] = nbtoString(IN_CHANNEL) + " " + channel + " :You have joined too many channels";
	msg[ERR_NOTONCHANNEL] = nbtoString(ERR_NOTONCHANNEL) + " " + channel + ":You're not on that channel";
	msg[ERR_NOSUCHCHANNEL] = nbtoString(ERR_NOSUCHCHANNEL) + " " + channel + " :No such channel";
	msg[MODE_PLUS_I] = nbtoString(MODE_PLUS_I) + " " + channel + " :Cannot join channel (+i)";
	msg[ERR_CHANNELISFULL] = nbtoString(ERR_CHANNELISFULL) + " " + channel + " :Cannot join channel (+l)";
	msg[ERR_BADCHANNELKEY] = nbtoString(ERR_BADCHANNELKEY) + " " + channel + " :Cannot join channel (+k)";
	msg[RPL_NOTOPIC] = nbtoString(RPL_NOTOPIC) + " " + channel + " :No topic is set";
	// msg[RPL_TOPIC] = nbtoString(RPL_TOPIC) + " " + channel + " TOPIC///";
	msg[ERR_CHANOPRIVSNEEDED] = nbtoString(ERR_CHANOPRIVSNEEDED) + " " + channel + " :You're not channel operator";
	msg[ERR_USERONCHANNEL] = nbtoString(ERR_USERONCHANNEL) + " " + channel + " :is already on channel";
	msg[RPL_INVITING] = nbtoString(RPL_INVITING) + " " + client.getNickName() + " " + channel;
	msg[ERR_NOSUCHNICK] = nbtoString(ERR_NOSUCHNICK) + " " + channel + " :No such nick/channel";

	// NICK
	msg[NICK_NOT_GIVEN] = nbtoString(NICK_NOT_GIVEN) + " :Nickname not given";
	msg[NICK_IN_USE] =  nbtoString(NICK_IN_USE) + " " + client.getNickName() + " :Nickname is already in use";

	// PASS
	msg[NOT_REGISTRED] = nbtoString(NOT_REGISTRED) +  " :You have not registered";
	msg[ERR_NEEDMOREPARAMS] =  nbtoString(ERR_NEEDMOREPARAMS) + " " + cmd + " :Not enough parameters";
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

void ft_unknownCmd(Client &client, string &line){


    // string msg = getMsg(UNKNOW_CMD);
    string msg = msgs(client, "", line)[UNKNOW_CMD];
    string localhost = getLocalhost(client);
    sendMsg(client, localhost  + " " + client.getNickName() + " " + line + msg);

}

void justJoined(Client &client, channel &channel, string &line){

    string msg;
    string localhost = getLocalhost(client);

    if (channel.getChannelTopic().empty())
        msg = msgs(client, channel.getChannelName(), line)[RPL_NOTOPIC];
    else
        msg = channel.getChannelTopic(); //! 332

    sendMsg(client, localhost  + " " + client.getNickName() + " " + line + msg); ////later
    sendMsg(client, localhost + "353" + " " + client.getNickName() + " = "+ line + " :@" + client.getNickName()); //!353
    sendMsg(client, localhost + "366" + " " + client.getNickName() + " " + line + " :End of /NAMES list."); //! 366
}