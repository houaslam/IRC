#include "../includes/server.hpp"


Server::Server(int port, const char* password) : port(port), serverName(""), password(password){
	struct in_addr *addr = NULL;
	struct hostent* test = NULL;
	test = gethostbyname("localhost");
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

	cout << GREEN << "SOCKET SETUP IS DONE!\n" << RESET;
}

Server::~Server(){

}

Server::Server(const Server& src){
	*this = src;
}

Server& Server::operator=(const Server& server){
	if (this != &server){
		this->_socket = server._socket;
		this->password = server.password;
		this->s_addr = server.s_addr;
		this->clients = server.clients;
	}
	return *this;
}

		//GETTERS
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
map<int, Client>&  Server::getCLients(){
	return this->clients;
}
socklen_t  Server::get_addr_len() const{
    return sizeof(this->s_addr);
}
string Server::getServerName() const{
	return this->serverName;
}

map<string, channel> &Server::getChannels(){
	return this->channels;
}

		//SETTERS
void Server::setUser(Client &obj){
	this->clients[obj.get_fd()] = obj;
}
void Server::setChannel(string name, Client &client){
	client.get_fd();

	channel channel(name);
	channel.setChannelUser(client);
	this->channels.insert(make_pair(name, channel));
}

void Server::setServerName(string name){
	this->serverName = name;
}
