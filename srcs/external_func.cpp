#include "../includes/server.hpp"

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

void dprint(int fd, string str){
    write(fd, &str, sizeof(str));
}

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
