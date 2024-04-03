#include "../includes/client.hpp"
#include "../includes/server.hpp"

void getMode(string mode, string str, channel &channel, Server &server){
	return;
	str = "";
	if (mode.size() < 2)
		return;
	string flag; //itkol
	if (mode[0] == '-')
		flag  = "-";
	else
		flag = "+";
	if (mode.find("i"))
		cout <<"" << endl;
			// channel.getChannelModes()['i'] = flag + "i";
	else if(mode.find("t"))
			channel.getChannelModes()['t'] = flag + "t";
		else if (mode.find("o"))
		{
			//del or add
			// map<int , class Client> save = server.getCLients();
			for(map<int, class Client>::iterator it = server.getCLients().begin(); it != server.getCLients().end(); it++){
				// if (str.compare(it->second.getNickName()))
					// if (flag == "+")
					// 	channel.setChannelAdmin(it->first);
					// else

			}
		}
		// else if (mode[i] == 'l')
		// 	channel.getChannelModes()[i] = flag + "l";
}
				/*bool*/


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

// void bot(Server& server, string line, int fd){
// 	// 	if (server.getCLients()[fd].getNickName().empty()){
// 	// 	sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NOT_REGISTRED]); 
// 	// 	return ;
// 	// }
// 	line = line.substr(3);
// 	line = strtrim(line);
// 	if (line.empty()){
// 		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NOT_ENOUGH_PARA]); 
// 		return ;
// 	}
// 	else{
// 		vector<string> res = split(line, " ");
// 		if (res.size() != 4){
// 			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","","")[NOT_ENOUGH_PARA]); 
// 			return ;
// 		}
// 		send(fd, "WELCOME TO PIXER SERVER BOT\n", 29, 0);
// 	 // MAKE THE FORMULA USING THE PARAMETERS PROVIDED 
	 
// 	}
// }

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
		channel.setChannelUser(client); ///add invited to users as well
		cout << "NEW CHANNEL" << endl;
		cout << channel.getChannelUsers().size() << endl; 
		channel.setChannelAdmin(client.getNickName());
		server.setChannel(channel, spl[0], client);
		justJoined(client, channel, spl[0]); //!
    }
	else{
		channel &channel = server.getChannels()[spl[0]];
		if (isInChannel(client, spl[0])) ///LATER
			return ;
		if (!channel.getChannelModes()['l'].empty() && channel.getChannelModes()['l'] != "-l" && channel.getChannelUsers().size() > (size_t)atoi(channel.getChannelModes()['l'].c_str()))
			return sendMsg(client, msgs(client, "", "JOIN", "")[ERR_CHANNELISFULL]); 
		if (!channel.getChannelModes()['k'].empty() && channel.getChannelModes()['k'] != "-k" && spl[1] != channel.getChannelModes()['k'])
			return sendMsg(client, msgs(client, "", "JOIN", "")[ERR_BADCHANNELKEY]); 
		if (/*!isAdmin(client.getNickName(), channel) &&*/ !isInvited(client.getNickName(), channel) && channel.getChannelModes()['i'] == "+i")
			return sendMsg(client, msgs(client, "", "JOIN", "")[ERR_INVITEONLYCHAN]); 
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
		return sendMsg(client, msgs(client, "", spl[1], "INVITE")[ERR_NOSUCHCHANNEL]); 
	
	channel &channel = server.getChannels()[spl[1]];
	if (!isInChannel(client, channel.getChannelName()))
		return sendMsg(client, msgs(client, "", channel.getChannelName(), "INVITE")[ERR_NOTONCHANNEL]); 
	if (!isAdmin(client.getNickName(), channel))
		return sendMsg(client, msgs(client, "", channel.getChannelName(), "INVITE")[ERR_CHANOPRIVSNEEDED]); 
	if (isInChannelString(invited, channel))
		return sendMsg(client, msgs(client, invited, channel.getChannelName(), "INVITE")[ERR_USERONCHANNEL]); 
	if (!check_users(server, invited, fd))
		return sendMsg(client, msgs(client, invited, "", "INVITE")[ERR_NOSUCHNICK]); 

	channel.setChannelInvited(invited);
	sendMsg(client, msgs(client, invited, channel.getChannelName(), "INVITE")[RPL_INVITING]); 
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
		return sendMsg(client, msgs(client,"", spl[0], "TOPIC")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]]; 
	if (!isInChannel(server.getCLients()[fd], spl[0]))
		return sendMsg(client, msgs(client,"", channel.getChannelName(), "TOPIC")[ERR_NOTONCHANNEL]); 

	string topic = line.substr(spl[0].size());

	if (topic.empty())
	{
		if (channel.getChannelTopic().empty())
			return sendMsg(client, msgs(client,"", channel.getChannelName(), "TOPIC")[RPL_NOTOPIC]); 
		send(fd," :show old topic\n", 18, 0);
	}
	else{
		if (channel.getChannelModes()['t'] == "+t" &&
			!isAdmin(client.getNickName(), channel))
				return sendMsg(client, msgs(client,"", channel.getChannelName(), "TOPIC")[ERR_CHANOPRIVSNEEDED]); 
		else
			channel.setChannelTopic(topic);
	}
}

