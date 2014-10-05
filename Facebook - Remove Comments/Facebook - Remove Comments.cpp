
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
#include <fstream>
using namespace std;

static ifstream  fin;

bool getNextLine(string &line){
    if (fin.eof()) return false;
    static char buffer[1000];
    fin.getline(buffer, 1000);
    line = buffer;
}

void printNonComment(){
    string curLine, newLine;
    int n = 0, curPos = 0;
    bool startOfComment = false;
    bool startOfString = false;
    while (getNextLine(curLine)){
        n = curLine.size(); curPos = 0;
        newLine.clear();
        if (n == 0){
            cout << "" << endl;
            continue;
        }

        while (curPos < n){
            if (startOfComment){
                if (curPos < n - 1 && curLine[curPos] == '*' && curLine[curPos + 1] == '/'){
                    curPos += 2;
                    startOfComment = false;
                }
                else
                    ++curPos;
            }
            else {
                if (startOfString){
                    newLine += curLine[curPos];
                    if (curLine[curPos] == '"' && ((curPos == 0) || (curLine[curPos - 1] != '\\')))
                        startOfString = false;
                    ++curPos; continue;
                }
                if (curLine[curPos] == '"'){
                    newLine += curLine[curPos++];
                    startOfString = true; continue;
                }

                if (curPos < n - 1 && curLine[curPos] == '/' && curLine[curPos + 1] == '*'){
                    curPos += 2;
                    startOfComment = true;
                }
                else if (curPos < n - 1 && curLine[curPos] == '/' && curLine[curPos + 1] == '/')
                    break;
                else
                    newLine += curLine[curPos++];
            }
        }

        if (newLine.size()) cout << newLine.c_str() << endl;
    }
}

int main() {
    fin.open("D:\\test.cpp");
    if (fin.bad()){
        cout << "Invalid file: " << endl;
        return 0;
    }

    printNonComment();

    fin.close();
    return 0;
}