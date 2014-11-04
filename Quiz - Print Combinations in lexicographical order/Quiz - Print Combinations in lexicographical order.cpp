//  Write a code to print all possible combinations(order matters) of characters of string in lexicographical order.
//  Input: ¡°ABC¡±
//  Output : A, AB, ABC, AC, ACB, B, BA, BAC, BC, BCA, C, CA, CAB, CB, CBA

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX_CHAR_COUNT 26

class Solution
{
private:
    int countArr[MAX_CHAR_COUNT];

    int getNext(int start) {
        while (start < MAX_CHAR_COUNT && countArr[start] == 0) ++start;
        return start;
    }
    
    void print(string &result) {
        int curPos = getNext(0);
        while (curPos < MAX_CHAR_COUNT) {
            --countArr[curPos];
            result += ('A' + curPos);
            cout << result << endl;
            print(result);
            result.pop_back();
            ++countArr[curPos];
            curPos = getNext(1 + curPos);
        }
    }

public:
    void printStringCombinations(const string &str) {
        int n = str.size(); if (n == 0) return;
        memset(countArr, 0, sizeof(countArr));
        for (int i = 0; i < n; ++i)
            ++countArr[str[i] - 'A'];
        string result;
        print(result);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string str;
    Solution so;

    while (cin >> str) {
        cout << "Result ->" << endl;
        so.printStringCombinations(str);
        cout << "------------------------------------" << endl;
    }

	return 0;
}

