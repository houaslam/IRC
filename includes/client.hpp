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


void	user(Server& server, string line, int fd);
void	nick(Server& server ,string line, int fd);
void	join(Server& server, string line, int fd);
void	pass(Server& server, string line , int fd);
void	topic(Server &server, string line, int fd);
string	&withoutNewLine(string &line);
void	add_fd(struct pollfd fds[], int* fd_count, int fd);
void	del_fd(struct pollfd fds[], int* fd_count, int p);
void	justJoined(Client &client, channel &channel, int fd, string &line);
void	mode(Server &server, string line, int fd);


