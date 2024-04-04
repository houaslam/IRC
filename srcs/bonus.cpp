#include "../includes/server.hpp"

int get_info(FILE* file, int fd , string msg, int min , int max){
    char buf[1024];
    *buf = '\0';
    int w;

    while(*buf == '\0'){
        send(fd, msg.c_str(), msg.length(), 0);
        fgets(buf, 1024, file);
	    w = atoi(buf);
        if (w <= min || w > max){
            string war = "\033[31mINVALID\n\033[0m";
            send(fd, war.c_str() , war.length(), 0);
            *buf = '\0';
        }
    }
    return w;
}

int get_gender(FILE* file, int fd){
    char buf[1024];
    *buf = '\0';
	send(fd, "Enter your age (F/M) :", 26, 0);
    while(*buf != '\0'){
	    fgets(buf, 1024, file);
        string line = buf;
	    if (!line.compare("F\n"))
	    	return -161;
        else if (!line.compare("F\n"))
	    	return 5;
        else{
            line = "\033[31mINVALID\033[0m\n";
            send(fd, line.c_str(), 9, 0);
            *buf = '\0';
        }
    }
	return 0;
}

void bot(Server& server, int fd){
	double bmr;
		
    if (server.getCLients()[fd].getNickName().empty()){
		sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","")[NOT_REGISTRED]);
	// 	return ;
	}
	FILE* file = fdopen(fd, "r");
	send(fd, "WELCOME TO PIXER SERVER BOT\n", 29, 0);
	bmr = 10 * get_info(file, fd, "Enter your weight(KG) :", 30, 150);
    bmr += 6.25 * get_info(file, fd, "Enter your height(CM) :", 100,  210);
    bmr -= 5 * get_info(file, fd, "Enter your age :", 17, 80);
    bmr += get_gender(file, fd);
	// // FEMALE = BMR - 161
	// MALE = BMR + 5 
}
