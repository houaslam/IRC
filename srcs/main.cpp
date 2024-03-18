#include "../includes/server.hpp"
#include "../includes/client.hpp"

int main(int ac , char ** av){

	if (ac == 3){

		Server server(8500, av[2], av[1]);
		char reqs[1024];
		struct pollfd fds[1024];
		fds[0].fd = server.get_socket();
		fds[0].events = POLLIN;
		
		int nb_fds = 1;
        Client save;
		socklen_t add_size = sizeof(server.get_addr_len());

		while(true){

			if (poll(fds, nb_fds, 0) > 0){

				for (int i = 0; i < nb_fds; i++){

					if (fds[i].revents == POLLIN){
                        
						if (fds[i].fd == server.get_socket()){
    						int fd = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);
							if (fd <= 0)
								ft_error("CLIENT : ");
                            Client  user_("test", fd);
							save = user_;
							add_fd(fds, &nb_fds, user_.get_fd());
                            // server.adduser(user_);
							std::cout << "ALL USERS : " << std::endl;
							// server.aff_allusers();
						}

						else{
							int k = recv(fds[i].fd, reqs, sizeof(reqs), 0);
							if (k > 0){
								reqs[k] = '\0';
							    parse(save, reqs);
							}

							else{
								del_fd(fds, &nb_fds, i);
								if (k == 0)
									std::cout << BLUE << "BYE BYE\n" << RESET;
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
