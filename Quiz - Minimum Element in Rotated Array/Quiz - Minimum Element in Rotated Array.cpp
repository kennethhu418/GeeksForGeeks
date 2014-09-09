// Quiz - Minimum Element in Rotated Array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

class Solution
{
public:
    int findMinValue(int arr[], int n)
    {
        if (n == 0) return -1;
        if (n == 1) return arr[0];

        int start = 0, end = n - 1, mid = -1;
        while (start < end)
        {
            mid = ((start + end) >> 1);
            if (arr[start] == arr[end] && arr[start] == arr[mid])
            {
                ++start; continue;
            }

            if (arr[start] <= arr[mid] && arr[mid] <= arr[end])
                return arr[start];

            if (arr[mid] >= arr[start] && arr[mid] >= arr[end])
            {
                start = mid + 1;
                continue;
            }

            if (arr[mid] < arr[mid - 1])    return arr[mid];
            end = mid - 1;
        }

        return arr[start];
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Solution so;
    int arr1[] = { 5, 6, 1, 2, 3, 4 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr1, n1));

    int arr2[] = { 1, 2, 3, 4 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr2, n2));

    int arr3[] = { 1 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr3, n3));

    int arr4[] = { 1, 2 };
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr4, n4));

    int arr5[] = { 2, 1 };
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr5, n5));

    int arr6[] = { 5, 6, 7, 1, 2, 3, 4 };
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr6, n6));

    int arr7[] = { 1, 2, 3, 4, 5, 6, 7 };
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr7, n7));

    int arr8[] = { 2, 3, 4, 5, 6, 7, 8, 1 };
    int n8 = sizeof(arr8) / sizeof(arr8[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr8, n8));

    int arr9[] = { 3, 4, 5, 1, 2 };
    int n9 = sizeof(arr9) / sizeof(arr9[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr9, n9));

    int arr11[] = { 5, 6, 1, 2, 3, 4 };
    int n11 = sizeof(arr11) / sizeof(arr11[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr11, n11));

    int arr12[] = { 1, 1, 0, 1 };
    int n12 = sizeof(arr12) / sizeof(arr12[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr12, n12));

    int arr13[] = { 1, 1, 2, 2, 3 };
    int n13 = sizeof(arr13) / sizeof(arr13[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr13, n13));

    int arr14[] = { 3, 3, 3, 4, 4, 4, 4, 5, 3, 3 };
    int n14 = sizeof(arr14) / sizeof(arr14[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr14, n14));

    int arr15[] = { 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2 };
    int n15 = sizeof(arr15) / sizeof(arr15[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr15, n15));

    int arr16[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1 };
    int n16 = sizeof(arr16) / sizeof(arr16[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr16, n16));

    int arr17[] = { 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2 };
    int n17 = sizeof(arr17) / sizeof(arr17[0]);
    printf("The minimum element is %d\n", so.findMinValue(arr17, n17));

	return 0;
}

