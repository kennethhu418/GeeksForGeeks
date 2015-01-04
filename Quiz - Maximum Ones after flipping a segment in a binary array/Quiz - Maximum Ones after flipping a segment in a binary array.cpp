//You are given one binary array, whose elements are either 1 or 0. You can flip a segment in the array. Please find the maximum number of 1s 
//we can get after you do one flipping operation (or do nothing).
//
//For example, for the given array:
//{1, 1, 1, 0, 1, 0, 0, 1, 1}
//We can flip the segment[3, 6] to get the maximum number of 1s, which is 9. And after flipping, the array becomes
//{1, 1, 1, 1, 1, 1, 1, 1, 1}
//
//For the following given array, we just do nothing and we can get the maximum number of 1s - 4.
//{1, 1, 1, 1}

#include <iostream>
#include <ctime>
#include <cmath>
#include <assert.h>
using namespace std;

int getMaxCount_bruteforce(const int *arr, int n) {
    if (n < 2) return n;
    int orgOneCount = 0, zero = 0, one = 0;
    int maxDiff = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == 1) orgOneCount++;

        zero = one = 0;
        for (int j = i; j < n; ++j) {
            if (arr[j] == 0) ++zero;
            else ++one;
            if (zero - one > maxDiff) maxDiff = zero - one;
        }
    }
    return maxDiff > 0 ? maxDiff + orgOneCount : orgOneCount;
}

int getMaxCount_dynamicprogramming(const int *arr, int n) {
    if (n < 2) return n;
    int orgOneCount = 0, prevDiff = 0, maxDiff = 0, curDiff = 0;
    if (arr[n - 1] == 0) {
        prevDiff = 1; maxDiff = 1;
    }
    else
        ++orgOneCount;

    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] == 0) {
            curDiff = 1 + prevDiff;
            if (curDiff > maxDiff) maxDiff = curDiff;
        }
        else {
            curDiff = prevDiff - 1;
            if (curDiff < 0) curDiff = 0;
            ++orgOneCount;
        }
        prevDiff = curDiff;
    }

    return orgOneCount + maxDiff;
}


void generateArray(int *arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 2;
}


int main()
{
    const int   MAX_LEN = 600;
    int     n;
    int     arr[MAX_LEN];
    int     result_bruteforce = 0, result_dp = 0;
    int     try_count = 2000;

    while (try_count-- > 0) {
        n = 1 + rand() % MAX_LEN;
        generateArray(arr, n);
        result_bruteforce = getMaxCount_bruteforce(arr, n);
        result_dp = getMaxCount_dynamicprogramming(arr, n);
        assert(result_bruteforce == result_dp);
    }

    return 0;
}

