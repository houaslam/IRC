#include "../includes/errors.hpp"

// voit sendError(server &server, int fd, int n)

string getErrorMsg(string errorNumber){
    string _errorMsg = "";

    std::string numbers[] = {"405", "421", "431", "433", "451", "461", "462", "464"};
    int i = 0;
    while (i < 8 && numbers[i].compare(errorNumber))
        i++;

    switch (i)
    {
    case (0):
        _errorMsg = " :You have joined too many channels\n";
        break;
    case (1):
        _errorMsg = " :Unknown command\n";
        break;
    case (2):
        _errorMsg = " :Nickname not given\n";
        break;
    case (3):
        _errorMsg = " :Nickname is already in use\n";
        break;
    case (4):
        _errorMsg = " :You have not registered\n";
        break;
    case (5):
        _errorMsg = " :Not enough parameters\n";
        break;
    case (6):
        _errorMsg = " :You may not register\n";
        break;
    case (7):
        _errorMsg = " :Password is incorrect\n";
        break;
    
    default:
        break;
    }
    
    return _errorMsg;
}

string getLocalhost(Client &client){
    return ":" + client.getNickName() + "!" + client.getUser() +"@localhost ";
}

void ft_unknownCmd(Client &client, int fd, string &line){

    vector<string> first = split(line, " ");

    string _errorMsg = getErrorMsg(UNKNOW_CMD);
    string localhost = getLocalhost(client);

    sendMsg(fd, localhost + UNKNOW_CMD + " " + client.getNickName() + " " + first[0] + _errorMsg);

}

// void ft_notEnoughParam(clien)