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
		sendMsg(fd, "UR PASSWORD IS CORRECT\n");
	}
	else
		sendMsg(fd, "UR PASSWORD IS INCORRECT PLZ TRY AGAIN\n");
}

// NICK <nickname>
void nick(Server& server, string line, int fd){
	if (server.getCLients()[fd].pass == false){
		sendMsg(fd, "PROVID THE PASSWORD FIRST\n");
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		if (!server.getCLients()[fd].getNickName().empty())
			sendMsg(fd, "NICKNAME ALREADY SET\n");
		else
			sendMsg(fd, "No nickname is given\n");
	}
	else
	{
		if (check_users(server, line, fd))
			sendMsg(fd, "nickname alredy used by another user\n");
		else{
			server.getCLients()[fd].setNickName(line);
			string send = "ur nickname was set to " + server.getCLients()[fd].getNickName();
			sendMsg(fd, send + "\n");
		}
	}
}

// USER <username> <hostname> <servername> <realname>
void user(Server& server, string line, int fd){
	if (server.getCLients()[fd].getNickName().empty()){
		sendMsg(fd, "PROVID A NICKNAME FIRST\n");
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		sendMsg(fd, "not enough arguments\n");
		return ;
	}
	else{
		vector<string> res = split(line, " ");
		if (res.size() != 4){
			sendMsg(fd, "not enough arguments\n");
			return ;
		}
		server.getCLients()[fd].setUser(res[0]);
		server.getCLients()[fd].setHost(res[1]);
		server.setServerName(res[2]);
		server.getCLients()[fd].setRName(res[3]);
	}
	server.getCLients()[fd].isConnected = isConnected(server, fd);

}

// JOIN <channels>
void join(Server& server, string line, int fd){ // [X]
	line = line.substr(4);
	line = strtrim(line);

	if (line.empty()){
		sendMsg(fd,":"+ server.getCLients()[fd].getNickName() + "!" /*getfirstuser*/ + "@localhost 461 "+\
		server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters\n");
		return ;
	}

	vector<string> spl = split(line, " ");

		// if (!isChannelExist(server.getChannels(), split(line, " ")[1])) /*doesn't exist*/{
		//     server.setChannel(spl[0], server.getCLients()[fd]);

		//     cout << "channel " << line << "DOESN'T exist\n";

		// } /// KEEP ADDING TILL YOU SEGFAULT IT
	

}

