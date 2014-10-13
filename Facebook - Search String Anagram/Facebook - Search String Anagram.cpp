/***************************************************************
    bool anaStrStr (string needle, string haystack)
    {
    }
    Write a function that takes 2 strings , search returns true if any anagram of 
    string1(needle) is present in string2(haystack)
 ***************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_COUNT 256

class Solution
{
public:
    vector<int> anaStrStr(string str, string ptr)
    {
        vector<int> resultArr;
        memset(usageArr, 0, sizeof(int)*MAX_COUNT);
        memset(dynamicArr, 0, sizeof(int)*MAX_COUNT);

        int n = str.size(), m = ptr.size();
        //Initialize usageArr
        for (int i = 0; i < m; ++i) ++usageArr[ptr[i]];

        //Search anagram
        int curPos = 0, len = 0, start = 0; char c = '\0';
        while (curPos < n) {
            c = str[curPos];
            if (usageArr[c] == 0) {
                ++curPos; len = 0;
                memset(dynamicArr, 0, sizeof(int)*MAX_COUNT);
                continue;
            }
            ++dynamicArr[c];
            if (dynamicArr[c] <= usageArr[c]) {
                ++len;
                if (len == m){
                    resultArr.push_back(curPos - len + 1);
                    --dynamicArr[str[curPos - len + 1]]; --len;
                }
            }
            else {
                start = removeUntilTarget(str, curPos - len, c);
                len = curPos - start;
            }
            ++curPos;
        }
        return resultArr;
    }

private:
    int usageArr[MAX_COUNT];
    int dynamicArr[MAX_COUNT];

    int removeUntilTarget(const string &str, int start, char target) {
        int n = str.size(); char c = '\0';
        while (start < n) {
            c = str[start];
            --dynamicArr[c];
            if (c == target) return start;
            ++start;
        }
        return -1;
    }
};


//try input iamattackiaattcckaa;    cattack
int main()
{
    string str, ptr;
    int m = 0;
    vector<int> resultArr;
    Solution so;

    while (cin >> str >> ptr){
        resultArr = so.anaStrStr(str, ptr);
        m = ptr.size();
        for (int i = 0; i < resultArr.size(); ++i)
            cout << str.substr(resultArr[i], m) << endl;
        cout << "======================================" << endl;
    }
    return 0;
}