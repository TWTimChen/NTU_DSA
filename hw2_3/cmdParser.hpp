#ifndef CMD_PARSE_H
#define CMD_PARSE_H

#include "prodUser.hpp"
#include "userMap.hpp"
#include <queue>

class CmdParser
{
public:
    CmdParser() {}
    ~CmdParser() {}
    void readCmd(std::vector<std::string>& inputLineSplit);
    const std::vector<std::string> getProdFieldVec() const {return prodFieldVec;}
    void setProdField();
    void makeProfit();
    void readLine(std::vector<std::string>& inputLineSplit);
    void sortProdUser();
    bool empty();
    void execCmd();

private:
    std::queue<std::vector<std::string> > cmdQue;
    std::vector<std::string> prodFieldVec;
    UserMap userMap;
    ProdUser prodUser;
};

#endif