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
#include "client.hpp"

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
		const char* _host;
		struct sockaddr_in s_addr;
		map<int, class client>  clients;
	public:
	// CANONICAL FORM
		Server(int port, const char* password, const char* _host);
		Server(Server& src);
		Server& operator=(Server& server);

	// GETERS
	int get_port() const;
	int get_socket() const;
	string  get_password() const;
	struct sockaddr_in&  get_addr();
	socklen_t  get_addr_len() const;
	// SETERS
	

	// REGULAR FUNCTION
	void adduser(int id, string nickname);
};

void ft_error(string prob);