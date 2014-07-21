// Quiz - String Match.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution {
public:
    char* strStr(char *haystack, char *needle) {
        if (haystack == NULL || needle == NULL)    return NULL;
        if (*haystack == '\0' && *needle == '\0')  return haystack;
        if (*haystack == '\0' || *needle == '\0')  return NULL;

        AllocateAndInitPatternMemory(needle);

        char* curNeedle = needle, *curHaystack = haystack;
        int    curNeedlePos = 0;
        while (*curHaystack != '\0')
        {
            if (*curNeedle == '\0')
                break;

            if (*curHaystack == *curNeedle)
            {
                ++curHaystack; ++curNeedle; ++curNeedlePos;
                continue;
            }

            if (patternCounter[curNeedlePos] == -1)
            {
                ++curHaystack; curNeedle = needle;
                curNeedlePos = 0;
                continue;
            }

            curNeedle = needle + patternCounter[curNeedlePos];
            curNeedlePos = patternCounter[curNeedlePos];
        }

        char* result = (*curNeedle == '\0') ? (curHaystack - patternSize) : NULL;
        FreePatternMemory();
        return result;
    }

private:
    int    *patternCounter;
    int    patternSize;

    void   AllocateAndInitPatternMemory(const char* str)
    {
        if (str == NULL || *str == '\0')
            return;

        patternSize = 0;
        const char* curS = str;
        while (*curS != '\0')
        {
            ++patternSize;
            ++curS;
        }

        patternCounter = new int[patternSize];
        patternCounter[0] = -1;
        int i = 0, j = -1;

        while (i < patternSize - 1)
        {
            if (j == -1 || str[i] == str[j])
            {
                ++i;
                ++j;
                patternCounter[i] = j;
            }
            else
                j = patternCounter[j];
        }
    }

    void FreePatternMemory()
    {
        delete[] patternCounter;
        patternCounter = NULL;
        patternSize = 0;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    using namespace std;

    char * src = "mississippi";
    char *dest = "issip";
    Solution so;
    cout<< so.strStr(src, dest) <<endl;

    system("PAUSE");
	return 0;
}

