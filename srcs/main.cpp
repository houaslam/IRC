#include "../includes/server.hpp"
#include "../includes/client.hpp"

// void sendMsgg(Client& client, string str){
//     str = str + "\r\n";
//     send(client.get_fd(), getTime().c_str(), getTime().length(), 0);
//     send(client.get_fd(), getLocalhost(client).c_str(), getLocalhost(client).length(), 0);
//     send(client.get_fd(), str.c_str(), str.length() , 0);
// }

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
							fcntl(fd, F_SETFL, O_NONBLOCK);
							Client  user_(fd);
							server.setUser(user_);
							add_fd(fds, &nb_fds, user_.get_fd());
							// sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],))//  "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"

						}

						else {
							int k = read(fds[i].fd, reqs, sizeof(reqs));
							// int k = recv(fds[i].fd, reqs, sizeof(reqs), 0);
							// int k = read(fds[i].fd, reqs, sizeof(reqs));
							if (k > 0){
								reqs[k] = '\0';
								
								cout << "with newline -> " << "[" << reqs << "]"<< endl;
							    if (parse(server, fds[i].fd, reqs) == false)
									cout << "exit\n";
							}

							else{
								if (k == 0){
									// cout << "a user is disconnected\n";
									server.getCLients().erase(fds[i].fd);
									// unsetChannelUser
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
// /connect localhost 8500
