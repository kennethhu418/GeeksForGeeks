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

        quickSort(arr, 0, n - 1);
    }

private:
    void quickSort(int arr[], int start, int end)
    {
        if (start >= end)   return;
        int leftEnd = start -1, rightStart = end + 1;
        partitionArray(arr, start, end, leftEnd, rightStart);

        quickSort(arr, start, leftEnd);
        quickSort(arr, rightStart, end);
    }

    void partitionArray(int arr[], int start, int end, int &leftEnd, int &rightStart)
    {
        leftEnd = start; rightStart = end;
        int curPosL = start, curPosR = end;
        int pivot = arr[(start + end) >> 1];
        int temp = 0;

        while (curPosL <= curPosR)
        {
            while (curPosL <= curPosR && arr[curPosL] <= pivot)
            {
                if (arr[curPosL] < pivot)  arr[leftEnd++] = arr[curPosL];
                ++curPosL;
            }

            if (curPosL > curPosR)  break;

            while (curPosL <= curPosR && arr[curPosR] >= pivot)
            {
                if (arr[curPosR] > pivot)  arr[rightStart--] = arr[curPosR];
                --curPosR;
            }

            if (curPosL > curPosR)  break;

            temp = arr[curPosR];
            arr[rightStart--] = arr[curPosL];
            arr[leftEnd++] = temp;
            ++curPosL; --curPosR;
        }

        for (int i = leftEnd; i <= rightStart; i++)
            arr[i] = pivot;
        --leftEnd;  ++rightStart;
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
//int _tmain(int argc, _TCHAR* argv[])
//{
//    const int   MAX_VAL = 700;
//    int dataArr[1000];
//    int resultArr[1000];
//    int size;
//    int times = 6000;
//    Solution_QSort so;
//
//    srand(time(0));
//
//    while (times-- > 0)
//    {
//        size = rand() % 1001;
//        generateArray(dataArr, size, MAX_VAL);
//        memcpy(resultArr, dataArr, sizeof(int)*size);
//        cout << "Before sorting:" << endl;
//        OutputArray(resultArr, size);
//        so.sort(resultArr, size);
//        cout << "After sorting:" << endl;
//        OutputArray(resultArr, size);
//        if (!checkArray(resultArr, dataArr, size))
//        {
//            cout << "Oh, no!" << endl;
//            system("PAUSE");
//        }
//            
//        //cout << "==============================================" << endl;
//    }
//
//
//	return 0;
//}


//Verify Selecting largest K Number algorithm
int _tmain(int argc, _TCHAR* argv[])
{
    const int   MAX_VAL = 700;
    int dataArr[1000];
    int resultArr[1000];
    int size, K;
    int times = 6000;
    Solution_QSort so_sort;
    Solution_KLargest so_select;

    srand(time(0));

    while (times-- > 0)
    {
        size = 1 + rand() % 1000;
        K = rand() % size + 1;
        generateArray(dataArr, size, MAX_VAL);
        memcpy(resultArr, dataArr, sizeof(int)*size);

        //sort original array
        so_sort.sort(dataArr, size);

        //get the largest K numbers
        so_select.selectKLargestNumber(resultArr, size, K);

        //verify results
        so_sort.sort(resultArr, K);
        if (!verifySelection(resultArr, dataArr, K))
        {
            cout << "Oh, no!" << endl;
            system("PAUSE");
        }

        //cout << "==============================================" << endl;
    }


    return 0;
}
