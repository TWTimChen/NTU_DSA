#include "cmdParser.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////
////////////////                 utils                  ////////////////
////////////////////////////////////////////////////////////////////////
void split(const string& str, vector<string>& cont, char delim = ' '){
    stringstream ss(str);
    string token;
    cont.clear();
    while (getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

////////////////////////////////////////////////////////////////////////
////////////////                 main                   ////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    CmdParser cmdParser;
    string inputLine;
    vector<string> inputLineSplit;
    while(cin){
        getline(cin, inputLine);
        split(inputLine, inputLineSplit, ' ');
        if(inputLineSplit.size() == 0) break;
        cmdParser.readCmd(inputLineSplit);
    }

    return 0;
}
