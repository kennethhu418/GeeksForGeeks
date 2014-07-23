// Quiz - Array Partial Sorting.cpp : 定义控制台应用程序的入口点。
//


/****************************************************************************************************
    Given an array of integers, write a method to find indices m and n such that if you
    sorted elements m through n, the entire array would be sorted. Minimize n - m (that
    is, find the smallest such sequence).
****************************************************************************************************/
#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct _Range
{
    int     start;
    int     end;
}Range;

class Solution
{
public:
    Range   getUnsortedRange(int A[], int n)
    {
        Range result = {-1, -1};
        if (n < 2)  return result;

        int leftEnd = 0, rightStart = n - 1;
        while (leftEnd < n - 1)
        {
            if (A[leftEnd + 1] < A[leftEnd])
                break;
            ++leftEnd;
        }
        if (leftEnd == n - 1)   return result;

        while (rightStart > 0)
        {
            if (A[rightStart] < A[rightStart - 1])
                break;
            --rightStart;
        }

        int middleMin = 0, middleMax = 0;
        if (leftEnd + 1 == rightStart)
        {
            middleMin = A[rightStart++];
            middleMax = A[leftEnd--];
        }
        else
        {
            getMinMaxInRange(A, leftEnd + 1, rightStart - 1, middleMin, middleMax);
        }

        while (true)
        {
            if (leftEnd >= 0 && A[leftEnd] > middleMin)
            {
                if (A[leftEnd] > middleMax)
                    middleMax = A[leftEnd];
                --leftEnd;
                continue;
            }

            if (rightStart < n && A[rightStart] < middleMax)
            {
                if (A[rightStart] < middleMin)
                    middleMin = A[rightStart];
                ++rightStart;
                continue;
            }

            break;
        }

        result.start = leftEnd + 1;
        result.end = rightStart - 1;
        return result;
    }

private:
    inline void getMinMaxInRange(int A[], int start, int end, int &minVal, int &maxVal)
    {
        minVal = maxVal = A[start++];
        while (start <= end)
        {
            if (A[start] > maxVal)
                maxVal = A[start];
            if (A[start] < minVal)
                minVal = A[start];
            ++start;
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int A[] = {1, 2, 5, 3, 6, 4, 7,  8};
    Solution so;

    Range r = so.getUnsortedRange(A, sizeof(A) / sizeof(int));
	return 0;
}

