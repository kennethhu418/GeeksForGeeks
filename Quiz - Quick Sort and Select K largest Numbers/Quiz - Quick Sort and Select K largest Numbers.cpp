// Quiz - Quick Sort and Select K largest Numbers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <functional>

using namespace std;

// We can use median of median to get the optimal pivot, which can equally
// partition the array.
// See Solution_KLargest for detailed implementation
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

#define GROUP_SIZE 5
class Solution_KLargest {
public:
    int selectKLargestNumber(int *arr, int n, int k) {
        if (n == 0) return -1;
        if (n <= GROUP_SIZE) {
            sort(arr, arr + n, greater<int>());
            return arr[n - k];
        }

        int pivotStart = 0, pivotCount = 0;
        pivotCount = partition(arr, n, pivotStart);
        if ((k - 1 >= pivotStart) && (k - 1 < pivotStart + pivotCount))
            return arr[pivotStart];
        if (k - 1 < pivotStart)
            return selectKLargestNumber(arr, pivotStart, k);
        return selectKLargestNumber(arr + pivotStart + pivotCount, n - (pivotStart + pivotCount), k - (pivotStart + pivotCount));
    }

private:
    int partition(int *arr, int n, int &pivotStart) {
        int pivotCount = 0; pivotStart = 0;
        if (n == 0) return pivotCount;
        if (n == 1) return 1;

        int groupCount = (n + GROUP_SIZE - 1) / GROUP_SIZE;
        int *medianArr = new int[groupCount];
        for (int i = 0; i < groupCount - 1; ++i)
            medianArr[i] = median(arr + i * GROUP_SIZE, GROUP_SIZE);
        medianArr[groupCount - 1] = median(arr + (groupCount - 1) * GROUP_SIZE, n % GROUP_SIZE);

        int     pivot = selectKLargestNumber(medianArr, groupCount, (groupCount + 1) >> 1);
        delete[] medianArr;
        for (int i = 0; i < n; ++i) {
            if (pivot == arr[i]) {
                swap(arr[0], arr[i]);
                break;
            }
        }

        pivotCount = 1; pivotStart = 0;
        int curPos1 = 1, curPos2 = n - 1;
        while (curPos1 <= curPos2) {
            if (pivot == arr[curPos1]) {
                ++pivotCount; ++curPos1;
            }
            else if (pivot > arr[curPos1]) {
                while (curPos1 <= curPos2 && arr[curPos2] < pivot)
                    --curPos2;
                if (curPos1 > curPos2) break;
                swap(arr[curPos1], arr[curPos2--]);
            }
            else
                swap(arr[curPos1++], arr[pivotStart++]);
        }

        return pivotCount;
    }

    int median(int *arr, int n) {
        sort(arr, arr + n);
        return arr[(n - 1) >> 1];
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
    const int   MAX_SIZE = 7;
    int dataArr[MAX_SIZE];
    int resultArr[MAX_SIZE];
    int size, K;
    int times = 60000;
    Solution_QSort so_sort;
    Solution_KLargest so_select;

    //srand(time(0));

    while (times-- > 0)
    {
        cout << "Current Stamp: " << times << endl;
        size = 1 + rand() % MAX_SIZE;
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
