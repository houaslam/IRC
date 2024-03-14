#include "../includes/irc.hpp"

int main(){
	Server server(8500, "7894");
	char reqs[1024];
	struct po
	socklen_t add_size = sizeof(server.get_addr_len());
	int client = accept(server.get_socket(), (struct sockaddr *)&server.get_addr(), &add_size);

	if (client <= 0)
		ft_error("CLIENT : ");
	std::cout << "new connection\n";

	while(true){

		int k = recv(client, reqs, sizeof(reqs), 0);

		if (k > 0){
			reqs[k] = '\0';
			std::cout << "LOL = " << reqs << std::endl;
		}

		else if (k == 0){
			std::cout << "BYE BYE\n";
			break;
		}

		else{
			close(client);
			ft_error("DONE : ");
		}
	}
}