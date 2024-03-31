# pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class Client> users;
		map<char, string> modes;
		vector<string> admins;
		vector<int> invited;
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
		void    setChannelUser(class Client &client_);
		void setChannelTopic(string &topic);
		void setChannelAdmin(string admin);

		// GETERS
		string &getChannelName();
		vector<string> getChannelAdmins();
		string &getChannelTopic();
		map<char, string> &getChannelModes();

};

bool isAdmin(string admin, channel channel);