void fillMode(string mode, string &arg, channel &channel, Server &server, Client &client){
	server.getCLients(); //// WHAT IF WE GAVE A +O OR WHATEVER TO SOMEONE NOT IN THE CHANNEL
	if (mode.size() > 2) ///recheck later
	{
		send(client.get_fd(), "ERROR\n", 5, 0);	
		return; 
	}
	char flag = mode[0];
	if (mode[1] == 'o'){
		if (arg.empty())
			return sendMsg(client, "not enough arguments");
		if (flag == '+' && isInChannelString(arg, channel))
		{
			cout << "client is in channel " << channel.getChannelName() << endl;
			channel.setChannelAdmin(arg);
		}
		else
			for (size_t i = 0; i < channel.getChannelAdmins().size(); i++)
				if (arg == channel.getChannelAdmins()[i])
					channel.getChannelAdmins()[i] = ""; ////later
					// channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
	}
	if (mode[1] == 'k'){
		if (flag == '-')
			channel.getChannelModes()['k'] = "";
		else{
			if (arg.empty())
				return sendMsg(client, "not enough arguments");
			channel.getChannelModes()['k'] = arg;
		}
	}
	if (mode[1] == 'l'){
		if (flag == '-')
			channel.getChannelModes()['l'] = "";
		else
		{
			if (arg.empty())
				return sendMsg(client, "not enough arguments");
			for (size_t i = 0; i < arg.size(); i++)
				if (!isdigit(arg[i]))
					return;
			channel.getChannelModes()['l'] = arg;
		}
	}
	if (mode[1] == 't'){
		if (flag == '-')
			channel.getChannelModes()['t'] = "-t";
		else
			channel.getChannelModes()['t'] = "+t";
	}
	if (mode[1] == 'i'){
		if (flag == '-')
			channel.getChannelModes()['i'] = "-i";
		else
			channel.getChannelModes()['i'] = "+i";
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
		return sendMsg(client, msgs(client,"" , spl[0], "MODE")[ERR_NOSUCHCHANNEL]); 
	channel &channel = server.getChannels()[spl[0]];
	
	if (!isInChannel(client, spl[0]))
		return sendMsg(client, msgs(client, "",channel.getChannelName(), "MODE")[ERR_NOTONCHANNEL]); 
	else if (!isAdmin(client.getNickName(), channel))
		return sendMsg(client, msgs(client, "",channel.getChannelName(), "MODE")[ERR_CHANOPRIVSNEEDED]); 
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

// string getMsg(int msgNumber, Server& server, string channel, int fd){
// 	return(   msgs()[msgNumber]);
// }

