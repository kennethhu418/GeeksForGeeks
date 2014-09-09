// Quiz - Quick Sort and Select K largest Numbers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <assert.h>

using namespace std;

class Solution_QSort
{
public:
    void    sort(int arr[], int n)
    {
        if (n < 2)  return;
        if (n == 2)
        {
            if (arr[0] > arr[1])
                swap(arr[0], arr[1]);
            return;
        }

        int pivotStart = 0, pivotCount = 0;
        pivotStart = partition(arr, n, pivotCount);

        sort(arr, pivotStart);
        sort(arr + pivotStart + pivotCount, n - (pivotStart + pivotCount));
    }

private:
    int     partition(int arr[], int n, int &pivotCount)
    {
        int pivotIndex = selectPivot(arr, n);
        if (pivotIndex > 0) swap(arr[pivotIndex], arr[0]);

        pivotCount = 1;
        int startP = 0, curPos = 1, startG = n - 1, pivot = arr[0];
        while (curPos <= startG)
        {
            if (arr[curPos] == pivot){
                ++pivotCount; ++curPos;
                continue;
            }

            if (arr[curPos] < pivot)
                swap(arr[curPos++], arr[startP++]);
            else
            {
                while (startG >= curPos && arr[startG] > pivot) --startG;
                if (startG < curPos) break;
                swap(arr[startG--], arr[curPos]);
            }
        }

        return startP;
    }

    int selectPivot(int arr[], int n)
    {
        int     mid = ((n - 1) >> 1);
        if (arr[0] >= arr[mid] && arr[0] <= arr[n - 1] || arr[0] >= arr[n - 1] && arr[0] <= arr[mid])   return 0;
        if (arr[mid] >= arr[0] && arr[mid] <= arr[n - 1] || arr[mid] >= arr[n - 1] && arr[mid] <= arr[0]) return mid;
        return n - 1;
    }
};

class Solution_KLargest
{
public:
    void    selectKLargestNumber(int arr[], int n, int K)
    {
        if (K >= n) return;

        quickSelectionSort(arr, 0, n - 1, K);
    }

private:
    void    quickSelectionSort(int arr[], int start, int end, int K)
    {
        if (start == end)
        {
            assert(K == 1);
            return;
        }

        int pivot = arr[(start + end) >> 1];
        int curL = start, curR = end, nextLPlace = start, nextRPlace = end, tmp = -1;
        while (curL <= curR)
        {
            while (curL <= curR && arr[curL] <= pivot)
            {
                if (arr[curL] < pivot)  arr[nextLPlace++] = arr[curL];
                ++curL;
            }

            if (curL > curR)    break;

            while (curL <= curR && arr[curR] >= pivot)
            {
                if (arr[curR] > pivot)  arr[nextRPlace--] = arr[curR];
                --curR;
            }

            if (curL > curR)    break;

            tmp = arr[curR--];
            arr[nextRPlace--] = arr[curL++];
            arr[nextLPlace++] = tmp;
        }

        for (int i = nextLPlace; i <= nextRPlace; i++)
            arr[i] = pivot;

        if (K < nextLPlace - start)  quickSelectionSort(arr, start, nextLPlace - 1, K);
        if (K > nextRPlace + 1 - start)  quickSelectionSort(arr, nextRPlace + 1, end, K + start - nextRPlace - 1);
    }
};

void generateArray(int arr[], int n, int maxVal)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (maxVal + 1);
}

inline int getNumberCount(int arr[], int n, int start)
{
    int orgVal = arr[start]; int count = 0;
    while (start < n && arr[start] == orgVal)
    {
        ++count; ++start;
    }
    return count;
}

bool checkArray(int arr[], int orgArr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] < arr[i])    return false;
    }

    unordered_map<int, int> mapA;
    for (int i = 0; i < n; i++)
        mapA[orgArr[i]]++;

    int curPos = 0, curCount = 0;
    while (curPos < n)
    {
        curCount = getNumberCount(arr, n, curPos);
        if (mapA[arr[curPos]] != curCount)
            return false;
        curPos += curCount;
    }

    return true;
}

bool verifySelection(int arr1[], int arr2[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

void OutputArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}




//Verify Sorting algorithm
int _tmain(int argc, _TCHAR* argv[])
{
    const int   MAX_VAL = 700;
    int dataArr[1000];
    int resultArr[1000];
    int size;
    int times = 6000;
    Solution_QSort so;

    srand(time(0));

    while (times-- > 0)
    {
        size = rand() % 1001;
        generateArray(dataArr, size, MAX_VAL);
        memcpy(resultArr, dataArr, sizeof(int)*size);
        //cout << "Before sorting:" << endl;
        //OutputArray(resultArr, size);
        so.sort(resultArr, size);
        //cout << "After sorting:" << endl;
        //OutputArray(resultArr, size);
        if (!checkArray(resultArr, dataArr, size))
        {
            cout << "Oh, no!" << endl;
            system("PAUSE");
        }
            
        //cout << "==============================================" << endl;
    }


	return 0;
}


//Verify Selecting largest K Number algorithm
//int _tmain(int argc, _TCHAR* argv[])
//{
//    const int   MAX_VAL = 700;
//    int dataArr[1000];
//    int resultArr[1000];
//    int size, K;
//    int times = 6000;
//    Solution_QSort so_sort;
//    Solution_KLargest so_select;
//
//    srand(time(0));
//
//    while (times-- > 0)
//    {
//        size = 1 + rand() % 1000;
//        K = rand() % size + 1;
//        generateArray(dataArr, size, MAX_VAL);
//        memcpy(resultArr, dataArr, sizeof(int)*size);
//
//        //sort original array
//        so_sort.sort(dataArr, size);
//
//        //get the largest K numbers
//        so_select.selectKLargestNumber(resultArr, size, K);
//
//        //verify results
//        so_sort.sort(resultArr, K);
//        if (!verifySelection(resultArr, dataArr, K))
//        {
//            cout << "Oh, no!" << endl;
//            system("PAUSE");
//        }
//
//        //cout << "==============================================" << endl;
//    }
//
//
//    return 0;
//}
