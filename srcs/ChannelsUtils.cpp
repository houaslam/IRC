#include "../includes/server.hpp"

// void channelCheck(Server &server){
//				channel.getChannelInvited().erase(channel.getChannelInvited().begin() + i);

	// for (size_t i = 0; i < server.getChannels().size(); i++)
	// {
	// 	if (server.getChannels()[i].getChannelUsers().empty())
	// 		server.getChannels().erase(server.getChannels().begin()); ///test
	// }
	
// }

// void unsetUser(Server &server, int fd){
// 	vector<string>::iterator findIt;
// 	Client &client = server.getCLients()[fd];
// 	for (map<string, channel>::iterator it = server.getChannels().begin();it != server.getChannels().end(); it++)
// 	{
// 		//USERS
// 		for (vector<Client>::iterator i = 0; i < it->second.getChannelUsers().size(); i++)
// 		{
// 			findIt = find(it->second.getChannelUsers()[i].begin(), it->second.getChannelUsers()[i].end(), client.getNickName());
// 			// if ( != it->second.getChannelUsers().end())
// 			// if (it->second.getChannelUsers()[i])
// 		}
		
// 	// 	vector<Client>::iterator findIt = find(it->second.getChannelUsers().begin(), it->second.getChannelUsers().end(), client);
// 		// 	it->second.getChannelUsers().erase(findIt);
// 		// //ADMINS
// 		// vector<string>::iterator findIt = find(it->second.getChannelAdmins().begin(), it->second.getChannelAdmins().end(), client.getNickName());
// 		// if (findIt != it->second.getChannelAdmins().begin())
// 		// 	it->second.getChannelAdmins().erase(findIt);
// 	}
// 			// channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
// // 	for (size_t i = 0; i < channel.getChannelUsers().size(); i++) // in users
// // 		if (exUser.getNickName() == channel.getChannelUsers()[i].getNickName())
// // 			channel.getChannelUsers().erase(channel.getChannelUsers().begin() + i);

// // 	for (size_t i = 0; i < exUser.getInChannel().size(); i++) //in channels
// // 		if (channel.getChannelName() == exUser.getInChannel()[i])
// // 			exUser.getInChannel().erase(exUser.getInChannel().begin() + i);

// }

void unsetChannelUser(channel &channel, Client &exUser){


	cout << GREEN ;
	cout << "STAART _________ START" << endl;
	cout << "ADMINS _________ " << endl;
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++){
		cout << channel.getChannelAdmins()[i] << endl;
	}
	cout << "USERS _________ " << endl;
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++){
		cout << channel.getChannelUsers()[i].getNickName() << endl;
	}
	for (size_t i = 0; i < exUser.getInChannel().size(); i++){
		cout << exUser.getInChannel()[i] << endl;
	}
	cout << "EEND _________ EEND" << endl;
	cout << RESET ;
	/////test why it doesn't get delete
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++) //if they were admin
		if (channel.getChannelAdmins()[i] == exUser.getNickName())
			channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
	
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++) // in users
		if (exUser.get_fd() == channel.getChannelUsers()[i].get_fd())
			channel.getChannelUsers().erase(channel.getChannelUsers().begin() + i);

	for (size_t i = 0; i < exUser.getInChannel().size(); i++) //in channels
	{

		if (channel.getChannelName() == exUser.getInChannel()[i])
			exUser.getInChannel().erase(exUser.getInChannel().begin() + i);
	}

	//______________________________________________________________________

	cout << RED ;
	cout << "STAART _________ START" << endl;
	cout << "ADMINS _________ " << endl;
	for (size_t i = 0; i < channel.getChannelAdmins().size(); i++){
		cout << channel.getChannelAdmins()[i] << endl;
	}
	cout << "USERS _________ " << endl;
	for (size_t i = 0; i < channel.getChannelUsers().size(); i++){
		cout << channel.getChannelUsers()[i].getNickName() << endl;
	}
	for (size_t i = 0; i < exUser.getInChannel().size(); i++){
		cout << exUser.getInChannel()[i] << endl;
	}
	cout << "EEND _________ EEND" << endl;
	cout << RED ;
	// vector<string>::iterator findIt = find(exUser.getInChannel().begin(), exUser.getInChannel().end(), channel.getChannelName());
    
    // if (findIt != exUser.getInChannel().end()) {
    //     exUser.getInChannel().erase(findIt);
    // }

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

Client &getClientStringRef(map<int, Client> &clients, string &name)
{
	map<int, Client>::iterator it = clients.begin();

    for (; it != clients.end(); it++) {
        if (it->second.getNickName() == name) {
            return it->second;
        }
    }

	return it->second;
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
	if (mode.size() > 2) //////recheck later
		return; 
	char flag = mode[0];
	if (mode[1] == 'o'){
		if (arg.empty())
			return ;
		if (flag == '+' && isInChannelString(arg, channel))
		{
			sendMsg(client,  " MODE " + channel.getChannelName() + " +o " + arg);
			channel.setChannelAdmin(arg);
		}
		else
			for (size_t i = 0; i < channel.getChannelAdmins().size(); i++)
				if (arg == channel.getChannelAdmins()[i])
				{	sendMsg(client,  " MODE " + channel.getChannelName() + " -o " + arg); 
					channel.getChannelAdmins().erase(channel.getChannelAdmins().begin() + i);
				}
	}
	if (mode[1] == 'k'){
		if (flag == '-')
		{
			channel.getChannelModes()['k'] = "";
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " -k"); 
		}
		else{
			if (arg.empty())
				return sendMsg(client, msgs(client, "","", "MODE")[ERR_NEEDMOREPARAMS]); 
			channel.getChannelModes()['k'] = arg;
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " +k " + arg); 
		}
	}
	if (mode[1] == 'l'){
		if (flag == '-')
		{
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " -l"); 
			channel.getChannelModes()['l'] = "";
		}
		else
		{
			if (arg.empty())
				return sendMsg(client, msgs(client, "","", "MODE")[ERR_NEEDMOREPARAMS]); 
			for (size_t i = 0; i < arg.size(); i++)
				if (!isdigit(arg[i]))
					return;
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " +l " + arg); 
			channel.getChannelModes()['l'] = arg;
		}
	}
	if (mode[1] == 't'){
		if (flag == '-')
		{
			channel.getChannelModes()['t'] = "-t";
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " -t"); 
		}
		else
		{
			channel.getChannelModes()['t'] = "+t";
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " +t"); 
		}
	}
	if (mode[1] == 'i'){
		if (flag == '-')
		{
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " -i"); 
			channel.getChannelModes()['i'] = "-i";
		}
		else
		{
			for (size_t i = 0; i < channel.getChannelUsers().size(); i++)
				sendMsg(channel.getChannelUsers()[i],  " MODE " + channel.getChannelName() + " +i"); 
			channel.getChannelModes()['i'] = "+i";
		}
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