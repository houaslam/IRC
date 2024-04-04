#include "../includes/client.hpp"
#include "../includes/server.hpp"

// PASS <password>
void    pass(Server& server, string line , int fd){
	line = line.substr(4);
	line = strtrim(line);

	vector<string> res = split(line, " ");
	if (res.size() == 1 && !res[0].compare(server.get_password())){
		server.getCLients()[fd].pass = true;
	}
	else{
		if (server.getCLients()[fd].pass == false)
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "", "")[INCORRECT_PWD]); 
	}
}

void bot(Server& server, string line, int fd){
	// 	if (server.getCLients()[fd].getNickName().empty()){
	// 	sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NOT_REGISTRED]); 
	// 	return ;
	// }
	line = line.substr(3);
	line = strtrim(line);
	if (line.empty()){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[ERR_NEEDMOREPARAMS]); 
		return ;
	}
	else{
		vector<string> res = split(line, " ");
		if (res.size() != 4){
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[ERR_NEEDMOREPARAMS]); 
			return ;
		}
		send(fd, "WELCOME TO PIXER SERVER BOT\n", 29, 0);
	 // MAKE THE FORMULA USING THE PARAMETERS PROVIDED 
	 
	}
}

// NICK <nickname>
void nick(Server& server, string line, int fd){
	if (server.getCLients()[fd].pass == false){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "", "")[NOT_REGISTRED]);
		return ;
	}

	line = line.substr(4);
	line = strtrim(line);

	if (line.empty()){
		if (!server.getCLients()[fd].getNickName().empty())
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "","", "")[NICK_NOT_GIVEN]);

		else
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "","", "")[NICK_NOT_GIVEN]);
	}
	else{
		vector<string> res = split(line, " ");
		if (check_users(server, res[0], fd))
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NICK_IN_USE]);

		else{
			if (server.getCLients()[fd].getNickName() != ""){
				server.getCLients()[fd].setNickName(res[0]);
				sendMsg(server.getCLients()[fd], " NICK :" + res[0]);
			}
			server.getCLients()[fd].setNickName(res[0]);
		}
	}
}

// USER <username> <hostname> <servername> <realname>
void user(Server& server, string line, int fd){
	if (server.getCLients()[fd].getNickName().empty()){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NOT_REGISTRED]);
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[ERR_NEEDMOREPARAMS]); 

		return ;
	}
	else{
		vector<string> res = split(line, " ");
		if (res.size() != 4){
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[ERR_NEEDMOREPARAMS]); 

			return ;
		}
		server.getCLients()[fd].setUser(res[0]);
		server.getCLients()[fd].setHost(res[1]);
		server.setServerName(res[2]);
		server.getCLients()[fd].setRName(res[3]);
	}
	server.getCLients()[fd].isConnected = isConnected(server, fd);
	if (server.getCLients()[fd].isConnected){
		sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 001 " + server.getCLients()[fd].getNickName() + " :Welcome to the Internet Relay Network");
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 002 " + server.getCLients()[fd].getNickName() + " :Your host is " + server.getServerName() + " ");
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 003 " + server.getCLients()[fd].getNickName() + " :This server was created 0 ");
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 004 " + server.getCLients()[fd].getNickName() + " :" + server.getServerName() + " 1.1 More info");

	}
}

