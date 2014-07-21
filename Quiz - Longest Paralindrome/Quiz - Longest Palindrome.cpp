// Quiz - Longest Paralindrome.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

/****************************************************************************
 * This is an implementation of the Manacher’s algorithm
 * http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 ****************************************************************************/

class Solution
{
public:
    string longestPalindrome(string str)
    {
        generateExtendedStringAndAllocMem(str);

        int curCenter = 0;
        int curPos = 0, endPos = 0, mirrorPos = 0;
        resultLen[0] = 0;
        int n = extendedString.size();

        while (curCenter < n )
        {
            if (resultLen[curCenter] == 0)
            {
                if (curCenter == n - 1) break;
                resultLen[curCenter + 1] = getMirrorLen(curCenter + 1);
                curCenter++;
                continue;
            }

            curPos = curCenter + 1;
            endPos = curCenter + resultLen[curCenter];
            while (curPos <= endPos)
            {
                mirrorPos = 2 * curCenter - curPos;
                if (resultLen[mirrorPos] + curPos >= endPos)
                {
                    resultLen[curPos] = endPos - curPos - 1;
                    mirrorPos = 2 * curPos - endPos;
                    while (mirrorPos >= 0 && endPos < n && extendedString[mirrorPos] == extendedString[endPos])
                    {
                        mirrorPos--; endPos++; resultLen[curPos]++;
                    }
                    break;
                }

                resultLen[curPos++] = resultLen[mirrorPos];
            }

            curCenter = curPos;
        }

        int maxPos = getMaxPos();
        curPos = maxPos - resultLen[maxPos] + 1;
        string result = str.substr((curPos - 1) >> 1, resultLen[maxPos]);
        FreeMemory();
        return result;
    }

private:
    int *resultLen;
    string extendedString;
    const char FLAG_CHAR = '~';

    void generateExtendedStringAndAllocMem(const string &str)
    {
        int n = str.size();
        for (int i = 0; i < n; i++)
        {
            extendedString += FLAG_CHAR;
            extendedString += str[i];
        }
        extendedString += FLAG_CHAR;
        resultLen = new int[extendedString.size()];
    }

    void FreeMemory()
    {
        delete[] resultLen;
        extendedString.clear();
    }

    int getMirrorLen(int centerPos)
    {
        int n = extendedString.size();
        int start = centerPos - 1, end = centerPos + 1, len = 0;
        while (start >= 0 && end < n  && extendedString[start] == extendedString[end])
        {
            --start; ++end; ++len;
        }
        return len;
    }

    inline int getMaxPos()
    {
        int maxPos = 0, maxVal = resultLen[0], n = extendedString.size();
        for (int i = 1; i < n; i++)
        {
            if (resultLen[i] > maxVal)
            {
                maxPos = i;
                maxVal = resultLen[i];
            }
        }

        return maxPos;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    string input = "kmabccbaebabbabababababq";
    Solution so;
    cout << so.longestPalindrome(input) << endl;

    system("PAUSE");
	return 0;
}

