#pragma once

#include "server.hpp"


       /* ERRORS */
#define IN_CHANNEL			    "405"  //  " :You have joined too many channels"
#define UNKNOW_CMD			    "421"  // :Unknown command
#define NICK_NOT_GIVEN		    "431"  // :Nickname not given"
#define NICK_IN_USE			    "433"  //  :Nickname is already in use"
#define NOT_REGISTRED		    "451"  // :You have not registered
#define NOT_ENOUGH_PARA		    "461"  //  :Not enough parameters
#define ALREADY_REGISTERED	    "462"  //  :You may not register
#define INCORRECT_PWD		    "464"  // :Password is incorrect"

void ft_unknownCmd(Client &client, int fd, string &line);
