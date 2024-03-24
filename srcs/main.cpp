#include "../includes/server.hpp"
#include "../includes/client.hpp"


int main(int ac , char ** av){

	if (ac == 3){

		Server server(atoi(av[1]), av[2]);
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
    						sendMsg(fd,":" + server.getServerName() + " 001 " + user_.getNickName() + " :Welcome to the Internet Relay Network");
    						sendMsg(fd,":" + server.getServerName() + " 002 " + user_.getNickName() + " :Your host is " + server.getServerName() + " ");
    						sendMsg(fd,":" + server.getServerName() + " 003 " + user_.getNickName() + " :This server was created 0 ");
    						sendMsg(fd,":" + server.getServerName() + " 004 " + user_.getNickName() + " :" + server.getServerName() + " 1.1 More info");

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
