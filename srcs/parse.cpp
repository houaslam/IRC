
#include "../includes/server.hpp"

string &withoutNewLine(string &line){

    size_t newLine = line.find('\n');

    if (newLine != string::npos)
    {
        line.erase(newLine, 1);
    }
    return line;
}

bool parse(class Server &server,int i, string reqs){
    // server.getCLients()[i].setId(i);
    // int fd = server.getCLients()[i].get_fd();
    reqs = withoutNewLine(reqs);

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
            user(line);
           break;
        case 1:
            nick(server.getCLients()[i].getNickName(), reqs, 1);
            break;
        // case 2:
        //     join();
            // fall through
            // break;
        // case 3:
        //     ();
            // break;
        case 4:
            return false;
            // break;
        default:
            // dprint(server.getCLients().get_fd(), server.getCLients().getNickName() +":@localhost 421\t"   + " :Unknown command\n");
            dprint(1, "Ambiguous command\n");
            // dprint(server.getCLients()[i].get_fd(), "Ambiguous command\n");
            break;
    }

    return true;
}