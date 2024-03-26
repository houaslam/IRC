# pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class Client> clients;
		string name;
		string topic;
		int admin;
		string adminName;
		map<char, string> modes;
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
		void setChannelAdmin(int admin);
		void setChannelAdminName(string &admin);

		// GETERS
		string &getChannelName();
		int 	getChannelAdmin();
		string &getChannelTopic();
		map<char, string> &getChannelModes();
		string &getChannelAdminName();

};