// CountNumberOfTwos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

class Solution
{
public:
    unsigned int getNumberOfTwos(unsigned int n)
    {
        if (n < 2)  return 0;
        if (n < 12) return 1;

        unsigned int base = 1, curNum = n, high = 0, low = 0, total = 0, curDigit = 0;
        while (curNum)
        {
            high = curNum / 10;
            low = n % base;
            curDigit = curNum % 10;

            //For high is 0 - (high - 1)
            total += high* base;

            //For high is high
            if (curDigit == 2)
                total += (low + 1);
            else if (curDigit > 2)
                total += base;

            //Move on
            curNum /= 10;
            base *= 10;
        }

        return total;
    }
};

class Solution_BruteForce
{
public:
    unsigned int getNumberOfTwos(int n)
    {
        unsigned int total = 0;
        while (n > 0)
            total += getTwosNum(n--);
        return total;
    }

private:
    unsigned int getTwosNum(unsigned int n)
    {
        if (n < 2) return 0;
        unsigned int r = 0;
        unsigned int count = 0;
        while (n)
        {
            r = n % 10;
            if (r == 2) ++count;
            n /= 10;
        }
        return count;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    const unsigned int TIMES = 1000;
    const unsigned int MAX_VAL = 5000;
    unsigned int n = 0, times = TIMES;
    unsigned int standardAns = 0, myAns = 0;
    Solution so;
    Solution_BruteForce so2;

    srand(time(0));

    while (times-- > 0)
    {
        n = rand() % (MAX_VAL + 1);
        standardAns = so2.getNumberOfTwos(n);
        myAns = so.getNumberOfTwos(n);
        if (myAns != standardAns)
            cout << "Inconsistent Ans for n = " << n << " standard: " << standardAns << " my: " << myAns << endl;
    }

	return 0;
}

