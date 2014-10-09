
//  Implement a method called printNonComments() which prints out a extract 
//  of text with comments removed.
//  
//  For example, the input :
//  
//  hello /* this is a
//        multi line comment */ all
//  
//        Should produce :
//  
//  hello
//  all
//  
//  You have access to a method called getNextLine() which returns the next line in the input string
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

static ifstream fin;

/*********************************************************************************************
* This is a removeing comments codes authored by Zhipeng Hu
*********************************************************************************************/

// get next line in the istream
bool getNextLine(string &str){
    if (fin.eof()) return false;
    static char buffer[1000];
    fin.getline(buffer, 1000);
    str = buffer;
    return true;
}

void removeComments(){
    string str; /* used to get line string
                */
    int n = 0, curPos = 0;
    bool startOfComment = false, startOfString = false; //initialized with false 
    while (getNextLine(str)){
        n = str.size(); curPos = 0;
        while (curPos < n){
            if (startOfComment){
                if (str[curPos] == '*' && curPos < n - 1 && str[curPos + 1] == '/'){
                    curPos += 2; startOfComment = false;
                }
                else
                    curPos++;
            }
            else if (startOfString) {
                cout << str[curPos];
                if (str[curPos] == '"' && (curPos == 0 || str[curPos - 1] != '\\'))
                    startOfString = false;
                ++curPos;
            }
            else {
                if (str[curPos] == '/' && curPos < n - 1 && str[curPos + 1] == '/') break;
                if (str[curPos] == '/' && curPos < n - 1 && str[curPos + 1] == '*') {
                    startOfComment = true; curPos += 2; continue;
                }
                cout << str[curPos];
                if (str[curPos] == '"' && (curPos == 0 || str[curPos - 1] != '\'')) // it may be '"', which should not be start of string
                    startOfString = true;
                ++curPos;
            }
        }
        cout << endl;
    }

    cout << "All //comments /*removed*/ in the \
                         \"std::istream\"" << endl;
}

int main()
{
    fin.open("C:\\test.cpp");
    removeComments();
    fin.close();
    return 0;
}