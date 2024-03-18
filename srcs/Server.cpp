#include "../includes/irc.hpp"


Server::Server(int port, const char* password, const char* host) : port(port), password(password), _host(host){
	struct in_addr *addr = NULL;
	struct hostent* test = NULL;
	test = gethostbyname(_host);
	int reuse = 1;

	if (test != NULL)
		addr = (struct in_addr *)test->h_addr;
	else
		ft_error("INVALID ADD ");

	this->_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
		ft_error("SOCKET :");

	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*addr));
	s_addr.sin_family = AF_INET;

	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		ft_error("SOCKET opt : ");

	if (bind(_socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0)
		ft_error("BIND : ");

	if (listen(_socket, 5) < 0)
		ft_error("LISTEN : !");

	std::cout << GREEN << "SOCKET SETUP IS DONE!\n" << RESET;
}


Server::Server(Server& src){
	*this = src;
}


Server& Server::operator=(Server& server){
	if (this != &server){
		this->port = server.port;
		this->_socket = server._socket;
		this->password = server.password;
		this->s_addr = server.s_addr;
	}
	return *this;
}


int Server::get_port() const{
	return this->port;
}
int Server::get_socket() const{
	return this->_socket;
}
string  Server::get_password() const{
	return this->password;
}
struct sockaddr_in&  Server::get_addr(){
	return s_addr;
}
socklen_t  Server::get_addr_len() const{
    return sizeof(this->s_addr);
}