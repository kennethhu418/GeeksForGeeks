//  Given a current absolute path, e.g., "/usr/bin/mail", and a relative one, e.g, "../../../etc/xyz/../abc" return the absolute path 
//  created from the combination of the first two paths.In the example strings, the answer should be "/etc/abc".
//
//  http://www.careercup.com/question?id=6209523802963968

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string generateAbsolutePath(const string &absPath, const string &relPath)
    {
        int n = relPath.size(); if (n == 0) return absPath;

        Initialize(absPath);
        ParsePath(relPath);

        n = pathStack.size(); string result;
        for (int i = 0; i < n; ++i){
            result += '/';
            result += pathStack[i];
        }
        return result;
    }

private:
    vector<string> pathStack;

    int getNextSlash(const string &str, int start){
        while (start < str.size() && str[start] != '/') ++start;
        return start;
    }

    void ParsePath(const string &pathStr){
        int n = pathStr.size(); if (n == 0) return;
        int curCombStart = 0, curCombEnd = 1;
        string curComb;
        while (curCombStart < n){
            curCombEnd = getNextSlash(pathStr, curCombStart);
            curComb = pathStr.substr(curCombStart, curCombEnd - curCombStart);
            if (curComb == ".."){
                if (!pathStack.empty()) pathStack.pop_back();
            }
            else if (curComb.size() && curComb != ".")
                pathStack.push_back(curComb);
            curCombStart = curCombEnd + 1;
        }
    }

    void Initialize(const string &absPath){
        pathStack.clear();
        ParsePath(absPath);
    }
};

int main()
{
    string absPath, relPath, result;
    Solution so;

    //  Try the following inputs on the console:
    //  / usr / bin / mail      .. / .. / .. / etc / xyz / .. / abc
    //  / c / usrs / huz3 / .. / Kenneth / job_hunting / facebook / process / .. / offer / payment     details / .. / .. / .. / .. / amazon / offer / payment

    while (cin >> absPath >> relPath){
        result = so.generateAbsolutePath(absPath, relPath);
        cout << "The parsed path of " << absPath.c_str() << " and " << relPath.c_str() << " is " << result.c_str() << endl;
    }
    return 0;
}