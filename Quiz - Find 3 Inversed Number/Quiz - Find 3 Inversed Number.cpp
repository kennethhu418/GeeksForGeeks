// Quiz - Find 3 Inversed Number.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <algorithm>
#include <assert.h>
#include <queue>

/***************************************************************************
* Problem Statement:
* An integer array of size n is A[] given, find the three numbers
* s.t. A[i] > A[j] > A[k] and i < j < k
**************************************************************************/

using namespace std;

typedef struct __TripleRes
{
    int pos1;
    int pos2;
    int pos3;
}TripleRes;


/***************************************************************************
* class Solution implements the O(n) algorithm of the search.
**************************************************************************/
class Solution
{
public:
    TripleRes searchInversedNumbers(int arr[], int n)
    {
        TripleRes   result = { -1, -1, -1 };
        if (n < 3)  return result;

        sequence1 = sequence2[0] = sequence2[1] = -1;

        sequence1 = 0;

        for (int i = 1; i < n; i++)
        {
            if (arr[i] > arr[sequence1])
            {
                sequence1 = i;
                continue;
            }

            if (arr[i] == arr[sequence1])
                continue;

            if (sequence2[0] == -1 || arr[i] >= arr[sequence2[1]])
            {
                sequence2[0] = sequence1;
                sequence2[1] = i;
                continue;
            }

            result.pos1 = sequence2[0];
            result.pos2 = sequence2[1];
            result.pos3 = i;
            break;
        }

        return result;
    }

private:
    int sequence1;
    int sequence2[2];
};

/***************************************************************************
* Following codes are used to verify the Solution class by comparing
* the results with brute force searching.
**************************************************************************/

inline void FillArray(int arr[], int n, int max_val)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (max_val + 1);
}

inline void VerifyResult(const int *arr, const TripleRes &result, bool shouldInvalidate)
{
    if (shouldInvalidate)
    {
        assert(result.pos1 < 0);
        return;
    }

    if (arr[result.pos1] > arr[result.pos2] && arr[result.pos2] > arr[result.pos3])
        return;

    assert(0);
}

bool brute_force_verify(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (arr[i] > arr[j] && arr[j] > arr[k])
                    return true;
            }
        }
    }

    return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int ARR_SIZE = 20;
    const int MAX_VAL = 60;
    const int TRY_COUNT = 10000; //try 10000 times of the algorithm
    int arr[ARR_SIZE];
    Solution so;
    TripleRes result;

    srand(time(0));

    int curTryTimes = 0;
    while (curTryTimes++ < TRY_COUNT)
    {
        FillArray(arr, ARR_SIZE, MAX_VAL);
        if (curTryTimes % 10 == 0)
            sort(arr, arr + ARR_SIZE);

        cout << curTryTimes << " round verify." << endl << endl;

        result = so.searchInversedNumbers(arr, ARR_SIZE);
        VerifyResult(arr, result, !brute_force_verify(arr, ARR_SIZE));
    }

    return 0;
}
