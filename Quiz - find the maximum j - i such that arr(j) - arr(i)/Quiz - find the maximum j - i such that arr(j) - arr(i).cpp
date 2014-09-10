// Quiz - find the maximum j - i such that arr(j) - arr(i).cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
using namespace std;

//Given an array arr[], find the maximum j – i (j > i) such that arr[j] > arr[i].
//
//Examples:
//
//Input : {34, 8, 10, 3, 2, 80, 30, 33, 1}
//Output: 6  (j = 7, i = 1)
//
//Input : {9, 2, 3, 4, 5, 6, 7, 8, 18, 0}
//Output: 8 (j = 8, i = 0)
//
//Input : {1, 2, 3, 4, 5, 6}
//Output: 5  (j = 5, i = 0)
//
//Input : {6, 5, 4, 3, 2, 1}
//Output: -1

class Solution
{
private:
    int	*leftMinArr;
    int *rightMaxArr;

public:
    int maxIndexDiff(int arr[], int n)
    {
        if (n < 2)
            return -1;

        AllocateMemory(n);

        GetMinMaxArr(arr, n);

        int curMin = getNextMin(arr, n, 0);
        int curMax = getNextMax(arr, n, curMin + 1);
        int maxDiff = -1;
        while (curMin < n && curMax < n)
        {
            if (arr[curMax] > arr[curMin])
            {
                if (curMax - curMin > maxDiff)
                    maxDiff = curMax - curMin;

                curMax = getNextMax(arr, n, curMax + 1);
            }
            else
            {
                curMin = getNextMin(arr, n, curMin + 1);
                if (curMax <= curMin)
                    curMax = getNextMax(arr, n, curMin + 1);
            }
        }

        FreeMemory();
        return maxDiff;
    }

private:
    void AllocateMemory(int n)
    {
        leftMinArr = new int[n];
        rightMaxArr = new int[n];
    }

    void FreeMemory()
    {
        delete[] leftMinArr;
        delete[] rightMaxArr;
    }

    void GetMinMaxArr(int * arr, int n)
    {
        int curMinVal = arr[0];
        for (int i = 0; i < n; ++i)
            curMinVal = leftMinArr[i] = min(curMinVal, arr[i]);
        int curMaxVal = arr[n - 1];
        for (int i = n - 1; i >= 0; --i)
            curMaxVal = rightMaxArr[i] = max(curMaxVal, arr[i]);
    }

    int getNextMax(int * arr, int n, int start)
    {
        while (start < n && rightMaxArr[start] != arr[start])
            ++start;
        return start;
    }

    int getNextMin(int * arr, int n, int start)
    {
        while (start < n && leftMinArr[start] != arr[start])
            ++start;
        return start;
    }
};

int main() {
    Solution so;

    int arr1[] = { 9, 2, 3, 4, 5, 6, 7, 8, 18, 0 };
    int n = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Max diff index of arr1 is " << so.maxIndexDiff(arr1, n) << endl;

    int arr2[] = { 34, 8, 10, 3, 2, 80, 30, 33, 1 };
    n = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Max diff index of arr2 is " << so.maxIndexDiff(arr2, n) << endl;

    int arr3[] = { 9, 2, 3, 4, 5, 6, 7, 8, 18, 0 };
    n = sizeof(arr3) / sizeof(arr3[0]);
    cout << "Max diff index of arr3 is " << so.maxIndexDiff(arr3, n) << endl;

    int arr4[] = { 6, 5, 4, 3, 2, 1 };
    n = sizeof(arr4) / sizeof(arr4[0]);
    cout << "Max diff index of arr4 is " << so.maxIndexDiff(arr4, n) << endl;

    return 0;
}