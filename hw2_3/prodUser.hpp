#ifndef PROD_USER_H
#define PROD_USER_H

#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class ProdUser
{
public:
    ProdUser() {}
    ~ProdUser() {}

    void setProdField(const std::vector<std::string>& prodFieldVec);
    void insertProdUser(std::string& prodId,std::string& userId);
    void sortProdUser();
    void getIntersect(
        std::string& prod1, 
        std::string& prod2, 
        std::vector<std::string>& retUserId);
    void printItersect(std::string& prod1, std::string& prod2);

private:
    std::unordered_set<std::string> prodField;
    std::unordered_map<std::string, std::vector<std::string> > prodUser;
};

#endif