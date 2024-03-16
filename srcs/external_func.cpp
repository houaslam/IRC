#include "../includes/irc.hpp"

void ft_error(string prob){
    string res = RED + prob + RESET;
    perror(res.c_str());
    exit(1);
}