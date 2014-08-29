#include "stdafx.h"
#include <iostream>
using namespace std;

//Lucky numbers are subset of integers.Rather than going into much theory, let us see the process of arriving at lucky numbers,
//
//Take the set of integers
//1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, ¡­¡­
//
//First, delete every second number, we get following reduced set.
//1, 3, 5, 7, 9, 11, 13, 15, 17, 19, ¡­¡­¡­¡­
//
//Now, delete every third number, we get
//1, 3, 7, 9, 13, 15, 19, ¡­.¡­.
//
//Continue this process indefinitely¡­¡­
//Any number that does NOT get deleted due to above process is called ¡°lucky¡±.
//
//Therefore, set of lucky numbers is 1, 3, 7, 13, ¡­¡­¡­
//
//Now, given an integer ¡®n¡¯, write a function to say whether this number is lucky or not.



class Solution
{
public:
    bool isLuckyNumber(int n)
    {
        if (n == 1)	return true;

        int curPos = n - 1, curElimanateCounter = 2;
        while (curPos >= curElimanateCounter - 1)
        {
            if ((curPos + 1) % curElimanateCounter == 0)
                return false;

            curPos = (curPos / curElimanateCounter)*(curElimanateCounter - 1) + curPos % curElimanateCounter;
            ++curElimanateCounter;
        }

        return true;
    }
};

int main() {
    const int LUCKY_LIMIT = 10000;

    Solution so;
    for (int i = 1; i <= LUCKY_LIMIT; ++i)
    {
        if (so.isLuckyNumber(i))
            cout << i << ", ";
    }
    cout << endl;
    return 0;
}

