//Given an array that represents elements of arithmetic progression in order.
//One element is missing in the progression, find the missing number.
//
//Examples:
//
//Input : arr[] = { 2, 4, 8, 10, 12, 14 }
//Output: 6
//
//Input : arr[] = { 1, 6, 11, 16, 21, 31 };
//Output: 26

#include <iostream>
#include <cmath>
#include <ctime>
#include <assert.h>
using namespace std;

int searchMissingNumber(const int *arr, int n) {
    if (n < 2)   return -1;
    if (n == 2) return (arr[1] << 1) - arr[0];
    int k = (arr[n - 1] - arr[0]) / n;
    if (k == 0) return arr[0];

    int start = 0, end = n - 1, mid = -1;
    while (start < end) {
        if (start + 1 == end)
            return arr[start] + k;
        mid = ((start + end) >> 1);
        if (arr[mid] - arr[mid - 1] != k)
            return arr[mid] - k;
        if (arr[mid + 1] - arr[mid] != k)
            return arr[mid + 1] - k;
        if (arr[start] + (mid - start)*k == arr[mid])
            start = mid + 1;
        else
            end = mid - 1;
    }

    return -1;
}

/************* Test Codes Below ***********************/ 
void generateArithmeticArray(int *arr, int n, int MAX_VAL, int MAX_DIFF) {
    if (n == 0) return;
    if (n == 1) {
        arr[0] = rand() % MAX_VAL;
        return;
    }
    else if (n == 2) {
        arr[0] = rand() % MAX_VAL;
        arr[1] = rand() % MAX_VAL;
        return;
    }

    int k = 1 + rand() % MAX_DIFF;
    if (rand() & 1)
        k = -k;

    arr[0] = rand() % (MAX_VAL / 4);
    for (int i = 1; i < n; ++i)
        arr[i] = arr[i - 1] + k;
}

int removeOneElement(int *arr, int *result, int n) {
    if (n < 3) {
        memmove(result, arr, n * sizeof(int));
        return -1;
    }

    int removedIndex = 1 + rand() % (n - 2);
    int nextIndex = 0;
    for (int i = 0; i < removedIndex; ++i)
        result[nextIndex++] = arr[i];
    for (int i = removedIndex + 1; i < n; ++i)
        result[nextIndex++] = arr[i];
    return removedIndex;
}

int main() {
    const int   MAX_N = 400;
    const int   MAX_VAL = 1024;
    const int   MAX_DIFF = 50;
    const int   MAX_TRY = 400000;
    int     dataArr[MAX_N + 1];
    int     testArr[MAX_N + 1];
    int     n = 0;
    int     tryTimes = 0;
    int     targetIndex = 0, target = 0;

    srand(time(NULL));

    while (tryTimes++ < MAX_TRY) {
        n = 4 + rand() % (MAX_N - 3);
        generateArithmeticArray(dataArr, n, MAX_VAL, MAX_DIFF);
        
        targetIndex = removeOneElement(dataArr, testArr, n);
        target = searchMissingNumber(testArr, n - 1);
        assert(target == dataArr[targetIndex]);
    }
    return 0;
}