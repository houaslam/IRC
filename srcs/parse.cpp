
#include "../includes/server.hpp"
#include "../includes/client.hpp"

string withoutNewLine(string &line){
    size_t pos = line.find('\r');

    if (pos != string::npos)
        line.erase(pos, 1);

    pos = line.find('\n');
    
    if (pos != string::npos)
        line.erase(pos, 1);
    
    return line;
}

void parse(class Server &server,int fd, string reqs){
    channelCheck(server);
    reqs = withoutNewLine(reqs);


    vector<string> line;
    line = split(reqs, " ");

    if (line.empty())
        return ;

    string commands[] = {"USER", "NICK", "PASS", "JOIN", "TOPIC", "MODE", "INVITE", "BMR", "PRIVMSG", "KICK", "PART", "PING", "WHOIS", "CAP"};
    size_t n = 0;

    size_t size =  sizeof(commands) / sizeof(string);
    while (n < size && commands[n].compare(line[0]))
            n++;
    if (n == 12 || n == 13)
        return ;
    if (server.getCLients()[fd].isConnected == false && (n >= 3 && n <= 10))
	    return sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "", "")[NOT_REGISTRED]);
    string color = RED;
    if (server.getCLients()[fd].isConnected == true)
        color = GREEN;
    cout << color << n << RESET<<endl;
    cout << "without" << n <<endl;
    switch (n)
    {
        case 0:
            user(server, reqs, fd);
           break;
        case 1:
            nick(server, reqs, fd);
            break;
        case 2:
            pass(server, reqs, fd);
            break;
        case 3:
            join(server, reqs, fd);
            break;
        case 4:
            topic(server, reqs, fd);
            break;
        case 5:
            mode(server, reqs, fd);
            break;
        case 6:
            invite(server, reqs, fd);
            break;
        case 7:
            bot(fd, reqs, server);
            break;
        case 8:
            privmsg(server, reqs, fd);
            break;
        case 9:
            kick(server, reqs, fd);
            break;
        case 10:
            part(server, reqs, fd);
            break;
        case 11:
        {
            string pong = "PONG :";
            if (reqs.size() > 5)
                pong += reqs.substr(5);
            pong +="\r\n";
            send(fd, pong.c_str(), pong.size(), 0);
            break;
        }
        default:{
            if (server.getCLients()[fd].isConnected == true)
                sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "" ,"", reqs)[UNKNOW_CMD]);
            break;
        }
    }

    return ;
}