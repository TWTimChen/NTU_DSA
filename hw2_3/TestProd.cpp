#include "userMap.hpp"
#include "prodUser.hpp"

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
    const int 
    SALE            = 0,
    TIMESTAMP       = 3,
    PROD_PRICE      = 5,
    PROD_AGE_GOURP  = 6,
    PROD_GENDER     = 9,
    PROD_ID         = 19,
    USER_ID         = 21;

    string inputLine;
    vector<string> inputLineSplit;
    int numLine;
    if(argc >= 3){
        numLine = atoi(argv[2]);
    } else numLine = 10000;

    ifstream inputFile;
    inputFile.open(argv[1]);

    ProdUser prodUser;
    string prod1 = "A66DB02AC1726A8D79C518B7F7AB79F0";
    string prod2 = "-1";
    vector<string> prodField;
    prodField.push_back(prod1);
    prodField.push_back(prod2);

    prodUser.setProdField(prodField);
    for(int i=0; i<numLine; i++){
        getline(inputFile, inputLine);
        split(inputLine, inputLineSplit, '\t');

        assert(inputLineSplit.size() == 23);
        prodUser.insertProdUser(
            inputLineSplit[PROD_ID],
            inputLineSplit[USER_ID]
        );
        /*
        cout << "---------------------------------------------"
        << " Line "
        << i << " "
        << "---------------------------------------------"
        << endl;

        for(int i=0; i<inputLineSplit.size(); i++){
            cout << inputLineSplit[i] << endl;
        }
        */
    }

    prodUser.sortProdUser();

    cout << "---------------------------------------------"
    << " " << "TestClick" << " "
    << "---------------------------------------------"
    << endl
    << "Prod1: " 
    << prod1
    << endl
    << "Prod2: " 
    << prod2
    << endl;

    prodUser.printItersect(prod1, prod2);

    return 0;
}
