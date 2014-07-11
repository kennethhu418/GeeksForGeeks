// Quiz - Longest Repeating SubString.cpp : 定义控制台应用程序的入口点。
//

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

int _tmain(int argc, _TCHAR* argv[])
{
    string s = "banana";
    Solution so;

    cout << "Input your string :";
    while (cin>>s)
    {
        cout << "The longest repeating substring is: ";
        cout << so.getLongestRepeatingString(s) << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Input your string :";
    }

	return 0;
}

