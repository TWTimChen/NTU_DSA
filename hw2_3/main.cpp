#include "cmdParser.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, char** argv)
{   
    CmdParser cmdParser;
    string inputLine;
    vector<string> inputLineSplit;
    while(getline(cin, inputLine)){
        if(inputLine == "") break;
        split(inputLine, inputLineSplit, ' ');
        if(inputLineSplit[0]=="") break;
        cmdParser.readCmd(inputLineSplit);
    }

    cmdParser.setProdField();

    ifstream inputFile;
    inputFile.open(argv[1]);

    //int testLine = 1e3;
    //int lineCount = 0;
    while(getline(inputFile, inputLine)){ 
	    split(inputLine, inputLineSplit, '\t');
        cmdParser.readLine(inputLineSplit);
        //lineCount++;
        //if(lineCount > testLine) break;
    }
    
    cmdParser.makeProfit();
    cmdParser.sortProdUser();

    while(!cmdParser.empty()){
        cmdParser.execCmd();
    }
    
    return 0;
}
