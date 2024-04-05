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

void* bot(void *arg){
    Server *server = static_cast<Server *>(arg);
    int fd = server->curr_fd;
	double bmr;
		
    // if (server->getCLients()[fd].getNickName().empty()){
	// 	// sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd],"","", )[NOT_REGISTRED]);
	// // 	return ;
	// }
    cerr << "HELLO FROM THREAD" << endl;
	FILE* file = fdopen(fd, "r");
	send(fd, "WELCOME TO PIXER SERVER BOT\n", 29, 0);
	bmr =  get_info(file, fd, "Enter your weight(KG) :", 30, 150);
    int h = get_info(file, fd, "Enter your height(CM) :", 100,  210);
    bmr /=  h * h;
    bmr *= 10000;
    send(fd, "\n\n", 7, 0);
    // cout << bmr << endl;
    if (bmr > 35)
        send(fd, "You are extremly obese\n", 24, 0);
    else if (bmr > 34.9 && bmr < 30)
        send(fd, "You are obese\n", 15, 0);
    else if (bmr > 29.9 && bmr < 25)
        send(fd, "You are overweight\n", 20, 0);
    else if (bmr > 18.5 && bmr < 24.9)
        send(fd, "You are extremly normal\n", 24, 0);
    else if ( bmr < 18.5)
        send(fd, "You are underweight\n", 21, 0);
    return NULL;
}
