#include "../includes/irc.hpp"

void del_fd(struct pollfd fds[], int* fd_count, int p){
	fds[p].fd = fds[*fd_count - 1].fd;
	(*fd_count)--;
}

void add_fd(struct pollfd fds[], int* fd_count, int fd){
	fds[(*fd_count)].fd = fd;
	fds[(*fd_count)].events = POLLIN;
	std::cout << BLUE << "NEW CONNECTION\n" << RESET;
	(*fd_count)++;
}

int main(int ac , char ** av){

	if (ac == 3){
	
		Server server(8500, av[2], av[1]);
		char reqs[1024];
		int client;
		struct pollfd fds[5];
		fds[0].fd = server.get_socket();
		fds[0].events = POLLIN;
		socklen_t add_size = sizeof(server.get_addr_len());
		int nb_fds = 1;
		

		while(true){

			if (poll(fds, nb_fds, 0) > 0){

				for (int i = 0; i < nb_fds; i++){

					if (fds[i].revents == POLLIN){
						if (fds[i].fd == server.get_socket()){
							client = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);
							if (client <= 0)
								ft_error("CLIENT : ");
							add_fd(fds, &nb_fds, client);
						}

						else{
							int k = recv(fds[i].fd, reqs, sizeof(reqs), 0);

							if (k > 0){
								reqs[k] = '\0';
								std::cout << "client = " << reqs;
							}

							else{
								del_fd(fds, &nb_fds, i);

								if (k == 0){
									std::cout << BLUE << "BYE BYE\n" << RESET;
									continue;
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