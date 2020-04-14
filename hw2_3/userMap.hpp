#ifndef USER_MAP_H
#define USER_MAP_H

#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>

extern const int 
SALE            ,
TIMESTAMP       ,
PROD_PRICE      ,
PROD_AGE_GOURP  ,
PROD_GENDER     ,
PROD_ID         ,
USER_ID         ;

typedef std::pair<std::string, int> ID_TIME;

struct CompareLess{
    bool operator()(const ID_TIME& pair1,const ID_TIME& pair2) const {
        if(pair1.first < pair2.first){
            return true;
        }else if (pair1.first == pair2.first){
            if(pair1.second < pair2.second) 
                return true;
            else 
                return false;
        }else
            return false;
    }
};

class UserData
{
public:
    UserData(): nClick(0) {}
    ~UserData() {}

    void insertUserInfo(std::vector<std::string>& inputLineSplit);
    int getSaleByIdTime(std::string& id, int& time);
    void printByIdTime();
    void makeProfit();
    float getProfit(const int& time);

private:
    int nClick;
    std::map<ID_TIME, int, CompareLess> idTimeMap;
    std::map<int, int> saleByTime;
    std::map<int, float> profitByTime;
    std::vector<int> sale;
    std::vector<std::string> prodPrice;
    std::vector<std::string> prodAgeGroup;
    std::vector<std::string> prodGender;
};


class UserMap
{
public:
    UserMap(): nUser(0){};
    ~UserMap();

    void insertUser(std::vector<std::string>& inputLineSplit);
    void printUserSale(std::string& userId, std::string& prodId, std::string& time);
    void printUserInfo(std::string& userId);
    void makeUserProfit();
    void getUserProfit(const int& time, const float& theta, std::vector<std::string>& retUser);
    void printUserProfit(std::string& time, std::string& theta);
    int getNumUser(){return nUser;}

private:
    int nUser;
    std::map<std::string, UserData*> userIdMap;
};

#endif 