// JOIN <channels>
void join(Server& server, string line, int fd){ 
	Client &client = server.getCLients()[fd];
    line = line.substr(4);
    line = strtrim(line);

    if (line.empty())
		return sendMsg(client, msgs(client, "", "", "JOIN")[ERR_NEEDMOREPARAMS]); 
    vector<string> spl = split(line, " ");
	if (spl.size() == 1)
		spl.push_back("");
    if (!isChannelExist(server.getChannels(), split(line, " ")[0])) /*doesn't exist*/{
        channel channel(spl[0]);

		client.setInChannel(spl[0]);
		channel.setChannelUser(client);
		channel.setChannelAdmin(client.getNickName());
		server.setChannel(channel, spl[0], client);
		justJoined(client, channel, spl[0]); //!
    }
	else{
		channel &channel = server.getChannels()[spl[0]];
		if (isInChannel(client, spl[0])) ///LATER
			return ;
		if (!channel.getChannelModes()['l'].empty() && channel.getChannelModes()['l'] != "-l" && channel.getChannelUsers().size() > (size_t)atoi(channel.getChannelModes()['l'].c_str()))
			return sendMsg(client, msgs(client, "", "", "")[ERR_CHANNELISFULL]); 
		if (!channel.getChannelModes()['k'].empty() && channel.getChannelModes()['k'] != "-k" && spl[1] != channel.getChannelModes()['k'])
			return sendMsg(client, msgs(client, "", "", "")[ERR_BADCHANNELKEY]); 
		if (/*!isAdmin(client.getNickName(), channel) &&*/ !isInvited(client.getNickName(), channel) && channel.getChannelModes()['i'] == "+i")
			return sendMsg(client, msgs(client, "", "", "")[ERR_INVITEONLYCHAN]); 
		client.setInChannel(spl[0]);
		channel.setChannelUser(client);
		justJoined(client, channel, spl[0]); //!
	}
}


// INVITE <nick> [<channel>]
void invite(Server& server, string line, int fd){
	Client &client = server.getCLients()[fd];
	line = line.substr(6);
    line = strtrim(line);

    if (line.empty() || split(line, " ").size() < 2)
		return sendMsg(client, msgs(client, "", "", "INVITE")[ERR_NEEDMOREPARAMS]); 
	
	vector<string> spl = split(line, " ");

	string &invited = spl[0];
    if (!isChannelExist(server.getChannels(), spl[1]))
		return sendMsg(client, msgs(client, "", spl[1], "")[ERR_NOSUCHCHANNEL]); 
	
	channel &channel = server.getChannels()[spl[1]];
	if (!isInChannel(client, channel.getChannelName()))
		return sendMsg(client, msgs(client, "", channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 
	if (!isAdmin(client.getNickName(), channel))
		return sendMsg(client, msgs(client, "", channel.getChannelName(), "")[ERR_CHANOPRIVSNEEDED]); 
	if (isInChannelString(invited, channel))
		return sendMsg(client, msgs(client, invited, channel.getChannelName(), "")[ERR_USERONCHANNEL]); 
	if (!check_users(server, invited, fd))
		return sendMsg(client, msgs(client, invited, "", "")[ERR_NOSUCHNICK]); 

	channel.setChannelInvited(invited);
	sendMsg(client, msgs(client, invited, channel.getChannelName(), "")[RPL_INVITING]); 
}

// TOPIC 
void	topic(Server &server, string line, int fd){// [X]
	Client &client = server.getCLients()[fd];
    line = line.substr(5);
    line = strtrim(line);

    if (strtrim(line).empty())
		return sendMsg(client, msgs(client, "","", "TOPIC")[ERR_NEEDMOREPARAMS]); 
	
	vector<string> spl = split(line, " ");

    if (!isChannelExist(server.getChannels(), spl[0]))
		return sendMsg(client, msgs(client,"", spl[0], "")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]]; 
	if (!isInChannel(server.getCLients()[fd], spl[0]))
		return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 

	string topic = line.substr(spl[0].size());

	if (topic.empty())
	{
		if (channel.getChannelTopic().empty())
			return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[RPL_NOTOPIC]); 
		send(fd," :show old topic\n", 18, 0);
	}
	else{
		if (channel.getChannelModes()['t'] == "+t" &&
			!isAdmin(client.getNickName(), channel))
				return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[ERR_CHANOPRIVSNEEDED]); 
		else
			channel.setChannelTopic(topic);
	}
}

