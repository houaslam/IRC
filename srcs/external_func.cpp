#include "../includes/irc.hpp"

void ft_error(string prob){
    string res = RED + prob + RESET;
    perror(res.c_str());
    exit(1);
}

vector<string> split(string src, string s) {
    vector<string> ret;
    string str;

    size_t i = 0;
    size_t len = src.length();

    while (i < len) {
        size_t found = src.find(s, i);
        if (found > len) {
            str = src.substr(i); 
            i = len;
        }
        else {
            str = src.substr(i, found - i);
            i = found + s.length();
        }

        if (!str.empty()) {
            ret.push_back(str);
        }
    }

    return ret;
}


string strtrim(const string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) {
        start++;
    }

    size_t end = str.length();
    while (end > start && isspace(str[end - 1])) {
        end--;
    }

    return str.substr(start, end - start);
}