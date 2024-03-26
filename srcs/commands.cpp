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
    if (!server.getCLients()[fd].getInChannel().empty())
        return;


    server.getServerName();
    line = line.substr(4);
    line = strtrim(line);

    if (line.empty()){
        sendMsg(server.getCLients()[fd],":"+ server.getCLients()[fd].getNickName() + "!" /*getfirstuser*/ + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters");
        return ;
    }

    vector<string> spl = split(line, " ");

        if (!isChannelExist(server.getChannels(), split(line, " ")[0])) /*doesn't exist*/{
            channel channel(spl[0]);
			cout << "CHANNEL DOESN'T EXIST\n";
			channel.addUser(server.getCLients()[fd]);
            server.getCLients()[fd].setInChannel(spl[0]);

			server.getChannels().insert(make_pair(spl[0], channel));
			justJoined(server.getCLients()[fd], channel, fd, spl[0]);
        } /// KEEP ADDING TILL YOU SEGFAULT IT

}

// string getMsg(int msgNumber, Server& server, string channel, int fd){
// 	return(   msgs()[msgNumber]);
// }
