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
        if (n < 2) return;
        int start = 0, end = n - 1, pStart = 0, pEnd = 0;
        while (start <= end) {
            partition(arr + start, end - start + 1, pStart, pEnd);
            if (K >= pStart + 1 && K <= pEnd + 1) return;
            if (K <= pStart)
                end = start + pStart - 1;
            else {
                start = start + pEnd + 1;
                K -= (pEnd + 1);
            }        
        }
    }

private:
    int selectPivot(int arr[], int n)
    {
        int     mid = ((n - 1) >> 1);
        if (arr[0] >= arr[mid] && arr[0] <= arr[n - 1] || arr[0] >= arr[n - 1] && arr[0] <= arr[mid])   return 0;
        if (arr[mid] >= arr[0] && arr[mid] <= arr[n - 1] || arr[mid] >= arr[n - 1] && arr[mid] <= arr[0]) return mid;
        return n - 1;
    }

    void partition(int * arr, int n, int &pStart, int &pEnd) {
        if (n <= 0) return;
        if (n == 1) {
            pStart = pEnd = 0; return;
        }

        int pivotIndex = selectPivot(arr, n);
        swap(arr[0], arr[pivotIndex]);

        int pivot = arr[0], curPos = 1, curEnd = n - 1, pCnt = 1;
        pStart = 0;
        while (curPos <= curEnd) {
            if (arr[curPos] == pivot) {
                ++curPos; ++pCnt; continue;
            }
            if (arr[curPos] > pivot) {
                swap(arr[pStart++], arr[curPos++]);
                continue;
            }

            while (curPos <= curEnd && arr[curEnd] < pivot) --curEnd;
            if (curPos > curEnd) break;
            swap(arr[curPos], arr[curEnd--]);
        }
        
        pEnd = pStart + pCnt - 1;
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
//        //cout << "Before sorting:" << endl;
//        //OutputArray(resultArr, size);
//        so.sort(resultArr, size);
//        //cout << "After sorting:" << endl;
//        //OutputArray(resultArr, size);
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
        so_sort.sort(dataArr, size); //sorted increasingly, should reverse
        int s = 0, e = size - 1; while (s < e) swap(dataArr[s++], dataArr[e--]);
        s = 0; e = K - 1; while (s < e) swap(dataArr[s++], dataArr[e--]);

        //get the largest K numbers
        so_select.selectKLargestNumber(resultArr, size, K);

        //verify results
        so_sort.sort(resultArr, K);
        if (!verifySelection(resultArr, dataArr, K))
        {
            cout << "Oh, no!    " << times << endl;
            system("PAUSE");
        }

        //cout << "==============================================" << endl;
    }


    return 0;
}
