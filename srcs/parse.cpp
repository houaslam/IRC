
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

bool parse(class Server &server,int fd, string reqs){
    channelCheck(server);
    cout << BLUE << "->" << reqs << RESET;
    reqs = withoutNewLine(reqs);


    vector<string> line;
    line = split(reqs, " ");

    if (line.empty())
        return true;

    string commands[] = {"USER", "NICK", "PASS", "EXIT", "JOIN", "TOPIC", "MODE", "INVITE", "BMR", "PRIVMSG", "KICK", "PART", "PING", "WHOIS", "CAP"};
    size_t n = 0;

    size_t size =  sizeof(commands) / sizeof(string);
    while (n < size && commands[n].compare(line[0]))
            n++;
    if (n == 13 || n == 14)
        return true;
    switch (n)
    {
        if (server.getCLients()[fd].isConnected == false && (n >= 4 && n <= 11)){
		    sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "", "", "")[NOT_REGISTRED]);
            break;
        }
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
            return false;
        case 4:
            join(server, reqs, fd);
            break;
        case 5:
            topic(server, reqs, fd);
            break;
        case 6:
            mode(server, reqs, fd);
            break;
        case 7:
            invite(server, reqs, fd);
            break;
        case 8:
            bot(fd, reqs, server);
            break;
        case 9:
            privmsg(server, reqs, fd);
            break;
        case 10:
            kick(server, reqs, fd);
            break;
        case 11:
            part(server, reqs, fd);
            break;
        case 12:
        {
            cout << "PING WAS RECIEVED\n";
            string pong = "PONG :" + reqs.substr(5) +"\r\n";
            cout << "sending" << pong << endl;
            send(fd, pong.c_str(), pong.size(), 0);
            break;
        }
        default:{
            if (server.getCLients()[fd].isConnected == true)
                sendMsg(server.getCLients()[fd], msgs(server.getCLients()[fd], "" ,"", reqs)[UNKNOW_CMD]);
            break;
        }
    }

    return true;
}