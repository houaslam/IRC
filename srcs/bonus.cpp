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
		
	if (server.getCLients()[fd].isConnected == false)
		return sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","", "")[NOT_REGISTRED]);
	line = line.substr(3);
	line = strtrim(line);
	vector<string> res = split(line, " ");
	if (line.empty() || res.size() != 2)
		return sendMsg(server.getCLients()[fd], "Incorrect format: BMR weight height\n");

	sendMsg(server.getCLients()[fd], "WELCOME TO PIXER SERVER BOT\n");
	bmr = get_info(fd,  res[0], 30, 150);
	if (bmr < 0)
		return;

	int h = get_info(fd, res[1], 100,  210);
	if (h < 0)
		return;

	bmr /=  h * h;
	bmr *= 10000;

	if (bmr > 35)
		sendMsg(server.getCLients()[fd], "\033[31mYou are extremly obese\n\033[0m");
	else if (bmr < 34.9 && bmr > 30)
		sendMsg(server.getCLients()[fd], "\033[33mYou are obese\n\033[0m");
	else if (bmr < 29.9 && bmr > 25)
		sendMsg(server.getCLients()[fd], "\033[35mYou are overweight\n\033[0m");
	else if (bmr > 18.5 && bmr < 24.9)
		sendMsg(server.getCLients()[fd], "\033[32mYou are normal\n\033[0m");
	else if ( bmr < 18.5)
		sendMsg(server.getCLients()[fd], "\033[31mYou are underweight\n\033[0m");
}
