#include "../includes/server.hpp"

void clearScreen(int fd) {
    const char* clear_cmd = "\033[H\033[2J"; 
    write(fd, clear_cmd, 10); 
}

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

void del_fd(struct pollfd fds[], int* fd_count, int p){
	close(fds[p].fd);
	fds[p].fd = fds[*fd_count - 1].fd;
	(*fd_count)--;
}

void add_fd(struct pollfd fds[], int* fd_count, int fd){
	fds[(*fd_count)].fd = fd;
	fds[(*fd_count)].events = POLLIN;
	std::cout << BLUE << "NEW CONNECTION\n" << RESET;
	(*fd_count)++;
}

string  getTime(void){
    time_t start = time(NULL);
    struct tm *time = localtime(&start);
    string res;
    res +=  "[" + nbtoString(time->tm_hour) +  ':'+  nbtoString(time->tm_min) +  ']' + " ";
    return res;
}
string nbtoString(int nb){
    std::stringstream ss;
    ss << nb;
    std::string str = ss.str();
    return str;
}

