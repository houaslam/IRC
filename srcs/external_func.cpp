#include "../includes/irc.hpp"

void ft_error(string prob){
    perror(prob.c_str());
    exit(1);
}