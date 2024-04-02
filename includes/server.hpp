# pragma once

#include <sstream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <map>
#include <vector>
#include <vector>
#include <sys/socket.h>  
#include <string>
#include <cctype>
#include <poll.h>
#include <vector>
#include "client.hpp"
#include "channel.hpp"
#include <sys/time.h>
#include <ctime>
#include <algorithm>

       /* COLORS */
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"    
#define YELLOW  "\033[33m"    
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"     
#define CYAN    "\033[36m"     
#define WHITE   "\033[37m"   


       /* ERRORS */

// CHANNEL
#define IN_CHANNEL			    405  // :You have joined too many channels
#define ERR_NOTONCHANNEL		442	 // :You're not on that channel
#define ERR_NOSUCHCHANNEL 		403  // :No such channel
#define MODE_PLUS_I 			437  // <client> <channel> :Cannot join channel (+i)"
#define ERR_CHANNELMODEINVALID	473  // :Invalid channel mode
#define ERR_CHANNELISFULL		471  // :Cannot join channel (+l)
#define ERR_BADCHANNELKEY		475  // :Cannot join channel (+k)
#define RPL_INVITING			341  // :<nick> <channel>
#define RPL_TOPIC	    		332  // :Channel Topic
#define RPL_NOTOPIC				331  // :No topic is set"
#define ERR_CHANOPRIVSNEEDED	482  // :You're not channel operator
#define ERR_USERONCHANNEL		443  // :is already on channel

  
// NICK 
#define NICK_NOT_GIVEN		    431  // :Nickname not given"
#define NICK_IN_USE			    433  // :Nickname is already in use"

// PASS
#define INCORRECT_PWD		    464  // :Password is incorrect

// GENERAL
#define NOT_REGISTRED		    451  // :You have not registered
#define UNKNOW_CMD			    421  // :Unknown command
#define NOT_ENOUGH_PARA		    461  // :Not enough parameters
#define ALREADY_REGISTERED	    462  // :You may not register


using namespace std;

class Server{
	private:
	// SERVER INFO
		int port;
		int _socket;
		string serverName;
		const char* password;
		struct sockaddr_in s_addr;
	// SERVER COMPONENTS
		map<int, string> msg;
		map<int , class Client>  clients;
		map<string, class channel>  channels;

	public:
	// CANONICAL FORM
		~Server();
		Server(const Server& src);
		Server(int port, const char* password);
		Server& operator=(const Server& server);

	// GETERS
		int get_port() const;
		int get_socket() const;
		string get_password() const;
		string getServerName() const;

		map<int, Client> &getCLients();
		map<int, string> get_msg() const;
		map<string, class channel> &getChannels();

		struct sockaddr_in&  get_addr();
		socklen_t  get_addr_len() const;


		// SETERS
		void setUser(Client &obj);
		void setServerName(string name);
		channel &setChannel(channel channel, string &name, Client &client);

		// REGULAR FUNCTION
		void aff_allusers();

};

// OTHERS
bool parse(class Server &server,int i, string line);
void ft_error(string prob);
std::vector<std::string> split(std::string src, std::string s);
string strtrim(const string& str);

// EXTERNAL FUNCTION
void sendMsg(Client& client, string str);
void ft_unknownCmd(Client &client, int fd, string &line);
void justJoined(Client &client, channel &channel, string &line);
string getMsg(int msgNumber);
string getLocalhost(Client &client);
string nbtoString(int nb);
map<int, string> msgs(Client& client, string channel, string cmd);
void clearScreen(int fd);
string getTime(void);
void del_fd(struct pollfd fds[], int* fd_count, int p);
void add_fd(struct pollfd fds[], int* fd_count, int fd);

// BOOL
bool isConnected(Server& server, int fd);
bool isChannelExist(map<string, channel> &channels,string &line);
bool isInChannel(class Client &client, string &name);
bool isAdmin(int admin, channel channel);

// if (hajar == zwina)
// 	return taha + hajar = love;
// if (hajar == khyba)
// 	return (taha + hajar = love);
// 	bghit ngheyerha