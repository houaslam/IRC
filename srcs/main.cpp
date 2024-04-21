#include "../includes/server.hpp"
#include "../includes/client.hpp"
#include "limits.h"

int main(int ac , char ** av){
	if (ac == 3){
		Server server(atoi(av[1]), av[2]);
		char reqs[MAX_CANON];
		struct pollfd fds[MAX_CANON];
		fds[0].fd = server.get_socket();
		fds[0].events = POLLIN;
		socklen_t add_size = sizeof(server.get_addr_len());

		int nb_fds = 1;
		cout << GREEN << "[🤗 Welcome to our server]" << endl<< RESET;
		while(true){


			if (poll(fds, nb_fds, -1) > 0){
				for (int i = 0; i < nb_fds; i++){
					if (fds[i].revents == POLLIN){

						if (fds[i].fd == server.get_socket()){
							int fd = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);
							if (fd <= 0)
								ft_error("CLIENT : ");
							Client  user_(fd);
							server.setUser(user_);
							add_fd(fds, &nb_fds, user_.get_fd());
						}

						else {
							int k = read(fds[i].fd, reqs, sizeof(reqs));
							if (k >= MAX_CANON)
								break;
							if (k > 0){
								reqs[k] = '\0';
							    parse(server, fds[i].fd, reqs);
							}

							else{
								if (k == 0){
									cout << YELLOW << "[👋 Goodbye!]" << endl << RESET;
									server.getCLients().erase(fds[i].fd);
									del_fd(fds, &nb_fds, i);
								}
								else
									ft_error("DONE : ");
							}
						}
					}
				}
			}
		}
	}
}


