// #include "../includes/server.hpp"
// #include "../includes/client.hpp"

// void del_fd(struct pollfd fds[], int* fd_count, int p){
// 	close(fds[p].fd);
// 	fds[p].fd = fds[*fd_count - 1].fd;
// 	(*fd_count)--;
// }

// void add_fd(struct pollfd fds[], int* fd_count, int fd){
// 	fds[(*fd_count)].fd = fd;
// 	fds[(*fd_count)].events = POLLIN;
// 	std::cout << BLUE << "NEW CONNECTION\n" << RESET;
// 	(*fd_count)++;
// }

// int main(int ac , char ** av){

// 	if (ac == 3){

// 		Server server(8500, av[2], av[1]);
// 		char reqs[1024];
// 		int clientFd;
// 		struct pollfd fds[1024];

// 		fds[0].fd = server.get_socket();
// 		fds[0].events = POLLIN;
// 		socklen_t add_size = sizeof(server.get_addr_len());
// 		int nb_fds = 1;

// 		while(true){

// 			if (poll(fds, nb_fds, 0) > 0){

// 				for (int i = 0; i < nb_fds; i++){

// 					if (fds[i].revents == POLLIN){
// 						if (fds[i].fd == server.get_socket()){
// 							clientFd = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);
// 							if (clientFd <= 0)
// 								ft_error("CLIENT : ");
// 							add_fd(fds, &nb_fds, clientFd);
// 							server.adduser(clientFd, "test");
// 							// client client__("client", clientFd);
// 							// server.clients[clientFd] = client__;
// 						}

// 						else{
// 							int k = recv(fds[i].fd, reqs, sizeof(reqs), 0);
// 							cout << "BYTES = " << k << endl;
// 							if (k > 0){
// 								reqs[k] = '\0';
// 								std::cout << "client = " << reqs;
// 							}

// 							else{
// 								// server.ea
// 								ft_error("LOL : ");
// 								del_fd(fds, &nb_fds, i);

// 								if (k == 0){
// 									std::cout << BLUE << "BYE BYE\n" << RESET;
// 									// continue;
// 								}

// 								else
// 									ft_error("DONE : ");
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	
// }
#include <iostream>
#include <map>
#include <string>

class client {
private:
    std::string nickname;
    int nb;
public:
    client(std::string nickname, int id) : nickname(nickname), id(id) {
		std::cout << "USER WITH " << id << " WAS CREATED\n";
	}
};

int main() {
    std::map<int, client> lol;
    std::string hello = "hello";
    client Client(hello, 4);
	lol.push_back(4, hello);
    // lol[0] = Client;
    return 0;
}


// int main(){
// 	std::map<int , class client> lol;
// 	string hello = "hello";
// 	client Client(hello, 4);
// 	lol[0] = Client;
// 	}