void	mode(Server &server, string line, int fd){
    line = line.substr(4);
    line = strtrim(line);
	Client &client = server.getCLients()[fd];
    if (line.empty() || split(line, " ").size() < 2){
		sendMsg(client, msgs(client, "","", "MODE")[ERR_NEEDMOREPARAMS]); 
        return ;
    }
	vector<string> spl = split(line, " ");
	if (!isChannelExist(server.getChannels(), spl[0]))
		return sendMsg(client, msgs(client,"" , spl[0], "")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]];
	
	if (!isInChannel(client, spl[0]))
		return sendMsg(client, msgs(client, "",channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 
	else if (!isAdmin(client.getNickName(), channel))
		return sendMsg(client, msgs(client, "",channel.getChannelName(), "")[ERR_CHANOPRIVSNEEDED]); 
	else if (spl[1][0] == '+' || spl[1][0] == '-')
	{
		if (spl.size() < 3)
			spl.push_back("");
		if ((spl[1].find("o") != string::npos || spl[1].find("k") != string::npos || spl[1].find("l") != string::npos) && spl[2].empty())
			return sendMsg(client, msgs(client, "","", "MODE")[ERR_NEEDMOREPARAMS]); 
		else
			fillMode(spl[1], spl[2], channel, server, client);
				// sendMsg(client, msgs(client, "","", "MODE")[ERR_NEEDMOREPARAMS]); 
	}
	else
		sendMsg(client, msgs(client ,"" , "", "MODE")[ERR_NEEDMOREPARAMS]); 
	
}

// <target>{,<target>} <text to be sent>
void	privmsg(Server &server, string line, int fd){
	line = line.substr(7);
    line = strtrim(line);
	Client &client = server.getCLients()[fd];
    if (line.empty())
		return sendMsg(client, msgs(client, "","", "PRIVMSG")[ERR_NORECIPIENT]);
	vector<string> spl = split(line, " ");
	if (!isChannelExist(server.getChannels(), spl[0]) && !check_users(server, spl[0], fd))
		return sendMsg(client, msgs(client,"" , spl[0], "")[ERR_NOSUCHNICK]);
	if (spl.size() == 1)
		spl.push_back("");
	if(spl[1][0] != ':')
		return (sendMsg(client, msgs(client ,"" , "", "PRIVMSG")[ERR_NEEDMOREPARAMS])); 
	string msg = getPRVMsg(line);
	if (msg.empty())
		return (sendMsg(client, msgs(client ,"" , "", "")[ERR_NOTEXTTOSEND]));
	if (check_users(server, spl[0], fd))
	{
		sendMsg(client, msgs(client , spl[0], "", "")[RPL_AWAY]);
		Client target = getClientString(server.getCLients(), spl[0]);
		msg = "[" + client.getNickName() + "] " + msg + "\r\n";
		send(target.get_fd(), msg.c_str(), msg.size(), 0);
		return;
	}
	if (isChannelExist())
	// channel &channel = server.getChannels(spl[0]);
	// if (channel.getChannelModes()['i'] == "+i" && isInvited(client.getNickName(), channel))
	// 	return sendMsg(client, msgs(client,"" , spl[0], "")[ERR_CANNOTSENDTOCHAN]);

}
///CHECK BEFORE EVERY COMMAND IF ITS THE SAME USER 
///RETURN FALSE WHEN REMOVING A USER SO WE WILL DELETE THEIR FD
///ADD PART
/*
ERR_NOSUCHNICK (401) //
ERR_NOSUCHSERVER (402) //!X
ERR_NOSUCHCHANNEL 403 ->doesn't exist //
ERR_CANNOTSENDTOCHAN (404) -> when it's +i //
ERR_TOOMANYTARGETS (407)
ERR_NORECIPIENT (411) //
ERR_NOTEXTTOSEND (412) //
ERR_NOTOPLEVEL (413)
ERR_WILDTOPLEVEL (414)
RPL_AWAY (301) //
475 +L
*/
// string getMsg(int msgNumber, Server& server, string channel, int fd){
// 	return(   msgs()[msgNumber]);
// }

