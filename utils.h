//
// Created by winstonthebaker on 10/27/25.
//

#ifndef INVENTORYMANAGEMENT_UTILS_H
#define INVENTORYMANAGEMENT_UTILS_H
#include <string>

inline std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return ""; // string is all whitespace

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

#endif //INVENTORYMANAGEMENT_UTILS_H