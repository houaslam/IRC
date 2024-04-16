#include "../includes/server.hpp"

void unsetUser(channel &channel, Client &exUser){
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++) //if they were admin
		if (exUser.getNickName() == channel.getChannelAdmins()[i])
			channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
		if (exUser.getNickName() == channel.getChannelUsers()[i].getNickName())
			channel.getChannelUsers().erase(channel.getChannelUsers().begin() + i);

	vector<string>::iterator it = find(exUser.getInChannel().begin(), exUser.getInChannel().end(), channel.getChannelName());
	
	exUser.getInChannel().erase(it);
}


Client getClientString(map<int, Client> clients, string &name)
{
	map<int, Client>::iterator it = clients.begin();
	Client ret = it->second;

    for (; it != clients.end(); it++) {
        if (it->second.getNickName() == name) {
            ret = it->second;
        }
    }

	return ret;
}

string getPRVMsg(string &line){

	size_t colone = line.find(':');
	string msg = "";

    if (colone != string::npos)
	{
    	msg = line.substr(colone + 1);
	}

	return msg;
}

void fillMode(string mode, string &arg, channel &channel, Server &server, Client &client){
	server.getCLients();
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
			channel.setChannelAdmin(arg);
		else
			for (size_t i = 0; i < channel.getChannelAdmins().size(); i++)
				if (arg == channel.getChannelAdmins()[i])
					channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
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

bool isAdmin(string admin, channel &channel){
	
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++){
		if (channel.getChannelAdmins()[i] == admin)
			return true;
	}
	return false;
}

bool isInvited(string invited, channel &channel){
	
	for (size_t i = 0; i < channel.getChannelInvited().size(); i++){
		if (channel.getChannelInvited()[i] == invited)
			return true;
	}
	return false;
}

bool check_users(Server& server, string line, int ref){
	map<int , class Client> save = server.getCLients();
	for(map<int, class Client>::iterator it = save.begin(); it != save.end(); it++){
		if (!line.compare(it->second.getNickName()) && it->second.get_fd() != ref)
			return true;
	}
	return false;
}

bool isChannelExist(map<string, channel> &channels,string &line){
	for(map<string, channel>::iterator it = channels.begin(); it != channels.end(); it++){
		if (line == it->second.getChannelName())
			return true;
	}
	return false;
}

bool isConnected(Server& server, int fd){
	if (!server.getCLients()[fd].pass)
		return false;
	if (server.getCLients()[fd].getNickName().empty())
		return false;
	return true;
}

bool isInChannel(Client &client, string &channel){

	vector<string>::iterator it = find(client.getInChannel().begin(), client.getInChannel().end(), channel);
	
	if (it == client.getInChannel().end())
		return false;

	return true;
}
bool isInChannelString(string &client, channel &channel){

	for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
	{
		if (channel.getChannelUsers()[i].getNickName() == client)
			return true;
	}
	return false;
}