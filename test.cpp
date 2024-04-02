#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    if (index_to_remove < vec.size()) {
        vec.erase(vec.begin() + 4);
    }
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // int value_to_remove = 4;
         // vec.erase(std::remove(vec.begin(), vec.end(), value_to_remove), vec.end());
    // for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    std::cout << std::endl;

    return 0;
}


