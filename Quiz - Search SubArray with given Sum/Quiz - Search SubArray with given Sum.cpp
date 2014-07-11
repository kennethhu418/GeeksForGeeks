// Quiz - Search SubArray with given Sum.cpp : 定义控制台应用程序的入口点。
//


/****************************************************************************************
    Search Contiguous elements in an array whose sum is k.
    **************************************************************************************/

#include "stdafx.h"
#include <time.h>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool getContigousSubArray(int arr[], int n, int S, int &start, int &end)
    {
        if (n == 0) return false;
        if (n == 1){ start = end = 0; return arr[0] == S; }

        start = end = 0;
        int curSum = 0;

        while (end < n)
        {
            curSum += arr[end];
            if (curSum == S)
                return true;

            if (curSum < S)
            {
                end++;  continue;
            }

            while (start <= end)
            {
                curSum -= arr[start++];
                if (curSum == S)    return true;
                if (curSum > S)         continue;
                break;
            }

            end++;
        }

        return false;
    }
};

void  FillArray(int arr[], int n, unsigned int max_val = 100)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (max_val + 1);
}

inline int getSum(int arr[], int start, int end)
{
    int sumVal = 0;
    while (start <= end)
        sumVal += arr[start++];
    return sumVal;
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int ARRAY_SIZE = 14;
    const int MAX_VAL = 46;

    int     dataArr[ARRAY_SIZE];
    FillArray(dataArr, ARRAY_SIZE, MAX_VAL);

    Solution so;
    int expectedStart = -1, expectedEnd = -1, sum = 0;
    int resultStart = 0, resultEnd = 0;

    srand(time(0));

    cout << "Input start and end expected (maxVal 13. -1 as no valid sum and -2 as new array): ";
    while (cin >> expectedStart >> expectedEnd)
    {
        if (expectedStart > expectedEnd)
        {
            cout << "Invalid input, try again." << endl;
            cout << "Input start and end expected (maxVal 13. -1 as no valid sum): ";
            continue;
        }

        if (expectedStart >= ARRAY_SIZE || expectedEnd >= ARRAY_SIZE)
        {
            cout << "Invalid input, try again." << endl;
            cout << "Input start and end expected (maxVal 13. -1 as no valid sum): ";
            continue;
        }

        if (expectedStart == -1)
        {
            sum = rand() % (2*MAX_VAL);
        }
        else if (expectedStart == -2)
        {
            FillArray(dataArr, ARRAY_SIZE, MAX_VAL);
            cout << "Input start and end expected (maxVal 13. -1 as no valid sum): ";
            continue;
        }
        else
            sum = getSum(dataArr, expectedStart, expectedEnd);
        cout << "Expected Sum is " << sum << endl;

        if (so.getContigousSubArray(dataArr, ARRAY_SIZE, sum, resultStart, resultEnd))
        {
            cout << "Successfully searched the range: " << resultStart << " - " << resultEnd << endl;
            cout << "The resulted sum is " << getSum(dataArr, resultStart, resultEnd) << endl;
        }
        else
            cout << "Failed to search the range" << endl;

        cout << "=========================================" << endl << endl;
        cout << "Input start and end expected (maxVal 13. -1 as no valid sum): ";
    }

	return 0;
}

