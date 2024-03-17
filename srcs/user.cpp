#include "../includes/parse.hpp"

void user(vector<string> line){
    (void)line;
}

void nick(string &nickname,string line, size_t size){
    if (size == 0)
        ft_error (":"+ nickname +"@localhost 431\t"+nickname+" :Nickname not given");
    // else
    // {
        
    //     nickname = 
    // }
    (void)line;
}
