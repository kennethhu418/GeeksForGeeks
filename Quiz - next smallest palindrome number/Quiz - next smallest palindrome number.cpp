// Quiz - next smallest palindrome number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution
{
public:
    int getNextPalindromeNumber(int num)
    {
        if (num < 9)
            return num + 1;

        if (allNineDigits(num))
            return num + 2;

        int digitCount = getDigitCount(num);
        int halfPos = digitCount / 2;
        int halfNum = getHalfNum(num, halfPos);

        int mirrorNum = calcMirrorNum(halfNum, !(digitCount & 1));
        if (mirrorNum > num)
            return mirrorNum;

        return calcMirrorNum(halfNum + 1, !(digitCount & 1));
    }

private:
    inline bool allNineDigits(int num)
    {
        if (num < 9)    return false;
        if (num == 9)   return true;

        int r;
        while (num)
        {
            r = num % 10;
            if (r != 9)
                return false;
            num /= 10;
        }

        return true;
    }

    inline int getDigitCount(int num)
    {
        if (num < 10)
            return 1;

        int count = 0;
        while (num)
        {
            count++;
            num /= 10;
        }
        return count;
    }

    inline int getHalfNum(int num, int lowerCount)
    {
        int divisor = 1;
        while (lowerCount)
        {
            divisor *= 10;
            lowerCount--;
        }
        return num / divisor;
    }

    int calcMirrorNum(int num, bool mirrorLastDigit)
    {
        int digitCount = getDigitCount(num);
        int orgNum = num;
        int lowerHalf = 0, r = 0;

        if (!mirrorLastDigit)
        {
            num /= 10;
            --digitCount;
        }

        while (num)
        {
            r = num % 10;
            lowerHalf = lowerHalf * 10 + r;
            num /= 10;
        }

        int mulVal = 1;
        while (digitCount)
        {
            mulVal *= 10;
            digitCount--;
        }

        return mulVal * orgNum + lowerHalf;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int num = 99999;

    using namespace std;

    Solution so;
    cout << so.getNextPalindromeNumber(num) << endl;
	return 0;
}

