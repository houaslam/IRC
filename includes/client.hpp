# pragma once

#include "server.hpp"
#include "channel.hpp"
using namespace std;

class Server;
class channel;

class Client{
	private:

		// NICK
		string nickname;

		// USER
		string username;
		string hostname;
		string r_name;

		// CONNECTION

		//CLIENT HIMSELF 
		int fd;

		// JOIN
		vector<string> inChannel;
	public:
		pthread_t thread;
		bool isConnected;
		bool pass;

		Client();
		Client(int fd);
		Client(const Client& src);
		Client& operator=(const Client& client_);
		~Client();

		//SETTERS
		void setId(int id);
		void setFd(int fd);
		void setNickName(string nick);
		void setUser(string nick);
		void setHost(string nick);
		void setRName(string nick);
		void setInChannel(string &inChannel);

		// GETTERS
		string& getNickName(void);
		string& getUser(void);
		vector<string> &getInChannel(void);
		int get_fd();
		int getId();
};


void    user(Server& server, string line, int fd);
void    nick(Server& server ,string line, int fd);
string  &withoutNewLine(string &line);
void    join(Server& server, string line, int fd);
void    pass(Server& server, string line , int fd);
void	topic(Server &server, string line, int fd);
void	invite(Server &server, string line, int fd);
void	mode(Server &server, string line, int fd);
void	bot(int fd, string cmd, Server& sever);
void	privmsg(Server &server, string line, int fd);
void	part(Server &server, string line, int fd);
