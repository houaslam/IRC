# pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class Client> users;
		map<char, string> modes;
		vector<string> admins;
		vector<string> invited;
		string name;
		string topic;
	public:

		// CANONICAL FORM
		channel();
		channel(string name);
		channel(const channel& src);
		channel& operator=(const channel& src);
		~channel();

		// REGULAR FUNCTIONS
		void setChannelUser(class Client &client_);
		void setChannelTopic(string &topic);
		void setChannelAdmin(string &admin);
		void setChannelInvited(string &admin);

		// GETERS
		string &getChannelName();
		string &getChannelTopic();
		vector<string> &getChannelAdmins();
		vector<string> &getChannelInvited();
		vector<Client> &getChannelUsers();
		map<char, string> &getChannelModes();

};
