// # pragma once

#include "irc.hpp"
#include "client.hpp"


class channel{
	private:
		vector<class client> clients;
		string name;
		int mode;
		string topic;
	public:
	// CANONICAL FORM
		channel(string name);
		channel(channel& src);
		~channel();
		channel& operator=(channel& src);
	// REGULAR FUNCTIONS
		void    add_user(class client client_);

};