// Quiz - Maximum of all subarrays of size K.cpp : 定义控制台应用程序的入口点。
//

//Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.
//
//Examples:
//
//Input :
//    arr[] = { 1, 2, 3, 1, 4, 5, 2, 3, 6 }
//      k = 3
//      Output :
//             3 3 4 5 5 5 6
//
//         Input :
//               arr[] = { 8, 5, 10, 7, 9, 4, 15, 12, 90, 13 }
//      k = 4
//      Output :
//             10 10 10 15 15 90 90



//We create a Dequeue, Qi of capacity k, that stores only useful elements of current window of k elements.An element is 
//useful if it is in current window and is greater than all other elements on left side of it in current window.We process all 
//array elements one by one and maintain Qi to contain useful elements of current window and these useful elements are 
//maintained in sorted order.The element at front of the Qi is the largest and element at rear of Qi is the smallest of 
//current window.

#include <iostream>
#include <deque>
#include <assert.h>
using namespace std;

class Solution
{
public:
    void getMaxElementsInKSizeWindow(int * arr, int n, int K, int * resultArr)
    {
        if (n == 0 || K == 0 || K > n) return;
        if (K == 1){
            memmove(resultArr, arr, sizeof(int)*n);
            return;
        }

        deque<int>    windowQ;
        //Fill with first K elements into windowQ
        windowQ.push_back(0);
        for (int i = 1; i < K; ++i){
            while (!windowQ.empty() && arr[i] >= arr[windowQ.back()])
                windowQ.pop_back();
            windowQ.push_back(i);
        }

        resultArr[0] = arr[windowQ.front()];
        for (int i = K; i < n; ++i){
            while (!windowQ.empty() && windowQ.front() < i - K + 1)
                windowQ.pop_front();
            assert(!windowQ.empty());
            while (!windowQ.empty() && arr[i] >= arr[windowQ.back()])
                windowQ.pop_back();
            windowQ.push_back(i);
            resultArr[i - K + 1] = arr[windowQ.front()];
        }
    }
};

void OutputArr(int * arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << "  ";
    cout << endl;
}

int main() {
    Solution so;
    int resultArr[20];
    int arr[] = { 8, 5, 10, 7, 9, 4, 15, 12, 90, 13 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int K = 4;

    so.getMaxElementsInKSizeWindow(arr, n, K, resultArr);
    OutputArr(resultArr, n - K + 1);

    return 0;
}