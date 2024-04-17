
#include "../includes/server.hpp"
#include "../includes/client.hpp"

string &withoutNewLine(string &line){

    size_t newLine = line.find('\n');

    if (newLine != string::npos)
    {
        line.erase(newLine, 1);
    }
    return line;
}

bool parse(class Server &server,int fd, string reqs){
    reqs = withoutNewLine(reqs);
    server.get_addr();

    vector<string> line;
    line = split(reqs, " ");

    if (line.empty())
        return true;

<<<<<<< HEAD
    string commands[] = {"USER", "NICK", "JOIN", "SEND", "EXIT", "PASS", "TOPIC", "MODE", "INVITE", "BMR", "PRIVMSG", "PART", "KICK"};
=======
    string commands[] = {"USER", "NICK", "JOIN", "SEND", "EXIT", "PASS", "TOPIC", "MODE", "INVITE", "BMR", "PRIVMSG", "PING", "PART"};
>>>>>>> refs/remotes/origin/main
    size_t n = 0;
    size_t size =  sizeof(commands) / sizeof(string);
    if (line.empty())
        n = size;
    else
        while (n < size && commands[n].compare(line[0]))
            n++;
    cerr << "-----------COMMAND---------------->" << reqs  << "|\n";
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
            cout << "-----------PING---------------->" << reqs << endl;
            break;
        case 12:
            part(server, reqs, fd);
            break;
        case 12:
            kick(server, reqs, fd);
            break;
        default:{
            sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "" ,"", reqs)[UNKNOW_CMD]);
            break;
        }
    }

    return true;
}