#include "../includes/server.hpp"

map<int, string> msgs(Client& client,string nickname,string channel, string cmd){
	map<int, string> msg;
	// CHANNEL
	msg[ERR_TOOMANYCHANNELS] = nbtoString(ERR_TOOMANYCHANNELS) + " " + channel + " :You have joined too many channels";
	msg[ERR_NOTONCHANNEL] = nbtoString(ERR_NOTONCHANNEL) + " " + channel + " :You're not on that channel";
	msg[ERR_NOSUCHCHANNEL] = nbtoString(ERR_NOSUCHCHANNEL) + " " + channel + " :No such channel";
	msg[ERR_INVITEONLYCHAN] = nbtoString(ERR_INVITEONLYCHAN) + " " + channel + " :Cannot join channel (+i)";
	msg[ERR_CHANNELISFULL] = nbtoString(ERR_CHANNELISFULL) + " " + channel + " :Cannot join channel (+l)";
	msg[ERR_BADCHANNELKEY] = nbtoString(ERR_BADCHANNELKEY) + " " + channel + " :Cannot join channel (+k)";
	msg[RPL_NOTOPIC] = nbtoString(RPL_NOTOPIC) + " " + channel + " :No topic is set";
	msg[RPL_TOPIC] = nbtoString(RPL_TOPIC) + " " + client.getNickName() + " " + channel + " " + nickname;

	msg[ERR_CHANOPRIVSNEEDED] = nbtoString(ERR_CHANOPRIVSNEEDED) + " " + channel + " :You're not channel operator";
	msg[ERR_USERONCHANNEL] = nbtoString(ERR_USERONCHANNEL) + " " + nickname + "" + channel + " :is already on channel";
	msg[RPL_INVITING] = nbtoString(RPL_INVITING)  + " " + client.getNickName() + " " + nickname + " " + channel;
	msg[ERR_NOSUCHNICK] = nbtoString(ERR_NOSUCHNICK) + " " + nickname + " :No such nick/channel";
	msg[ERR_NORECIPIENT] = nbtoString(ERR_NORECIPIENT) + " " + nickname + " :No recipient given (" + cmd + ")";
	msg[ERR_CANNOTSENDTOCHAN] = nbtoString(ERR_CANNOTSENDTOCHAN) + " " + nickname + " " + channel + " :Cannot send to channel";
	msg[ERR_NOTEXTTOSEND] = nbtoString(ERR_NOTEXTTOSEND) + " :No text to send";
	msg[RPL_AWAY] = nbtoString(RPL_AWAY) + " " + client.getNickName() + " " + nickname + " :Your message has been delivered";
	msg[ERR_USERNOTINCHANNEL] = nbtoString(ERR_USERNOTINCHANNEL) + " " + nickname + " " + channel + " :They aren't on that channel";

	// NICK
	msg[NICK_NOT_GIVEN] = nbtoString(NICK_NOT_GIVEN) + " :Nickname not given";
	msg[NICK_IN_USE] =   " : Nickname is already in use";
	msg[ERR_ERRONEUSNICKNAME] =  " :Erroneus nickname";

	// PASS
	msg[NOT_REGISTRED] = nbtoString(NOT_REGISTRED) +  " :You have not registered";
	msg[ERR_NEEDMOREPARAMS] =  nbtoString(ERR_NEEDMOREPARAMS) + " " + cmd + " :Not enough parameters";
	msg[ALREADY_REGISTERED] = " : You may not reregister";
	msg[INCORRECT_PWD] =  " : Password is incorrect";

	// GENERAL
	msg[UNKNOW_CMD] = nbtoString(UNKNOW_CMD) + " " + cmd +  " :Unknown command";

	return msg;
}

void sendMsg(Client& client, string str){
    str = getLocalhost(client) + str + "\r\n";
    send(client.get_fd(), str.c_str(), str.length() , 0);
}

string getLocalhost(Client &client){
    return ":" + client.getNickName() + "!" + client.getUser() +"@localhost ";
}

void justJoined(Client &client, channel &channel, string &line){
	sendMsg(client, "JOIN " + channel.getChannelName());
    if ((!channel.getChannelTopic().empty())){
		sendMsg(client, msgs(client, channel.getChannelTopic(), channel.getChannelName(), "")[RPL_TOPIC]);
		string msg = getLocalhost(client) + "333 " + client.getNickName() + " " + channel.getChannelName() + " " + channel.TopicSetter + " " + channel.TopicTime + "\r\n";
		send(client.get_fd(), msg.c_str(), msg.size(), 0); //! 333
	}
	
	string nicknames;
	vector<string>::iterator it;
	
	for (size_t i = 0; i < channel.getChannelAdmins().size() ; i++)
	{
		nicknames += "@" + channel.getChannelAdmins()[i];
			nicknames += " ";
	}

	for (size_t i = 0; i < channel.getChannelUsers().size() ; i++)
	{
		it = find(channel.getChannelAdmins().begin(), channel.getChannelAdmins().end(), channel.getChannelUsers()[i].getNickName());
		if (it == channel.getChannelAdmins().end())
		{
			nicknames += channel.getChannelUsers()[i].getNickName();
				nicknames += " ";
		}
	}
    sendMsg(client , "353 " + client.getNickName() + " = "+ line + " :" + nicknames); //!353
	sendMsg(client , "366 " + client.getNickName() + " " + line + " :End of /NAMES list."); //! 366

}
