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

#include <iostream>
using namespace std;

class Solution
{
private:
    int getFirstDecrease(int arr[], int n)
    {
        int pos = 0;
        while (pos < n - 1)
        {
            if (arr[pos] > arr[pos + 1]) return pos;
            ++pos;
        }
        return n;
    }

    int getFirstIncrease(int arr[], int n)
    {
        int pos = n - 1;
        while (pos > 0)
        {
            if (arr[pos] < arr[pos - 1]) return pos;
            --pos;
        }
        return -1;
    }

    void getMinMax(int arr[], int start, int end, int &minVal, int &maxVal)
    {
        minVal = maxVal = arr[start++];
        while (start <= end){
            minVal = min(minVal, arr[start]);
            maxVal = max(maxVal, arr[start++]);
        }
    }

public:
    int getUnsorted(int arr[], int n, int &rangeEnd)
    {
        int rangeStart = -1; rangeEnd = -1;
        if (n < 2)	return rangeStart;

        rangeStart = getFirstDecrease(arr, n);
        if (rangeStart >= n) return -1;

        rangeEnd = getFirstIncrease(arr, n);

        int minVal = 0, maxVal = 0;
        getMinMax(arr, rangeStart, rangeEnd, minVal, maxVal);

        while (rangeStart > 0 && arr[rangeStart - 1] > minVal)
            --rangeStart;
        while (rangeEnd < n - 1 && arr[rangeEnd + 1] < maxVal)
            ++rangeEnd;

        return rangeStart;
    }
};

int main() {
    int arr1[] = { 10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60 };
    int arr2[] = { 0, 1, 15, 25, 6, 7, 30, 40, 50 };
    int arr3[] = { 10, 12, 20, 30, 35, 40, 42, 43, 45, 50, 60, 10 };
    int start = -1, end = -1;
    Solution so;

    start = so.getUnsorted(arr1, sizeof(arr1) / sizeof(int), end);
    cout << "Unsorted range of arr1 is from " << start << " to " << end << endl;

    start = so.getUnsorted(arr2, sizeof(arr2) / sizeof(int), end);
    cout << "Unsorted range of arr2 is from " << start << " to " << end << endl;

    start = so.getUnsorted(arr3, sizeof(arr3) / sizeof(int), end);
    cout << "Unsorted range of arr3 is from " << start << " to " << end << endl;
    return 0;
}
