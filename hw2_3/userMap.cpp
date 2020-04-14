#include "userMap.hpp"

using namespace std;

extern const int 
SALE            = 0,
TIMESTAMP       = 3,
PROD_PRICE      = 5,
PROD_AGE_GOURP  = 6,
PROD_GENDER     = 9,
PROD_ID         = 19,
USER_ID         = 22;

void UserData::insertUserInfo(vector<string>& inputLineSplit){
    int timeInt = stoi(inputLineSplit[TIMESTAMP]);
    int saleInt = stoi(inputLineSplit[SALE]);
    
    ID_TIME id_time(
        inputLineSplit[PROD_ID], 
        timeInt);
    idTimeMap.insert(make_pair(id_time, nClick));
    saleByTime.insert(make_pair(
        timeInt,
        saleInt
    ));
    sale.push_back(saleInt);
    prodPrice.push_back(inputLineSplit[PROD_PRICE]);
    prodAgeGroup.push_back(inputLineSplit[PROD_AGE_GOURP]);
    prodGender.push_back(inputLineSplit[PROD_GENDER]);
    nClick++;
    return;
}

int UserData::getSaleByIdTime(std::string& id, int& time){
    ID_TIME id_time(id, time);
    assert(idTimeMap.find(id_time) != idTimeMap.end());
    int index = idTimeMap[id_time];
    return sale[index];
}

void UserData::printByIdTime(){
    int indices[nClick];
    int index;
    map<ID_TIME, int>::iterator iter;
    for(iter=idTimeMap.begin(); iter!=idTimeMap.end(); iter++){
        index = iter->second;
	if(sale[index] == 1){
            cout 
            << iter->first.first << " " 
            << iter->first.second << " "
            << prodPrice[index] << " "
            << prodAgeGroup[index] << " "
            << prodGender[index] 
            << endl;
	    }
    }
    return;
}

void UserData::makeProfit(){
    int cumSale = 0;
    float cCount = 1.;
    map<int, int>::reverse_iterator iter;
    for(iter=saleByTime.rbegin(); iter!=saleByTime.rend(); iter++){
        cumSale += iter->second;
        profitByTime.insert(make_pair(
            iter->first,
            cumSale/cCount
        ));
        cCount++;
    }
    saleByTime.clear();
    return;
}

float UserData::getProfit(const int& time){
    map<int, float>::iterator iter;
    iter = profitByTime.lower_bound(time);
    if(iter == profitByTime.end()){
        return 0;
    }else{
        return iter->second;
    }
}// need check for saleSum == 0


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

UserMap::~UserMap(){
    map<string, UserData*>::iterator iter;
    for(iter=userIdMap.begin(); iter!=userIdMap.end(); iter++)
        delete iter->second;
}

void UserMap::insertUser(vector<string>& inputLineSplit){
    string userId = inputLineSplit[USER_ID];
    if(userIdMap.find(userId) == userIdMap.end()){
        UserData* userData = new UserData;
        userData->insertUserInfo(inputLineSplit);
        userIdMap.insert(make_pair(userId, userData));
        nUser++;
    }else{
        userIdMap[userId]->insertUserInfo(inputLineSplit);
    }
}

void UserMap::printUserSale(string& userId, string& prodId, string& time){
    int timeInt = stoi(time);
    cout 
    << userIdMap[userId]->getSaleByIdTime(prodId, timeInt)
    << endl;
    return;
}

void UserMap::printUserInfo(string& userId){
    userIdMap[userId]->printByIdTime();
    return;
}

void UserMap::makeUserProfit(){
    map<string, UserData*>::iterator iter;
    for(iter=userIdMap.begin(); iter!=userIdMap.end(); iter++){
        iter->second->makeProfit();
    }
}

void UserMap::getUserProfit(const int& time, const float& theta, vector<string>& retUser){
    unsigned maxUser = 10;
    float profit;
    map<string, UserData*>::iterator iter;
    for(iter=userIdMap.begin(); iter!=userIdMap.end(); iter++){
        profit = iter->second->getProfit(time);
        if(profit>=theta) retUser.push_back(iter->first);
        if(retUser.size()>=10) break;
    }
}

void UserMap::printUserProfit(string& time, string& theta){
    const int timeInt = stoi(time);
    const float thetafloat = stof(theta);
    vector<string> retUser;
    getUserProfit(timeInt, thetafloat, retUser);
    for(int i=0; i<retUser.size(); i++)
        cout << retUser[i] << endl;
    return;
}
