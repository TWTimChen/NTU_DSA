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
////////////////                BigInt                  ////////////////
////////////////////////////////////////////////////////////////////////

class BigInt
{
public:
    BigInt(){}
    BigInt(const string& bigStr){ parseStr(bigStr); }
    BigInt(const BigInt& bigInt){ 
        digit = bigInt.digit; 
        intArray = new int[256];
        for(int i=0; i<digit; i++){
            intArray[i] = bigInt.intArray[i];
        }
    }
    ~BigInt(){} //if(intArray) delete[] intArray;
// to-dos set digit
    void parseStr(const string& bigStr){
        digit = bigStr.size();
        intArray = new int[256];
        for(int i=0; i<digit; i++){
            intArray[i] = bigStr[digit-(i+1)] - '0';
        }
        checkDigit();
        return;
    }

    void checkDigit(){
        assert(digit >= 0);
        for(int i=digit-1; i>=0; i--){
            if(intArray[i]==0){
                digit -= 1;
            }else return;
        }
    }

    void print(){
        for(int i=digit-1; i>=0; i--){
            cout << intArray[i];
        }
        cout << endl;
    }

    bool isZero(){
        return(digit == 0);
    }

    bool isEven(){
        return (intArray[0]%2 == 0);
    }

    bool isBigger(const BigInt& num){
        if(digit > num.digit){
            return true;
        }else if (digit == num.digit){
            for(int i=digit-1; i>=0; i--){
                if(intArray[i]>num.intArray[i]) return true;
                else if (intArray[i]<num.intArray[i]) return false;
            }
        }else return false;
        
    }

    BigInt& operator-(BigInt& num){
        assert(digit>=num.digit);
        for(int i=0; i<digit; i++){
            if(intArray[i]>=num.intArray[i]){
                intArray[i] -= num.intArray[i];
            }else{
                intArray[i+1] -= 1;
                intArray[i] += 10;
                intArray[i] -= num.intArray[i];
            }
        }
        checkDigit();
        return *this;
    }

    BigInt& divTwo(){
        for(int i=digit-1; i>=0; i--){
            if(intArray[i]%2 == 1){
                intArray[i-1] += 10;
            }
            intArray[i] /= 2;
        }
        checkDigit();
        return *this;
    }

    BigInt& multiTwo(){
        int carry = 0;
        for(int i=0; i<digit; i++){
            intArray[i] *= 2;
            if(carry > 0){
                intArray[i] += carry;
                intArray[i-1] -= carry*10;
            }
            carry = intArray[i]/10;
        }
        if(intArray[digit] > 0) digit += 1;

        return *this;
    }

private:
    int* intArray;
    int digit;

};

////////////////////////////////////////////////////////////////////////
////////////////                BigGCD                  ////////////////
////////////////////////////////////////////////////////////////////////

class BigGCD
{
public:    
    BigGCD(){}
    BigGCD(BigInt n1, BigInt n2): num1(n1), num2(n2){}

    void gcd(){
        BigInt m;
        BigInt n;
        if(num1.isBigger(num2)){
            m = num1;
            n = num2;
        }else{
            m = num2;
            n = num1;
        }
        unsigned twoCounter = 0;

        while(!m.isZero() && !n.isZero()){

            if (m.isEven() && n.isEven()){
                twoCounter++;
                m = m.divTwo();
                n = n.divTwo();
            } else if (!m.isEven() && n.isEven()){
                n = n.divTwo();
            } else if (m.isEven() && !n.isEven()){
                m = m.divTwo();
            }

            if (n.isBigger(m)){
                swap(m,n);
            }

            m = m-n; 
        }
        for(int i=0; i<twoCounter; i++) n.multiTwo();

        n.print();
        return;
    }

private:
    BigInt num1;
    BigInt num2;
};

////////////////////////////////////////////////////////////////////////
////////////////                  main                  ////////////////
////////////////////////////////////////////////////////////////////////

int main(){
    string inputRowS;
    vector<string> inputRowSplit(2);

    while(cin) {
        getline(cin, inputRowS);
        if(inputRowS.size() == 0) break;
        split(inputRowS, inputRowSplit);
    }

    assert(inputRowSplit.size() == 2);

    BigInt res;
    BigInt num1(inputRowSplit[0]);
    BigInt num2(inputRowSplit[1]);
    BigGCD biggcd(num1, num2);
    
    biggcd.gcd();

    return 0;
}

