
#include "../includes/server.hpp"
#include "../includes/client.hpp"

string withoutNewLine(string &line){
    // string ret ;
    
    // int j = 0;
    // int i = 0;
    // while (line[i])
    // {
    //     if (line[i] != '\n' && line[i] != '\r'){
    //         ret[j] = line[i];
    //         j++;
    //     }
    //     i++;
    // }
    
    // // for (size_t i = 0; i < line.size(); i++)
    // // {
    // // }
    // // return "";
    // ret[j++] = '\0';
    size_t pos = line.find('\r');

    if (pos != string::npos)
        line.erase(pos, 1);

    pos = line.find('\n');
    
    if (pos != string::npos)
        line.erase(pos, 1);
    
    return line;
}

bool parse(class Server &server,int fd, string reqs){
    reqs = withoutNewLine(reqs);

    vector<string> line;
    line = split(reqs, " ");

    if (line.empty())
        return true;

    string commands[] = {"USER", "NICK", "JOIN", "SEND", "EXIT", "PASS", "TOPIC", "MODE", "INVITE", "BMR", "PRIVMSG", "PING", "PART", "KICK"};
    size_t n = 0;
    size_t size =  sizeof(commands) / sizeof(string);
    if (line.empty())
        n = size;
    else
        while (n < size && commands[n].compare(line[0]))
            n++;
    switch (n)
    {
        case 0:
            user(server, reqs, fd);
           break;
        case 1:
            nick(server, reqs, fd);
            break;
        case 2:
            join(server, reqs, fd);
            break;
        case 4:
            return false;
        case 5:
            pass(server, reqs, fd);
            break;
        case 6:
            topic(server, reqs, fd);
            break;
        case 7:
            mode(server, reqs, fd);
            break;
        case 8:
            invite(server, reqs, fd);
            break;
        case 9:
            bot(fd, reqs, server);
            break;
        case 10:
            privmsg(server, reqs, fd);
            break;
        case 11:
            // cout << "-----------PING---------------->" << reqs << endl;
            sendMsg(server.getCLients()[fd], "PONG");
            break;
        case 12:
            part(server, reqs, fd);
            break;
        case 13:
            kick(server, reqs, fd);
            break;
        default:{
            sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "" ,"", reqs)[UNKNOW_CMD]);
            break;
        }
    }

    return true;
}