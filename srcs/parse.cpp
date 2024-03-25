
#include "../includes/server.hpp"

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

    string commands[] = {"USER", "NICK", "JOIN", "SEND", "EXIT", "PASS", "TOPIC"};
    int n = 0;
    // cout  << commands->size();
    if (line.empty())
        n = 8;
    else
        while (n < 8 && commands[n].compare(line[0]))
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
        default:{
            ft_unknownCmd(server.getCLients()[fd], fd, line[0]);
            break;
        }
    }

    return true;
}