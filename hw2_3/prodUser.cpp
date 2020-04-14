#include "prodUser.hpp"

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

void ProdUser::setProdField(const vector<string>& prodFieldVec){
    //prodField.insert(prodFieldVec[0]);
    //unordered_set<string>::iterator iter;
    for(int i=0; i<prodFieldVec.size(); i++){
        if(prodField.find(prodFieldVec[i]) == prodField.end()){
            prodField.insert(prodFieldVec[i]);
        }
    }
    return;
}

void ProdUser::insertProdUser(string& prodId, string& userId){
    if(prodField.find(prodId) != prodField.end()){
        if(prodUser.find(prodId) == prodUser.end()){
            vector<string> userIdVec;
            prodUser.insert(make_pair(prodId, userIdVec));
            prodUser[prodId].push_back(userId);
        }else{
            prodUser[prodId].push_back(userId);
        }
    }
    return;
}

void ProdUser::sortProdUser(){
    unordered_map<string, vector<string> >::iterator iter;
    for (iter = prodUser.begin(); iter != prodUser.end(); iter++){
        sort(iter->second.begin(), iter->second.end());
	iter->second.erase(
	    unique(iter->second.begin(), iter->second.end()),
	    iter->second.end()
	);
    }
}

void ProdUser::getIntersect(string& prod1, string& prod2, vector<string>& retUser){
    assert(prodUser.find(prod1) != prodUser.end());
    assert(prodUser.find(prod2) != prodUser.end());
	
    retUser.resize(prodUser[prod1].size());
    if(prod1 == prod2){
	    retUser = prodUser[prod1];
    }else{
	vector<string>::iterator iter;
    	iter = set_intersection(
       	    prodUser[prod1].begin(),
	        prodUser[prod1].end(),
	        prodUser[prod2].begin(),
	        prodUser[prod2].end(),
	        retUser.begin()
        );
    	retUser.resize(iter-retUser.begin());
    }

    return;
}

void ProdUser::printItersect(string& prod1, string& prod2){
    vector<string> retUser;
    getIntersect(prod1, prod2, retUser);
    for(int i=0; i<retUser.size(); i++){
        cout 
        << retUser[i] 
        << endl;
    }
}
