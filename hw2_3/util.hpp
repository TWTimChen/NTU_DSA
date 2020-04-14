#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

////////////////////////////////////////////////////////////////////////
////////////////                 utils                  ////////////////
////////////////////////////////////////////////////////////////////////
void split(const std::string& str, std::vector<std::string>& cont, char delim = ' '){
    std::stringstream ss(str);
    std::string token;
    cont.clear();
    while (getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

#endif