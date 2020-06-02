#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "deap.h"

using namespace std;

void split(const string& str, vector<string>& cont, char delim = ' '){
    stringstream ss(str);
    string token;
    cont.clear();
    while (getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

int main()
{
    Deap* printers;
    
    string inputLine;
    vector<string> lineSplit;
    getline(cin, inputLine);
    split(inputLine, lineSplit);

    const unsigned N = stoi(lineSplit[0]);
    const unsigned M = stoi(lineSplit[1]);
    printers = new Deap[N];
    for (unsigned i=0; i<N; i++)
        printers[i] = Deap(M);

    int id;
    unsigned q;
    Job j;
    while (getline(cin, inputLine)) {
        split(inputLine, lineSplit);
        if (lineSplit[0] == "add") {
            j.setJob(
                stoi(lineSplit[1]), 
                stoi(lineSplit[2])
            );
            id = stoi(lineSplit[3]);
            printers[id].add(id, j);
        }
        else if (lineSplit[0] == "quota") {
            q = stoi(lineSplit[1]);
            id = stoi(lineSplit[2]);
            printers[id].quota(id, q);
        }
        else if (lineSplit[0] == "drop") {
            id = stoi(lineSplit[1]);
            printers[id].drop(id);
        }
        else if (lineSplit[0] == "print") {
            id = stoi(lineSplit[1]);
            printers[id].print(id);
        }
        else break;
    }

    return 0;
}