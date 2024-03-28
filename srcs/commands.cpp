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

bool isChannelExist(map<string, channel> &channels,string &line){
	if (channels.find(line) == channels.end())
		return false;
	return true;
}

bool isConnected(Server& server, int fd){
	if (!server.getCLients()[fd].pass)
		return false;
	if (server.getCLients()[fd].getNickName().empty())
		return false;
	return true;
}

bool isInChannel(Client &client, string &name){

	vector<string>::iterator it = find(client.getInChannel().begin(), client.getInChannel().end(), name);

	if (it == client.getInChannel().end())
		return false;

	return true;
}

// PASS <password>
void    pass(Server& server, string line , int fd){
	line = line.substr(4);
	line = strtrim(line);

	vector<string> res = split(line, " ");
	if (res.size() == 1 && !res[0].compare(server.get_password())){
		server.getCLients()[fd].pass = true;
		sendMsg(server.getCLients()[fd], "UR PASSWORD IS CORRECT");
	}
	else{
		if (server.getCLients()[fd].pass == false)
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "")[INCORRECT_PWD]);
	}
}

// NICK <nickname>
void nick(Server& server, string line, int fd){
	if (server.getCLients()[fd].pass == false){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "")[NOT_REGISTRED]);
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		if (!server.getCLients()[fd].getNickName().empty())
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"", "")[NICK_NOT_GIVEN]);
		else
			sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"", "")[NICK_NOT_GIVEN]);
			// sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd].getNickName() + getMsg(NICK_NOT_GIVEN));
	}
	else
	{
		vector<string> res = split(line, " ");
		if (check_users(server, res[0], fd))
				sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","")[NICK_IN_USE]);
		else{
			server.getCLients()[fd].setNickName(res[0]);
			string send = "ur nickname was set to " + server.getCLients()[fd].getNickName();
			sendMsg(server.getCLients()[fd], send + "");
		}
	}
}

// USER <username> <hostname> <servername> <realname>
void user(Server& server, string line, int fd){
	if (server.getCLients()[fd].getNickName().empty()){
		sendMsg(server.getCLients()[fd], "PROVID A NICKNAME FIRST");
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		sendMsg(server.getCLients()[fd], "not enough arguments");
		return ;
	}
	else{
		vector<string> res = split(line, " ");
		if (res.size() != 4){
			sendMsg(server.getCLients()[fd], "not enough arguments");
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
void join(Server& server, string line, int fd){ // [X]
    // if (!server.getCLients()[fd].getInChannel().empty())
    //     return;


    server.getServerName();
    line = line.substr(4);
    line = strtrim(line);

    if (line.empty()){
		string msg = ":"+ server.getCLients()[fd].getNickName() + "!" + server.getCLients()[fd].getUser() + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters";
        send(fd,"JOIN :Not enough parameters", 29, 0);
        return ;
    }

    vector<string> spl = split(line, " ");

    if (!isChannelExist(server.getChannels(), split(line, " ")[0])) /*doesn't exist*/{
        channel channel(spl[0]);

		server.getCLients()[fd].setInChannel(spl[0]);
		channel.setChannelUser(server.getCLients()[fd]);
		channel.setChannelAdmin(fd);
		server.setChannel(channel, spl[0], server.getCLients()[fd]);
		justJoined(server.getCLients()[fd], channel, fd, spl[0]); //!

    }
	else{
		server.getCLients()[fd].setInChannel(spl[0]);
		server.getChannels()[spl[0]].setChannelUser(server.getCLients()[fd]);
		justJoined(server.getCLients()[fd], server.getChannels()[spl[0]], fd, spl[0]); //!
	}
}

void	topic(Server &server, string line, int fd){

    server.getServerName();
    line = line.substr(5);
    line = strtrim(line); 


    if (strtrim(line).empty()){
		string msg = ":"+ server.getCLients()[fd].getNickName() + "!" + server.getCLients()[fd].getUser() + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters";
        send(fd, ":Not enough parameters\n", 24, 0); //! 461
        return ;
    }

	vector<string> spl = split(line, " ");

	string channel = spl[0]; //next time work using reference 
    if (!isChannelExist(server.getChannels(), channel)) /*doesn't exist*/{
		send(fd, ":No such channel\n", 18, 0); //! 403
		return;
    }
	else if (!isInChannel(server.getCLients()[fd], channel))
	{
		send(fd, ":You're not on that channel\n", 29, 0); //! 442
		return;
	}

	string topic = line.substr(channel.size());

	if (topic.empty())
	{
		if (server.getChannels()[channel].getChannelTopic().empty())
			send(fd," :No topic is set\n", 19, 0); //! 331
		else
		{
			// send(fd, server.getChannels()[channel].getChannelTopic().c_str(), (server.getChannels()[channel].getChannelTopic()).size(), 0); //! 332
			send(fd," :show old topic\n", 18, 0); //! 331
		}
	}
	else{
		if (server.getChannels()[channel].getChannelModes()['t'] == "+t" &&
		 server.getChannels()[channel].getChannelAdmin() != fd)
			send(fd, "You're not channel operator\n", 29, 0); //! 482
		else{
			send(fd, ":new topic\n", 12, 0); //! 333
			server.getChannels()[channel].setChannelTopic(topic);
		}
	}
}
/*if the first arg doesn't start with a + or - we have to cases if we are in a channel we show nothing otherwize
we check if the mode already exist if we have the right to change it changes if we're not we show that we don't have the right
	and if we aren't in a channel and the first arg starts with a + or - we show "Not joined to any channel
" otherwize we show that no such a channel even if it does exist*/
// void	mode(Server &server, string line, int fd){

//     server.getServerName();
//     line = line.substr(5);
//     line = strtrim(line); 


//     if (strtrim(line).empty()){
// 		string msg = ":"+ server.getCLients()[fd].getNickName() + "!" + server.getCLients()[fd].getUser() + "@localhost 461 "+\
//         server.getCLients()[fd].getNickName()+" MODE :Not enough parameters";
//         send(fd, ":Not enough parameters\n", 24, 0); //! 461
//         return ;
//     }

// 	vector<string> spl = split(line, " ");

// 	if (isInChannel(server.getCLients()[fd], spl[0])){
// 		if (spl[0][0] != '+')
// 			return;
// 		else
// 			get
// 	}
	
// 	// string channel = spl[0]; //next time work using reference 
//     if (!isChannelExist(server.getChannels(), spl)) /*doesn't exist*/{
// 		send(fd, ":No such channel\n", 18, 0); //! 403
// 		return;
//     }
// 	else if (!isInChannel(server.getCLients()[fd], spl[0]))
// 	{
// 		send(fd, ":You're not on that channel\n", 29, 0); //! 442
// 		return;
// 	}

// 	string topic = line.substr(channel.size());

// 	if (topic.empty())
// 	{
// 		if (server.getChannels()[channel].getChannelTopic().empty())
// 			send(fd," :No topic is set\n", 19, 0); //! 331
// 		else
// 		{
// 			// send(fd, server.getChannels()[channel].getChannelTopic().c_str(), (server.getChannels()[channel].getChannelTopic()).size(), 0); //! 332
// 			send(fd," :show old topic\n", 18, 0); //! 331
// 		}
// 	}
// 	else{
// 		if (server.getChannels()[channel].getChannelModes()['t'] == "+t" &&
// 		 server.getChannels()[channel].getChannelAdmin() != fd)
// 			send(fd, "You're not channel operator\n", 29, 0); //! 482
// 		else{
// 			send(fd, ":new topic\n", 12, 0); //! 333
// 			server.getChannels()[channel].setChannelTopic(topic);
// 		}
// 	}
// }

