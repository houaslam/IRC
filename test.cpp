#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    // Method 1: Using erase() by index
    // size_t index_to_remove = 2; // Index of element to remove
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == 3)
            vec.erase(vec.begin() + i);

    }
    // if (index_to_remove < vec.size()) {
    //     vec.erase(vec.begin() + 1);
    // }
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Method 2: Using std::remove() and erase() to remove by value
    // int value_to_remove = 4; // Value to remove
    // vec.erase(std::remove(vec.begin(), vec.end(), value_to_remove), vec.end());
    // for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    std::cout << std::endl;

    return 0;
}
