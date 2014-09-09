// Quiz - Radix Sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

//Given an array of numbers of size n.It is also given that the array elements are in range from 0 to n2 – 1. Sort the given array in linear time.
//
//Examples:
//Since there are 5 elements, the elements can be from 0 to 24.
//Input : arr[] = { 0, 23, 14, 12, 9 }
//Output: arr[] = { 0, 9, 12, 14, 23 }
//
//Since there are 3 elements, the elements can be from 0 to 8.
//Input : arr[] = { 7, 0, 2 }
//Output: arr[] = { 0, 2, 7 }

//Solution: If we use Counting Sort, it would take O(n ^ 2) time as the given range is of size n^2. Using any comparison based sorting like Merge Sort, Heap Sort, ..etc would take O(nLogn) time.
//    Now question arises how to do this in 0(n) ? Firstly, is it possible ? Can we use data given in question ? n numbers in range from 0 to n2 – 1 ?
//    The idea is to use Radix Sort.Following is standard Radix Sort algorithm.
//
//    1) Do following for each digit i where i varies from least
//    significant digit to the most significant digit.
//    …………..a) Sort input array using counting sort(or any stable sort) according to the i’th digit
//
//    Let there be d digits in input integers.Radix Sort takes O(d*(n + b)) time where b is the base for representing numbers, for example, for decimal system, b is 10. Since n2 - 1 is the maximum possible value, the value of d would be O(\log_b(n)).So overall time complexity is O((n + b)*\log_b(n)).Which looks more than the time complexity of comparison based sorting algorithms for a large k.The idea is to change base b.If we set b as n, the value of O(\log_b(n)) becomes O(1) and overall time complexity becomes O(n).

class Solution
{
private:
    int *countArr;
    int *sortArr;

public:
    void    sortWithRadix(int * arr, int n)
    {
        if (n < 2)
            return;

        //Allocate memory for private arrays
        AllocateMemory(n);

        int r = 0, base = 1, s = 0, d = 0;
        bool stop = false;
        while (true)
        {
            stop = true; //assume currently all digits have been visited
            memset(countArr, 0, sizeof(int)*n);
            for (int i = 0; i < n; ++i)
            {
                d = arr[i] / base;
                r = d % n;
                if (d > 0)  stop = false;
                ++countArr[r];
            }

            if (stop)   break;

            //calculate the start index of each digit numbers
            s = 0;
            for (int i = 0; i < n; i++)
            {
                d = countArr[i];
                countArr[i] = s;
                s += d;
            }

            //now categorize the input numbers
            for (int i = 0; i < n; i++)
            {
                r = (arr[i] / base) % n;
                sortArr[countArr[r]++] = arr[i];
            }

            memmove(arr, sortArr, sizeof(int) * n);
            base *= n;
        }

        FreeMemory();
    }

private:
    void AllocateMemory(int n)
    {
        countArr = new int[n];
        sortArr = new int[n];
    }

    void FreeMemory()
    {
        delete[] countArr;
        delete[] sortArr;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int arr[] = { 7, 0, 2 };

    Solution so;
    so.sortWithRadix(arr, sizeof(arr) / sizeof(int));

	return 0;
}

