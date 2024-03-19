// # pragma once

#include "server.hpp"
#include "client.hpp"
using namespace std;

class channel{
	private:
		vector<class client> clients;
		string name;
		int mode;
		string topic;
	public:
	// CANONICAL FORM
		channel(string name);
		channel(const channel& src);
		~channel();
		channel& operator=(const channel& src);
	// REGULAR FUNCTIONS
		void    add_user(class client &client_);

};