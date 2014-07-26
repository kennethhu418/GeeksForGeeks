// CountNumberOfTwos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

class Solution
{
public:

    //calculate how many 2 there are for the numbers below n in decimal representation
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

    //calculate how many 1 there are for the numbers below n in binary representation
    unsigned int getNumberOfOnes(unsigned int n)
    {
        unsigned int low_bitmask = 0, shift_count_for_high_bit = 1;
        unsigned int total = 0, high = 0, low = 0;

        while (n & (~low_bitmask))
        {
            high = (n >> shift_count_for_high_bit);
            low = n & low_bitmask;

            total += high * (low_bitmask + 1);
            if (n & (1 + low_bitmask))  total += (low + 1);

            ++shift_count_for_high_bit;
            low_bitmask = (low_bitmask << 1) | 1;
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

    unsigned int getNumberOfOnes(unsigned int n)
    {
        unsigned int total = 0;
        while (n-- > 0)
            total += getOnesNum(n + 1);
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

    unsigned int getOnesNum(unsigned int n)
    {
        if (n == 0) return 0;
        unsigned int total = 0;
        while (n)
        {
            if (n & 1) ++total;
            n = (n >> 1);
        }
        return total;
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

    cout << endl << "================================================" << endl;
    cout << "      Now begin testing getNumberOfTwos routine." << endl;
    while (times-- > 0)
    {
        n = rand() % (MAX_VAL + 1);
        standardAns = so2.getNumberOfTwos(n);
        myAns = so.getNumberOfTwos(n);
        if (myAns != standardAns)
            cout << "Inconsistent Ans for n = " << n << " standard: " << standardAns << " my: " << myAns << endl;
    }

    cout << endl<<"================================================" << endl;
    cout << "      Now begin testing getNumberOfOnes routine." << endl;

    times = TIMES;
    while (times-- > 0)
    {
        n = rand() % (MAX_VAL + 1);
        standardAns = so2.getNumberOfOnes(n);
        myAns = so.getNumberOfOnes(n);
        if (myAns != standardAns)
            cout << "Inconsistent Ans for n = " << n << " standard: " << standardAns << " my: " << myAns << endl;
    }

	return 0;
}

