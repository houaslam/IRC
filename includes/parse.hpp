#pragma once

#include "client.hpp"

using namespace std;

void user(vector<string> line);
void parse(class Client client, string line);
void nick(string &nickname,string line, size_t size);
string &withoutNewLine(string &line);
