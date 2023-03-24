#include <iostream>
#include <string>
#include <vector>

std::string join(std::vector<std::string> list, char separator) {
    std::string result = "";
    for (int i = 0; i < list.size(); i++) {
        if (i > 0) {
            result += separator;
        }
        result += list[i];
    }
    return result;
}