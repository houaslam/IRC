# pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class Client> clients;
		string name;
		string topic;
		map<char, int> modes;
	public:

		// CANONICAL FORM
		channel();
		channel(string name);
		channel(const channel& src);
		channel& operator=(const channel& src);
		~channel();

		// REGULAR FUNCTIONS
		void    setUser(class Client &client_);
		void setChannelTopic(string &topic);
		
		// GETERS
		string &getChannelName();
		string &getChannelTopic();

};