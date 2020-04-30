#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cassert>
#include <math.h>

using namespace std;

typedef pair<string, int> PRECEDENCE;

const int 
NUMBER = -1,
PEREN_L = 0,
PEREN_L_BIN = 1,
PEREN_R = 2,
COMMA = 3,
TIER_2 = 4,
TIER_3 = 5,
TIER_4 = 6,

DUMMY = 1000;

bool isNumber(const char c){
    for(int i=0; i<10; i++)
        if((c-'0')==i) return true;
    if(c == '.') 
        return true;
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
        }else if(inputLine[ptr]=='l'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 4), PEREN_L));
            ptr += 3;
        }else if(inputLine[ptr]=='e'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 4), PEREN_L));
            ptr += 3;
        }else if(inputLine[ptr]=='p'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 4), PEREN_L));
            ptr += 3;
        }else if(inputLine[ptr]=='s'){
            if(inputLine[ptr+1]=='i'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 4), PEREN_L));
                ptr += 3;
            }else if(inputLine[ptr+1]=='q'){
                parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 5), PEREN_L));
                ptr += 4;
            }            
        }else if(inputLine[ptr]=='c'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 4), PEREN_L));
            ptr += 3;
        }else if(inputLine[ptr]=='f'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 5), PEREN_L));
            ptr += 4;
        }else if(inputLine[ptr]=='('){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1), PEREN_L));
        }else if(inputLine[ptr]==')'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1), PEREN_R));
        }else if(inputLine[ptr]==','){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1), COMMA));
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
        }else if(inputLine[ptr]=='*'){
            parsedLine.push_back(PRECEDENCE(inputLine.substr(ptr, 1) ,TIER_3));
        }else{
            cout << "Unexpected Operater: " << inputLine[ptr] << endl;
            cout << "At " << ptr << " position" << endl;
            break;
        }
        
        ptr+=1;
    }

    return;
}

static bool FLAG_COMMA = false;

void transPreToPost(int& idx, vector<PRECEDENCE>& inputLine, vector<PRECEDENCE>& parsedLine){
    stack<PRECEDENCE> operStack;
    operStack.push(PRECEDENCE("", DUMMY)); 
    //bool FLAG_COMMA = false;

    for(idx; idx<inputLine.size(); idx++){

        if(inputLine[idx].second == PEREN_L){
            cout << "A left Perentheses(function) is at " << idx << endl;
            int len = inputLine[idx].first.size();
            if(len > 1){
                inputLine[idx].first = inputLine[idx].first.substr(0, len-1);
                if(inputLine[idx].first == "pow"){
                    inputLine[idx].second = PEREN_L_BIN;
                }
                operStack.push(inputLine[idx]);
            }
            idx += 1;
            transPreToPost(idx, inputLine, parsedLine);
        }
        
        if(inputLine[idx].second == COMMA){
            if(!FLAG_COMMA){
                cout << "A comma is at " << idx << endl;
                while(operStack.top().second != DUMMY){
                    parsedLine.push_back(operStack.top());
                    cout << "Pop an operator  " << operStack.top().first << endl;
                    operStack.pop();
                }
                FLAG_COMMA = true;
                return;
            }else{
                idx += 1;
                FLAG_COMMA = false;
                transPreToPost(idx, inputLine, parsedLine);
            }
        }
        
        if(inputLine[idx].second == PEREN_R){
            cout << "A right Perentheses is at " << idx << endl;
            idx += 1;
            while(operStack.top().second != DUMMY){
                parsedLine.push_back(operStack.top());
                cout << "Pop an operator " << operStack.top().first << endl;
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
                cout << "Pop an operator " << operStack.top().first << endl;
                operStack.pop();
            }
            operStack.push(inputLine[idx]);
            cout << "Push a binary operator " << inputLine[idx].first << endl;
        }
    }
    //cout << "End index: " << idx << endl;
    while(operStack.top().second != DUMMY){
        parsedLine.push_back(operStack.top());
        cout << "Pop an operator " << operStack.top().first << endl;
        operStack.pop();
    }
    return;
}

double binaryOper(string& oper, double& double1, double& double2){
    if(oper == "*"){
        return double1*double2;
    }else if(oper == "/"){
        return double1/double2;
    }else if(oper == "+"){
        return double1+double2;
    }else if(oper == "-"){
        return double1-double2;
    }else if(oper == "pow"){
        return pow(double1,double2);
    }else{
        cout << "Unrecognized operator: " << oper << endl;
    }
    return 0;
}

double unaryOper(string oper, double& double1){
    if(oper == "+"){
        return +double1;
    }else if(oper == "-"){
        return -double1;
    }else if(oper == "log"){
        return log(double1);
    }else if(oper == "exp"){
        return exp(double1);
    }else if(oper == "sin"){
        return sin(double1);
    }else if(oper == "cos"){
        return cos(double1);
    }else if(oper == "fabs"){
        return fabs(double1);
    }else if(oper == "sqrt"){
        return sqrt(double1);
    }
    return 0;
}

double calcPostfix(vector<PRECEDENCE>& postExp){
    double retVal;
    stack<double> doubleStack;

    for(int i=0; i<postExp.size(); i++){
        //cout << "Doing..." << postExp[i].first << endl;
        if(postExp[i].second == NUMBER){
            doubleStack.push(stof(postExp[i].first));
        }else if(postExp[i].second == TIER_2 || postExp[i].second == PEREN_L){
            double double1 = doubleStack.top();
            doubleStack.pop();
            doubleStack.push(unaryOper(postExp[i].first, double1));
        }else{
            double double2 = doubleStack.top();
            doubleStack.pop();
            double double1 = doubleStack.top();
            doubleStack.pop();
            doubleStack.push(binaryOper(postExp[i].first, double1, double2));
        }
    }

    assert(doubleStack.size()==1);
    retVal = doubleStack.top();

    return retVal;
}

int main(){
    string rawArthExp;
    vector<PRECEDENCE> preExp;
    vector<PRECEDENCE> postExp;
    int idx = 0;
    double retVal;

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
        cout << fixed;
        cout << endl << "RESULT: " << retVal << setprecision(6) << endl;
        
        rawArthExp.clear();
        preExp.clear();
        postExp.clear();
        idx = 0;
    }
    return 0;
}