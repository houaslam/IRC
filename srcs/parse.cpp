
#include "../includes/parse.hpp"

string &withoutNewLine(string &line){

    size_t newLine = line.find('\n');

    if (newLine != string::npos)
    {
        line.erase(newLine, 1);
    }
    return line;
}

void parse(Client client, string reqs){
    
    reqs = withoutNewLine(reqs);
    // int fd =client.get_fd();

    vector<string> line;
    line = split(reqs, " ");

    string commands[] = {"USER", "NICK", "JOIN", "SEND"};
    int i = 0;
    if (line.empty())
        i = 5;
    else
        while (i < 4 && commands[i].compare(line[0]))
            i++;
    switch (i)
    {
        case 0:
            user(line);
        //    fall through
           break;
        case 1:
            nick(client.getNickName(), reqs, line.size());
            cout << client.getNickName() << endl;
            // fall through
            break;
        // case 2:
        //     join();
            // fall through
            // break;
        // case 3:
        //     ();
            // break;
        default:
            // dprint(client.get_fd(), client.getNickName() +":@localhost 421\t"   + " :Unknown command\n");
            
            cout << client.getNickName() <<":@localhost 421\t"   << " :Unknown command\n";
            // char res[1024];
            send(client.get_fd(), "test", 4, 0);
            // send(client.get_fd(), client.getNickName()+":@localhost 421\t:Unknown command\n", client.getNickName().size() + 34, 0);
            cout << "client fd = " << client.get_fd() << endl;
            break;
    }

}