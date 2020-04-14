#include "cmdParser.hpp"

using namespace std;

void CmdParser::readCmd(vector<string>& inputLineSplit){
    string cmdType = inputLineSplit[0];
    if(cmdType == "get"){
        assert(inputLineSplit.size() == 4);
        cmdQue.push(inputLineSplit);
    }else if(cmdType == "purchased"){
        assert(inputLineSplit.size() == 2);
        cmdQue.push(inputLineSplit);
    }else if(cmdType == "clicked"){
        assert(inputLineSplit.size() == 3);
        cmdQue.push(inputLineSplit);
        prodFieldVec.push_back(inputLineSplit[1]);
        prodFieldVec.push_back(inputLineSplit[2]);
    }else if(cmdType == "profit"){
        assert(inputLineSplit.size() == 3);
        cmdQue.push(inputLineSplit);
    }else if(cmdType == "quit"){
        assert(inputLineSplit.size() == 1);
        cmdQue.push(inputLineSplit);
    }
    return;
}

bool CmdParser::empty(){
    if(cmdQue.empty())
        return true;
    else
        return false;
}

void CmdParser::setProdField(){
    prodUser.setProdField(prodFieldVec);
}

void CmdParser::makeProfit(){
    userMap.makeUserProfit();
}

void CmdParser::readLine(vector<string>& inputLineSplit){
    prodUser.insertProdUser(inputLineSplit[PROD_ID], inputLineSplit[USER_ID]);
    userMap.insertUser(inputLineSplit);
}

void CmdParser::sortProdUser(){
    prodUser.sortProdUser();
}

void CmdParser::execCmd(){
    vector<string> cmdCurrent = cmdQue.front();

    if(cmdCurrent[0] == "quit"){
        cmdQue.pop();
        return;
    }

    cout
    << "********************"
    << endl;

    if(cmdCurrent[0] == "get"){
        userMap.printUserSale(
            cmdCurrent[1],
            cmdCurrent[2],
            cmdCurrent[3]
        );

    }else if(cmdCurrent[0] == "purchased"){
        userMap.printUserInfo(cmdCurrent[1]);

    }else if(cmdCurrent[0] == "clicked"){
        prodUser.printItersect(
            cmdCurrent[1],
            cmdCurrent[2]
        );

    }else if(cmdCurrent[0] == "profit"){
        userMap.printUserProfit(
            cmdCurrent[1],
            cmdCurrent[2]
        );
    }

    cout
    << "********************"
    << endl;
    cmdQue.pop();

    return;
}