#include "userMap.hpp"

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
    USER_ID         = 22;

    string inputLine;
    vector<string> inputLineSplit;
    int numLine;
    if(argc >= 3){
        numLine = atoi(argv[2]);
    } else numLine = 10000;

    UserMap userMap;
    ifstream inputFile;
    inputFile.open(argv[1]);

    int userCount = 0;
    string testUser1 = "E3DDEB04F8AFF944B11943BB57D2F620";
    string testProd = "A66DB02AC1726A8D79C518B7F7AB79F0";
    string testTime = "1598891820";
    string testTheta = "0";

    for(int i=0; i<numLine; i++){
        getline(inputFile, inputLine);
        split(inputLine, inputLineSplit, '\t');

        assert(inputLineSplit.size() == 23);
        userMap.insertUser(inputLineSplit);

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

        if(inputLineSplit[USER_ID] == testUser1)
            userCount++;
    }

    cout << "---------------------------------------------"
    << " " << "TestGet" << " "
    << "---------------------------------------------"
    << endl
    << "User: " 
    << testUser1
    << endl
    << "Prod: " 
    << testProd
    << endl
    << "Time: " 
    << testTime
    << endl;
    userMap.printUserSale(testUser1, testProd, testTime);

    cout << "---------------------------------------------"
    << " " << "TestUser" << " "
    << "---------------------------------------------"
    << endl
    << "User: " 
    << testUser1
    << endl
    << "Click: " 
    << userCount
    << endl;
    userMap.printUserInfo(testUser1);

    cout << "---------------------------------------------"
    << " " << "TestProfit" << " "
    << "---------------------------------------------"
    << endl
    << "Time: " 
    << testTime
    << endl
    << "Theta: " 
    << testTheta
    << endl;
    userMap.printUserProfit(testTime,testTheta);

    return 0;
}
