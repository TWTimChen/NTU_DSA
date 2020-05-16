#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include "tree.h"

using namespace std;

string& trim(string &s) {
    if (s.empty())
        return s;
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

void split(const std::string& str, vector<string>& cont, char delim = ' ') {
    stringstream ss(str);
    string token;
    cont.clear();
    while (getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

void parse(vector<string>& inputLineSplit, vector<int>& label, vector<vector<DATA_ID> >& data) {
    unsigned posComma, index;
    double value;
    DATA_ID dataId(0,data[0].size());
    
    label.push_back(stoi(inputLineSplit[0]));
    for(int i=0; i<data.size(); i++)
        data[i].push_back(dataId);

    for(int i=1; i<inputLineSplit.size(); i++) {
        posComma = inputLineSplit[i].find(":");
        index = stoi(inputLineSplit[i].substr(0,posComma)) - 1;
        value = stod(inputLineSplit[i].substr(posComma+1));
        data[index].back().first = value;
    }

    return;
}

int main(int argc, char **argv) {
    const double EPSILON = stod(argv[2]);
    // Get max index
    ifstream inputFile;
    inputFile.open(argv[1]);
    string inputLine;
    vector<string> inputLineSplit;

    unsigned indexMax, index;
    unsigned posSpace, posComma;
    while(getline(inputFile, inputLine)) {
        inputLine = trim(inputLine);
        posComma = inputLine.rfind(":");
        posSpace = inputLine.rfind(" ");
        index = stoi(inputLine.substr(posSpace+1, posSpace-posComma));
        indexMax = indexMax>index ? indexMax:index;
    }  
    inputFile.close();

    // Read and parse the data and label
    inputFile.open(argv[1]);
    vector<vector<DATA_ID> > data(indexMax);
    vector<int> label;

    unsigned lineCount;
    while(getline(inputFile, inputLine)) {
	    split(inputLine, inputLineSplit);
        parse(inputLineSplit, label, data);
        lineCount++;
    }
    inputFile.close();

    // Fit the data and construct a desision tree
    DTree dTree(EPSILON);

    dTree.fit(data, label);
    dTree.printTree();

    return 0;
}