# pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class Client> clients;
		string name;
		map<char, int> modes;
		string topic;
	public:
	// CANONICAL FORM
		channel(string &name);
		channel(const channel& src);
		channel& operator=(const channel& src);
		~channel();
	// REGULAR FUNCTIONS
		void    addUser(class Client &client_);

		//getters
		string &getChannelName();

};