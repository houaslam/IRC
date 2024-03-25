#include "../includes/client.hpp"
#include "../includes/server.hpp"
					
					/*BOOL*/
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
		sendMsg(fd, "UR PASSWORD IS CORRECT");
	}
	else{
		if (server.getCLients()[fd].pass == false)
			sendMsg(fd, "UR PASSWORD IS INCORRECT PLZ TRY AGAIN");
	}
}

// NICK <nickname>
void nick(Server& server, string line, int fd){
	if (server.getCLients()[fd].pass == false){
		sendMsg(fd, "PROVID THE PASSWORD FIRST");
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		if (!server.getCLients()[fd].getNickName().empty())
			sendMsg(fd, "NICKNAME ALREADY SET");
		else
			sendMsg(fd, server.getCLients()[fd].getNickName() + getMsg(NICK_NOT_GIVEN));
			// sendMsg(fd, "No nickname is given");
	}
	else
	{
		vector<string> res = split(line, " ");
		if (check_users(server, res[0], fd))
			sendMsg(fd, server.getCLients()[fd].getNickName() + " "+ res[0] + getMsg(NICK_IN_USE));
		else{
			server.getCLients()[fd].setNickName(res[0]);
			string send = "ur nickname was set to " + server.getCLients()[fd].getNickName();
			sendMsg(fd, send + "");
		}
	}
}

// USER <username> <hostname> <servername> <realname>
void user(Server& server, string line, int fd){

	if (server.getCLients()[fd].getNickName().empty()){
		sendMsg(fd, "PROVID A NICKNAME FIRST");
		return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	if (line.empty()){
		sendMsg(fd, "not enough arguments");
		return ;
	}
	else{
		vector<string> res = split(line, " ");
		if (res.size() != 4){
			sendMsg(fd, "not enough arguments");
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
    // if (!server.getCLients()[fd].getInChannel().empty())
    //     return;


    server.getServerName();
    line = line.substr(4);
    line = strtrim(line);

    if (line.empty()){
        sendMsg(fd,":"+ server.getCLients()[fd].getNickName() + "!" + server.getCLients()[fd].getUser() + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters");
        return ;
    }

    vector<string> spl = split(line, " ");

        if (!isChannelExist(server.getChannels(), split(line, " ")[0])) /*doesn't exist*/{
            channel channel(spl[0]);

			channel.setUser(server.getCLients()[fd]);
            server.getCLients()[fd].setInChannel(spl[0]);

			server.getChannels().insert(make_pair(spl[0], channel));
			justJoined(server.getCLients()[fd], channel, fd, spl[0]);
        } /// KEEP ADDING TILL YOU SEGFAULT IT

}

void	topic(Server &server, string line, int fd){

    server.getServerName();
    line = line.substr(5);
    line = strtrim(line);

    if (line.empty()){
        sendMsg(fd,":"+ server.getCLients()[fd].getNickName() + "!" + server.getCLients()[fd].getUser() + "@localhost 461 "+\
        server.getCLients()[fd].getNickName()+" JOIN :Not enough parameters"); //! 461
        return ;
    }
    
	vector<string> spl = split(line, " ");

    if (!isChannelExist(server.getChannels(), spl[0])) /*doesn't exist*/{
		send(fd, ":No such channel\n", 18, 0); //! 403
    }
	if (!isInChannel(server.getCLients()[fd] ,line))
		send(fd, ":You're not on that channel\n", 18, 0); //! 442
	if (spl.size() )
	server.set
}
