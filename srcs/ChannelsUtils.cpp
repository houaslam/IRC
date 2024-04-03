#include "../includes/server.hpp"

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

bool check_users(Server& server,string line , int ref){
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