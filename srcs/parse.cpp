
#include "../includes/server.hpp"

string &withoutNewLine(string &line){

    size_t newLine = line.find('\n');

    if (newLine != string::npos)
    {
        line.erase(newLine, 1);
    }
    return line;
}

// nick : check nick with others DONE
// nick : empty nick | return prev nickname DONE
// user : check the 4 arg 
// irssi connection
bool parse(class Server &server,int fd, string reqs){
    reqs = withoutNewLine(reqs);
    server.get_addr();

    vector<string> line;
    line = split(reqs, " ");

    string commands[] = {"USER", "NICK", "JOIN", "SEND", "EXIT"};
    int n = 0;
    if (line.empty())
        n = 6;
    else
        while (n < 5 && commands[n].compare(line[0]))
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
        default:{

            string str;
            str = ":" + server.getCLients()[fd].getNickName() +"!"+ server.getCLients()[fd].getUser() + ":@localhost 421\t"+ reqs +" :Unknown command\n";
            sendMsg(fd,str);
            break;
        }
    }

    return true;
}