# pragma once
#include <sstream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <map>
#include <vector>
#include <sys/socket.h>  
#include <string>
#include <cctype>

using namespace std;
class Server{
	private:
		int port;
		int _socket;
		string password;
		struct sockaddr_in s_addr;
	public:
	// CANONICAL FORM
		Server(int port, string password);
		Server(Server& src);
		Server& operator=(Server& server);

	// GETERS
	int get_port() const;
	int get_socket() const;
	string  get_password() const;
	struct sockaddr_in&  get_addr();
	socklen_t  get_addr_len() const;
	// SETERS
	
};

void ft_error(string prob);