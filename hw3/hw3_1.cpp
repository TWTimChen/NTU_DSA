#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cassert>

using namespace std;

typedef pair<string, int> PRECEDENCE;

const int 
NUMBER = -1,
PEREN_L = 0,
PEREN_R = 1,
TIER_2 = 2,
TIER_3 = 3,
TIER_4 = 4,
TIER_5 = 5,
TIER_6 = 6,
TIER_7 = 7,
TIER_8 = 8,
TIER_9 = 9,
TIER_10 = 10,
TIER_11 = 11,
DUMMY = 1000;

bool isNumber(const char c){
    for(int i=0; i<10; i++)
        if((c-'0')==i) return true;
    return false;
}

void parseArthExp(string& inputLine, vector<PRECEDENCE>& parsedLine){
    int ptr=0;
    while(ptr<inputLine.size()){
        int numPos=ptr;
        while (isNumber(inputLine[numPos]))
            numPos++;
        int numLen = numPos-ptr;
        if(numLen)
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, numLen), NUMBER));
        ptr = numPos;
        
        if(ptr==inputLine.size()){
            break;
        }else if(inputLine[ptr]=='('){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1), PEREN_L));
        }else if(inputLine[ptr]==')'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1), PEREN_R));
        }else if(inputLine[ptr]=='+'){
            if(ptr==0){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2)); // unary +
            }else if(isNumber(inputLine[ptr-1]) || inputLine[ptr-1]==')'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_4)); // binary +
            }else{
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2)); // unary +
            }
        }else if(inputLine[ptr]=='-'){
            if(ptr==0){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2)); // unary -
            }else if(isNumber(inputLine[ptr-1]) || inputLine[ptr-1]==')'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_4)); // binary -
            }else{
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2)); // unary -
            }
        }else if(inputLine[ptr]=='!'){
            if(inputLine[ptr+1]=='='){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_6));
                ptr += 1;
            }else{
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2));
            }
        }else if(inputLine[ptr]=='~'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_2));
        }else if(inputLine[ptr]=='*'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_3));
        }else if(inputLine[ptr]=='/'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_3));
        }else if(inputLine[ptr]=='%'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_3));
        }else if(inputLine[ptr]=='<'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 2) ,TIER_5));
            ptr += 1;
        }else if(inputLine[ptr]=='>'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 2) ,TIER_5));
            ptr += 1;
        }else if(inputLine[ptr]=='='){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 2) ,TIER_6));
            ptr += 1;
        }else if(inputLine[ptr]=='&'){
            if(inputLine[ptr+1]=='&'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 2) ,TIER_10));
                ptr += 1;
            }else{
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_7));
            }
        }else if(inputLine[ptr]=='^'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_8));
        }else if(inputLine[ptr]=='|'){
            if(inputLine[ptr+1]=='|'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 2) ,TIER_11));
                ptr += 1;
            }else{
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_9));
            }
        }else{
            cout << "Unexpected Operater: " << inputLine[ptr] << endl;
            cout << "At " << ptr << " position" << endl;
            break;
        }
        
        ptr+=1;
    }

    return;
}

void transPreToPost(int& idx, vector<PRECEDENCE>& inputLine, vector<PRECEDENCE>& parsedLine){
    stack<PRECEDENCE> operStack;
    operStack.push(PRECEDENCE("", DUMMY)); 

    for(idx; idx<inputLine.size(); idx++){
        if(inputLine[idx].second == PEREN_L){
            cout << "A left Perentheses is at " << idx << endl;
            idx += 1;
            transPreToPost(idx, inputLine, parsedLine);
        }
        
        if(inputLine[idx].second == PEREN_R){
            cout << "A right Perentheses is at " << idx << endl;
            idx += 1;
            while(operStack.top().second != DUMMY){
                parsedLine.push_back(operStack.top());
                cout << "Pop an operator  " << operStack.top().first << endl;
                operStack.pop();
            }
            return;
        }
        
        if(idx >= inputLine.size()){
            break;
        }else if(inputLine[idx].second == NUMBER){
            parsedLine.push_back(inputLine[idx]);
            //cout << "Push a number: " << inputLine[idx].first << endl;
        }else if(inputLine[idx].second == TIER_2){
            operStack.push(inputLine[idx]);
            cout << "Push a unary operator " << inputLine[idx].first << endl;
        }else{
            while(operStack.top().second <= inputLine[idx].second){
                parsedLine.push_back(operStack.top());
                operStack.pop();
            }
            operStack.push(inputLine[idx]);
            cout << "Push a binary operator " << inputLine[idx].first << endl;
        }
    }
    //cout << "End index: " << idx << endl;
    while(operStack.top().second != DUMMY){
        parsedLine.push_back(operStack.top());
        cout << "Pop an operator  " << operStack.top().first << endl;
        operStack.pop();
    }
    return;
}

int binaryOper(string& oper, int& int1, int& int2){
    if(oper == "*"){
        return int1*int2;
    }else if(oper == "/"){
        return int1/int2;
    }else if(oper == "%"){
        return int1%int2;
    }else if(oper == "+"){
        return int1+int2;
    }else if(oper == "-"){
        return int1-int2;
    }else if(oper == "<<"){
        return int1<<int2;
    }else if(oper == ">>"){
        return int1>>int2;
    }else if(oper == "=="){
        return int1==int2;
    }else if(oper == "!="){
        return int1!=int2;
    }else if(oper == "&"){
        return int1&int2;
    }else if(oper == "^"){
        return int1^int2;
    }else if(oper == "|"){
        return int1|int2;
    }else if(oper == "&&"){
        return int1&&int2;
    }else if(oper == "||"){
        return int1||int2;
    }else{
        cout << "Unrecognized operator: " << oper << endl;
    }
    return 0;
}

int unaryOper(string oper, int int1){
    if(oper == "+"){
        return +int1;
    }else if(oper == "-"){
        return -int1;
    }else if(oper == "!"){
        return !int1;
    }else if(oper == "~"){
        return ~int1;
    }
    return 0;
}

int calcPostfix(vector<PRECEDENCE>& postExp){
    int retVal;
    stack<int> intStack;

    for(int i=0; i<postExp.size(); i++){
        if(postExp[i].second == NUMBER){
            intStack.push(stoi(postExp[i].first));
        }else if(postExp[i].second == TIER_2){
            int int1 = intStack.top();
            intStack.pop();
            intStack.push(unaryOper(postExp[i].first, int1));
        }else{
            int int2 = intStack.top();
            intStack.pop();
            int int1 = intStack.top();
            intStack.pop();
            intStack.push(binaryOper(postExp[i].first, int1, int2));
        }
    }

    assert(intStack.size()==1);
    retVal = intStack.top();

    return retVal;
}

int main(){
    string rawArthExp;
    vector<PRECEDENCE> preExp;
    vector<PRECEDENCE> postExp;
    int idx = 0;
    int retVal;
    while(getline(cin, rawArthExp)){
        if(rawArthExp.size()==0) break;
        
        parseArthExp(rawArthExp, preExp);
        cout << endl << "Stack operations: " << endl;
        
        transPreToPost(idx, preExp, postExp);
        cout << endl << "Postfix expression: " << endl;
        for(int i=0; i<postExp.size(); i++){
            cout << postExp[i].first << " ";
        }
        cout << endl;

        retVal = calcPostfix(postExp);
        cout << endl << "RESULT: " << retVal << endl;
        
        rawArthExp.clear();
        preExp.clear();
        postExp.clear();
        idx = 0;
    }
    return 0;
}