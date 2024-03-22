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
#include "errors.hpp"
#include <sys/time.h>

       /* COLORS */
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"    
#define YELLOW  "\033[33m"    
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"     
#define CYAN    "\033[36m"     
#define WHITE   "\033[37m"   

using namespace std;

class Server{
	private:
		int port;
		int _socket;
		const char* password;
		struct sockaddr_in s_addr;
		map<int , class Client>  clients;
		vector<class channel>  channels;
		string serverName;

	public:
	// CANONICAL FORM
		Server(int port, const char* password);
		Server(const Server& src);
		Server& operator=(const Server& server);
		~Server();

	// GETERS
	string getServerName() const;
	int get_port() const;
	int get_socket() const;
	string  get_password() const;
	struct sockaddr_in&  get_addr();
	socklen_t  get_addr_len() const;
	map<int, Client> &getCLients();
	vector<class channel> &getChannels();


	// SETERS
	void setUser(Client &obj);
	

	// REGULAR FUNCTION
	void aff_allusers();
	channel &createChannel();

};

// OTHERS
bool parse(class Server &server,int i, string line);
void ft_error(string prob);
std::vector<std::string> split(std::string src, std::string s);
string strtrim(const string& str);
void add_fd(struct pollfd fds[], int* fd_count, int fd);
void del_fd(struct pollfd fds[], int* fd_count, int p);
void sendMsg(int fd, string str);
bool check_users(Server& server,string line);

// if (hajar == zwina)
// 	return taha + hajar = love;
// if (hajar == khyba)
// 	return (taha + hajar = love);
// 	bghit ngheyerha