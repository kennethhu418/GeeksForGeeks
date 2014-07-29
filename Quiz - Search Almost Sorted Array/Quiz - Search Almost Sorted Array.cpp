// Quiz - Search Almost Sorted Array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
#include <time.h>

using namespace std;

class Solution
{
public:
    int searchArray(int arr[], int n, int target)
    {
        if (n == 0) return -1;
        int start = 0, end = n - 1, mid = 0;
        while (start < end)
        {
            if (start + 1 == end)
            {
                if (arr[start] == target)   return start;
                if (arr[end] == target) return end;
                return -1;
            }

            mid = ((start + end) >> 1);
            if (arr[mid] == target) return mid;

            if (arr[mid] >= arr[mid - 1] && arr[mid] <= arr[mid + 1])
            {
                if (target > arr[mid])
                    start = mid + 1;
                else
                    end = mid - 1;
                continue;
            }
            
            if (arr[mid] < arr[mid - 1])
            {
                if (target == arr[mid - 1]) return mid - 1;
                if (target < arr[mid - 1])
                    end = mid - 2;
                else
                    start = mid + 1;
                continue;
            }

            if (target == arr[mid + 1]) return mid + 1;
            if (target < arr[mid + 1])
                end = mid - 1;
            else
                start = mid + 2;
        }

        if (start > end)    return -1;
        return (arr[start] == target) ? start : -1;
    }
};

class Solution_BruteForce
{
public:
    int searchArray(int arr[], int n, int target)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == target)   return i;
        }
        return -1;
    }
};

void    generateArray(int arr[], int n, int max_val, int swapNum)
{
    unordered_set<int>  mapA;
    int curVal = 0;

    for (int i = 0; i < n; )
    {
        curVal = rand() % (max_val + 1);
        if (mapA.find(curVal) == mapA.end())
        {
            arr[i++] = curVal;
            mapA.insert(curVal);
        }
    }

    sort(arr, arr + n);

    mapA.clear();
    int curPos = 0;
    for (int i = 0, curCount = 0; i < swapNum && curCount < 300; ++curCount)
    {
        curPos = rand() % (n - 1);
        if (mapA.find(curPos) != mapA.end())    continue;
        swap(arr[curPos], arr[curPos + 1]);
        mapA.insert(curPos);
        mapA.insert(curPos + 1);
        mapA.insert(curPos - 1);
        ++i;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int MAX_ARRAY_SIZE =  300;
    const int MAX_VAL = 100000;
    const int TRY_NUM_COUNT = 5000;
    const int TRY_COUNT_FOR_EACH_ARRAY = MAX_ARRAY_SIZE * 4;

    int dataArr[MAX_ARRAY_SIZE];
    int dataArrSize = MAX_ARRAY_SIZE;
    int swapNum = 0;
    int curSearchNum = 0;
    int tryCount = 0;

    Solution so;
    Solution_BruteForce so_b;
    int b_result, my_result;
    clock_t     total_my = 0, total_b = 0, start_t = 0;

    srand(time(0));
    while (tryCount++ < TRY_NUM_COUNT)
    {
        cout << "tryCount: " << tryCount << endl;

        dataArrSize = rand() % (MAX_ARRAY_SIZE - 1) + 2;
        swapNum = rand() % (dataArrSize >> 1);

        generateArray(dataArr, dataArrSize, MAX_VAL, swapNum);

        for (int i = 0; i < TRY_COUNT_FOR_EACH_ARRAY; i++)
        {
            curSearchNum = rand() % (MAX_VAL + 1);

            start_t = clock();
            my_result = so.searchArray(dataArr, dataArrSize, curSearchNum);
            total_my += (clock() - start_t);

            start_t = clock();
            b_result = so_b.searchArray(dataArr, dataArrSize, curSearchNum);
            total_b += (clock() - start_t);

            if (my_result != b_result)
            {
                cout << "Inconsistent results: my_result = " << my_result << " b_result = " << b_result << endl;
                assert(0);
            }

            //if (my_result >= 0)
            //    cout << "\tFound target: target = " << curSearchNum << " searched result = " << dataArr[my_result] << "."<<endl;
            //else
            //    cout << "\tDid not found target." << endl;
        }
    }

    cout << "total_my = " << total_my << "\ttotal_b = " << total_b << endl;
    
    system("PAUSE");
	return 0;
}

