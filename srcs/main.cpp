#include "../includes/server.hpp"
#include "../includes/client.hpp"


int main(int ac , char ** av){

	if (ac == 3){

		Server server(atoi(av[1]), av[2]);
		// server.setTime(NULL);
		char reqs[1024];
		struct pollfd fds[1024];
		fds[0].fd = server.get_socket();
		fds[0].events = POLLIN;
    	socklen_t add_size = sizeof(server.get_addr_len());

		int nb_fds = 1;

		while(true){

			if (poll(fds, nb_fds, 0) > 0){

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
							int k = recv(fds[i].fd, reqs, sizeof(reqs), 0);
							if (k > 0){
								reqs[k] = '\0';
							    if (parse(server, fds[i].fd, reqs) == false)
									cout << "exit\n";
							}

							else{
								if (k == 0){
									cout << "a user is disconnected\n";
									server.getCLients().erase(fds[i].fd);
								}
								else
									ft_error("DONE : ");
								del_fd(fds, &nb_fds, i);
							}
						}
					}
				}
			}
		}
	}
}
