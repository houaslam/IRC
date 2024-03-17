
#include "../includes/client.hpp"

void parse(client client, string reqs){
    vector<string> line;

    line = split(reqs, " ");

    string commands[] = {"USER", "NICK", "JOIN", "SEND"};
    int i = 0;
    while (commands[i].compare(line[0]))
        i++;
    switch (i)
    {
        case 0:
            user(line);
        //    fall through
           break;
        case 1:
            nick(client.getNickName(), reqs, line.size());
            // fall through
            break;
        // case 2:
        //     warning();
        //     // fall through
            // break;
        // case 3:
        //     error();
            // break;
        default:
            cout << ":@localhost 421\t" << reqs << " :Unknown command\n";
            break;
    }

}