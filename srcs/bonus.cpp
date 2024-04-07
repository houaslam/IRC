#include "../includes/server.hpp"

int get_info( int fd ,string buf, int min , int max){
	int w = atoi(buf.c_str());
	if (w <= min || w > max){
		string war = "\033[31mINVALID\n\033[0m";
		send(fd, war.c_str() , war.length(), 0);
		return -1;
	}
	return w;
}

void bot(int fd, string line,  Server& server){

	double bmr;
		
	if (server.getCLients()[fd].getNickName().empty()){
		// sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","", )[NOT_REGISTRED]);
	// 	return ;
	}
	line = line.substr(4);
	line = strtrim(line);
	vector<string> res = split(line, " ");
	if (line.empty() || res.size() != 2){
		send(fd, "Incorrect format: BMR weight height\n", 37, 0);
		return;
	}

	send(fd, "WELCOME TO PIXER SERVER BOT\n", 29, 0);
	bmr = get_info( fd,  res[0], 30, 150);
	if (bmr < 0)
		return;
	int h = get_info(fd, res[1], 100,  210);

	// sleep(1);
	// send(fd, ".", 2, 0);
	// sleep(1);
	// send(fd, ".", 2, 0);
	// sleep(1);
	// send(fd, ".", 2, 0);
	// sleep(1);
	// send(fd, ".\n", 3, 0);
	bmr /=  h * h;
	bmr *= 10000;

	if (bmr > 35)
		send(fd, "\033[31mYou are extremly obese\n\033[0m", 33, 0);
	else if (bmr < 34.9 && bmr > 30)
		send(fd, "\033[33mYou are obese\n\033[0m", 25, 0);
	else if (bmr < 29.9 && bmr > 25)
		send(fd, "\033[35mYou are overweight\n\033[0m", 29, 0);
	else if (bmr > 18.5 && bmr < 24.9)
		send(fd, "\033[32mYou are normal\n\033[0m", 25, 0);
	else if ( bmr < 18.5)
		send(fd, "\033[31mYou are underweight\n\033[0m", 30, 0);
}
