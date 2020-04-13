#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;

////////////////////////////////////////////////////////////////////////
////////////////                 utils                  ////////////////
////////////////////////////////////////////////////////////////////////

void split(const string& s, vector<string>& sv, const char* delim = " ") {
    sv.clear();                                
    char* buffer = new char[s.size() + 1];      
    buffer[s.size()] = '\0';
    copy(s.begin(), s.end(), buffer);    
    char* p = strtok(buffer, delim);      
    do {
        sv.push_back(p);                        
    } while ((p = strtok(NULL, delim)));   
    delete[] buffer;
    return;
}

////////////////////////////////////////////////////////////////////////
////////////////                 GCD                    ////////////////
////////////////////////////////////////////////////////////////////////

template <class T>
class GCD
{
public:
    GCD(){}
    GCD(T& i1, T& i2): num1(i1), num2(i2) {}
    ~GCD(){}

    void Def(T& iterTime){
        gcd = 1;
        T minVal = num1<num2 ? num1:num2;
        for(iterTime=2; iterTime<=minVal; iterTime++){
            if((num1%iterTime == 0) && (num2%iterTime == 0)){
                gcd = iterTime;
            }
        }
        iterTime = iterTime - 1;
        return;
    }

    void ReverseSearch(T& iterTime){
        gcd = 1;
        T minVal = num1<num2 ? num1:num2;
        for(iterTime=minVal; iterTime>=1; iterTime--){
            if((num1%iterTime == 0) && (num2%iterTime == 0)){
                gcd = iterTime;
                break;
            }
        }
        iterTime = minVal - iterTime;
        return;
    }

    void Binary(T& iterTime){
        T m = num2<=num1 ? num1:num2;
        T n = num1<num2 ? num1:num2;
        iterTime = 0;
        gcd = 1;

        while ((m != 0) && (n != 0)){
            if ((m%2 == 0) && (n%2 == 0)){
                gcd = gcd*2;
                m = m/2;
                n = n/2;
            } else if ((m%2 != 0) && (n%2 == 0)){
                n = n/2;
            } else if ((m%2 == 0) && (n%2 != 0)){
                m = m/2;
            }
            if (m<n){
                swap(m,n);
            }
            m = m-n; 
            iterTime++;
        }
        gcd = n*gcd;
        return;
    }
    
    void Euclid(T& iterTime){
        T m = num2<=num1 ? num1:num2;
        T n = num1<num2 ? num1:num2;
        T tmp;
        iterTime = 0;

        while ((m != 0) && (n != 0)){
            tmp = n;
            n = m%n; 
            m = tmp;
            iterTime++;
        }
        gcd = m;
        return;
    }

    void Reset(T& i1, T& i2){
        num1 = i1;
        num2 = i2;
        gcd = 1;
    }

    void Print(T& iterTime, string& method){
        cout << "Case(" << num1 << ", " << num2 << "): "<< 
        method << " = " << gcd << 
        ", taking " << iterTime << " iterations" << endl;
        return;
    }

    void PrintLog(){
        T iterTime;
        Def(iterTime);
        Print(iterTime, DefStr);
        ReverseSearch(iterTime);
        Print(iterTime, ReverseSearchStr);
        Binary(iterTime);
        Print(iterTime, BinaryStr);
        Euclid(iterTime);
        Print(iterTime, EuclidStr);

        return;
    }

    void PrintTest(){
        T iterTime;
        Binary(iterTime);
        cout << num1 << ","<< 
        num2 << "," << iterTime << endl;
    }

    void PrintCsv(){
        T iterTime;
        Def(iterTime);
        cout << num2 << ","<< 
        iterTime << "," << DefStr << endl;
        ReverseSearch(iterTime);
        cout << num2 << ","<< 
        iterTime << "," << ReverseSearchStr << endl;
        Binary(iterTime);
        cout << num2 << ","<< 
        iterTime << "," << BinaryStr << endl;
        Euclid(iterTime);
        cout << num2 << ","<< 
        iterTime << "," << EuclidStr << endl;

        return;
    }
    
private:
    string DefStr = "GCD-By-Def";
    string ReverseSearchStr = "GCD-By-Reverse-Search";
    string BinaryStr = "GCD-By-Binary";
    string EuclidStr = "GCD-By-Euclid";
    T num1;
    T num2;
    T gcd;
};

////////////////////////////////////////////////////////////////////////
////////////////                 main                   ////////////////
////////////////////////////////////////////////////////////////////////

int main(){
    string inputRowS;
    vector<string> inputRowSplit(2);
    vector<unsigned> inputRowI;
    unsigned rowNum=0;
    while(cin) {
        getline(cin, inputRowS);
        split(inputRowS, inputRowSplit);
        for(int i=0; i<inputRowSplit.size(); i++){
            inputRowI.push_back(stoi(inputRowSplit[i]));
        }
        if (inputRowI[2*rowNum] == 0){
            inputRowI.pop_back();
            break;
        }     
        rowNum++;
    }

    assert(inputRowI.size()%2 == 0);

    GCD<unsigned> gcd;
    for(int i=0; i<inputRowI.size(); i+=2){
        gcd.Reset(inputRowI[i], inputRowI[i+1]);
        gcd.PrintLog();
        //gcd.PrintTest();
    }

    return 0;
};