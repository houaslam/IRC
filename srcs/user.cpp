#include "../includes/parse.hpp"

void user(vector<string> line){
    (void)line;
}

void nick(string &nickname,string line, size_t size){
    if (size == 1)
        cout << ":"+ nickname +"@localhost 431\t"+ nickname +" :Nickname not given\n";
    else
    {
        line = line.substr(4);
        line = strtrim(line);
        nickname = line;

    }
}
