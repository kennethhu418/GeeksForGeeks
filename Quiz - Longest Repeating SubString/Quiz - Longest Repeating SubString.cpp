// Quiz - Longest Repeating SubString.cpp : 定义控制台应用程序的入口点。
//

/************************************************************************
  * Find the longest substring in the given string which occurs more than once.
************************************************************************/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare(const char* s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 < *s2)  return true;
        if (*s1 > *s2)  return false;
        s1++; s2++;
    }

    if (*s1 == '\0' && *s2 == '\0')
        return false;

    if (*s1 != '\0')
        return false;

    return true;
}

class Solution
{
public:
    string  getLongestRepeatingString(const string &s)
    {
        int     n = s.size();
        if (n < 2)  return s;

        vector<const char*> suffixArray(n);
        for (int i = 0; i < n; i++)
            suffixArray[i] = &s[i];

        sort(suffixArray.begin(), suffixArray.end(), compare);

        unsigned int  longestIndex = 0, longestLen = 1, curLen = 0;
        for (int i = 0; i < n - 1; i++)
        {
            curLen = getSameLen(suffixArray[i], suffixArray[i + 1]);
            if (curLen > longestLen)
            {
                longestIndex = i;
                longestLen = curLen;
            }
        }

        string result;
        const char* resultSrc = suffixArray[longestIndex];
        while (longestLen-- > 0)
        {
            result += *resultSrc;
            resultSrc++;
        }

        return result;
    }

private:
    inline unsigned int getSameLen(const char *s1, const char *s2)
    {
        unsigned int len = 0;
        while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
        {
            len++; s1++; s2++;
        }
        return len;
    }

};

class Solution_KMP
{
public:
    string  getLongestRepeatingString(const string &s)
    {
        int     n = s.size();
        if (n < 2)  return s;

        string result;  int longestLen = 0, curLen = 0, longestPos = 0;
        AllocateMemory(n);
        calculateNextPatterns(s.c_str());

        for (int i = 0; i < n; i++)
        {
            curLen = getLongestCommonPrefix(s.c_str(), s.c_str() + i, nextArr[i], n - i);
            if (curLen > longestLen)
            {
                longestLen = curLen;
                longestPos = i;
            }
        }

        FreeMemory();
        return s.substr(longestPos, longestLen);
    }

private:
    int **nextArr;
    int     size;

    void AllocateMemory(int n)
    {
        size = n;
        nextArr = new int*[n];
        for (int i = 0; i < n; i++)
            nextArr[i] = new int[n - i];
    }

    void FreeMemory()
    {
        for (int i = 0; i < size; i++)
            delete[] nextArr[i];
        delete[] nextArr;
    }

    void calculateNextPatterns(const char *str)
    {
        for (int i = 0; i < size; i++)
            calculateSingleNextPattern(str + i, nextArr[i], size - i);
    }

    void calculateSingleNextPattern(const char* p, int *next, int n)
    {
        if (n == 0) return;
        int i = 0, j = -1;
        next[0] = -1;
        while (i < n - 1)
        {
            if (j == -1 || p[i] == p[j])
            {
                ++j;    ++i;
                next[i] = j;
            }
            else
                j = next[j];
        }
    }

    int getLongestCommonPrefix(const char *s, const char *p, int *next, int n)
    {
        const char* orgP = p;   int curPos = 0, longestLen = 0;
        while (*s)
        {
            if (*p == '\0') break;

            if (*s == *p)
            {
                ++s; ++p; ++curPos;
            }
            else
            {
                if (curPos > longestLen)
                    longestLen = curPos;
                curPos = next[curPos];
                if (curPos == -1)
                {
                    ++s; p = orgP; curPos = 0;
                }
                else
                    p = orgP + curPos;
            }
        }

        if (*p == '\0' && (s - n) != orgP)
            longestLen = n;

        return longestLen;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string s = "banana";
    Solution_KMP so;

    cout << "Input your string :";
    while (cin>>s)
    {
        cout << "The longest repeating substring is: ";
        cout << so.getLongestRepeatingString(s) << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Input your string :";
    }

	return 0;
}

