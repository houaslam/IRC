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
	// server.getCLients()[fd].isConnected = isConnected(server, fd);
	// if (server.getCLients()[fd].isConnected){
		sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 001 " + server.getCLients()[fd].getNickName() + " :Welcome to the Internet Relay Network");
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 002 " + server.getCLients()[fd].getNickName() + " :Your host is " + server.getServerName() + " ");
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 003 " + server.getCLients()[fd].getNickName() + " :This server was created " + getTime());
    	sendMsg(server.getCLients()[fd],":" + server.getServerName() + " 004 " + server.getCLients()[fd].getNickName() + " :" + server.getServerName() + " 1.1 More info");

	// }
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
		channel.setChannelAdmin(client.getNickName());
		server.setChannel(channel, spl[0], client);
		justJoined(client, channel, spl[0]); //!
    }
	else{
		channel &channel = server.getChannels()[spl[0]];
		if (isInChannel(client, spl[0])) ///LATER
			return justJoined(client, channel, spl[0]);
		if (!channel.getChannelModes()['l'].empty() && channel.getChannelModes()['l'] != "-l" && channel.getChannelUsers().size() >= (size_t)atoi(channel.getChannelModes()['l'].c_str()))
			return sendMsg(client, msgs(client, "", "", "")[ERR_CHANNELISFULL]); 
		if (!channel.getChannelModes()['k'].empty() && channel.getChannelModes()['k'] != "-k" && spl[1] != channel.getChannelModes()['k'])
			return sendMsg(client, msgs(client, "", "", "")[ERR_BADCHANNELKEY]); 
		if (/*!isAdmin(client.getNickName(), channel) &&*/ !isInvited(client.getNickName(), channel) && channel.getChannelModes()['i'] == "+i")
			return sendMsg(client, msgs(client, "", "", "")[ERR_INVITEONLYCHAN]); 
		for (size_t i = 0; i < channel.getChannelInvited().size(); i++)
			if (client.getNickName() == channel.getChannelInvited()[i])
				channel.getChannelInvited().erase(channel.getChannelInvited().begin() + i);
		client.setInChannel(spl[0]);
		channel.setChannelUser(client);
		justJoined(client, channel, spl[0]); //! ///

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
	Client reciever = getClientString(server.getCLients(), invited);
	sendMsg(reciever, "INVITE " + invited + " :#" + channel.getChannelName());

}

// TOPIC 
void	topic(Server &server, string line, int fd){
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
		if ((spl[1].find("o") != string::npos) && spl[2].empty())
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
		sendMsg(target,  ":" + client.getNickName() + " PRIVMSG " + target.getNickName() + " :" + msg);
	}//:user1!user@host PRIVMSG #channel :Hello, everyone!


	else if(isChannelExist(server.getChannels(), spl[0]))
	{
		channel &channel = server.getChannels()[spl[0]];
		if (!isInChannel(server.getCLients()[fd], spl[0]))
			return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 
		if ((channel.getChannelModes()['i'] == "+i" && (!isInvited(client.getNickName(), channel) && !isInChannel(client, spl[0]))) || \
			(!channel.getChannelModes()['k'].empty() && channel.getChannelModes()['k']  != "-k" && !isInChannel(client, spl[0])))
				return sendMsg(client, msgs(client,"" , spl[0], "")[ERR_CANNOTSENDTOCHAN]);
		for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
		{
			if (fd != channel.getChannelUsers()[i].get_fd())
				sendMsg(channel.getChannelUsers()[i], ":" + client.getNickName() + " PRIVMSG #" + channel.getChannelName() + " :" + msg);
		}
	}
}

void	part(Server &server, string line, int fd){
	Client &client = server.getCLients()[fd];
    line = line.substr(4);
    line = strtrim(line);

    if (strtrim(line).empty())
		return sendMsg(client, msgs(client, "","", "PART")[ERR_NEEDMOREPARAMS]); 
	
	vector<string> spl = split(line, " ");

    if (!isChannelExist(server.getChannels(), spl[0]))
		return sendMsg(client, msgs(client,"", spl[0], "")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]]; 
	if (!isInChannel(server.getCLients()[fd], spl[0]))
		return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 
	unsetChannelUser(channel, client);
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
		sendMsg(channel.getChannelUsers()[i], "PART #" + channel.getChannelName());
}

//kick <channel> <user> <reason>
void	kick(Server &server, string line, int fd){ 
	Client &client = server.getCLients()[fd];
    line = line.substr(4);
    line = strtrim(line);

    if (strtrim(line).empty() || split(line, " ").size() < 2)
		return sendMsg(client, msgs(client, "","", "KICK")[ERR_NEEDMOREPARAMS]); 
	
	vector<string> spl = split(line, " ");

    if (!isChannelExist(server.getChannels(), spl[0]))
		return sendMsg(client, msgs(client,"", spl[0], "")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]]; 
	if (!isInChannel(server.getCLients()[fd], spl[0]))
		return sendMsg(client, msgs(client,"", channel.getChannelName(), "")[ERR_NOTONCHANNEL]); 
	if (!isAdmin(client.getNickName(), channel))
		return sendMsg(client, msgs(client, "", channel.getChannelName(), "")[ERR_CHANOPRIVSNEEDED]);
	string user = spl[1];
	if (isAdmin(user, channel) || !isInChannelString(user, channel))
		return sendMsg(client, msgs(client, user, channel.getChannelName(), "")[ERR_USERNOTINCHANNEL]);
	if (spl.size() > 2){ ///SEMD THE REASON
		string reason = line;
    	size_t pos = line.find(channel.getChannelName()[0]);
    	if (pos != string::npos)
			reason = line.substr(pos + channel.getChannelName().size());
    	pos = reason.find(user[0]);
    	if (pos != string::npos)
			reason = reason.substr(pos + user.size());
		// for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
			/////finish
//KICK <channel> <user> :<reason>

	}
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
		sendMsg(channel.getChannelUsers()[i],  " KICK #" + channel.getChannelName() + " " + user);
	Client &cUser = getClientStringRef(server.getCLients(), user);
	unsetChannelUser(channel, cUser);
}

///CHECK BEFORE EVERY COMMAND IF ITS THE SAME USER 
///RETURN FALSE WHEN REMOVING A USER SO WE WILL DELETE THEIR FD
/// IF NO USER LEFT WE DELETE THE CHANNEL
/// ADD HASHTAGS
///WHAT ABOUT ALREADY JOINED
