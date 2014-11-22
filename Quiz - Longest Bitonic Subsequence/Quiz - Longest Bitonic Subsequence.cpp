//  Given an array arr[0 ... n-1] containing n positive integers, a subsequence of arr[] is called Bitonic if it is 
//  first increasing, then decreasing. Write a function that takes an array as argument and returns the length of the
//  longest bitonic subsequence.
//  A sequence, sorted in increasing order is considered Bitonic with the decreasing part as empty. Similarly, decreasing
//  order sequence is considered Bitonic with the increasing part as empty.
//  
//  Examples:
//  
//  Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
//  Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)
//  
//  Input arr[] = {12, 11, 40, 5, 3, 1}
//  Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)
//  
//  Input arr[] = {80, 60, 30, 40, 20, 10}
//  Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)

#include <iostream>
using namespace std;

int getLongestBitonicSubsequence(int * arr, int n) {
    if (n < 2) return n;

    int *bitonicRes = new int[n], *decreaseRes = new int[n];
    bitonicRes[n - 1] = decreaseRes[n - 1] = 1;

    int maxSequence = 0;
    for (int i = n - 2; i >= 0; --i) {
        decreaseRes[i] = bitonicRes[i] = 1;

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[i] && decreaseRes[j] + 1 > decreaseRes[i])
                decreaseRes[i] = 1 + decreaseRes[j];
        }

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[i] && bitonicRes[j] + 1 > bitonicRes[i])
                bitonicRes[i] = 1 + bitonicRes[j];
        }

        if (bitonicRes[i] < decreaseRes[i]) bitonicRes[i] = decreaseRes[i];
        if (bitonicRes[i] > maxSequence) maxSequence = bitonicRes[i];
    }

    delete[] bitonicRes; delete[] decreaseRes;
    return maxSequence;
}


int main()
{
    int arr1[] = { 1, 11, 2, 10, 4, 5, 2, 1 };
    int arr2[] = { 12, 11, 40, 5, 3, 1 };
    int arr3[] = { 80, 60, 30, 40, 20, 10 };

    cout << getLongestBitonicSubsequence(arr1, sizeof(arr1) / sizeof(int)) << endl;
    cout << getLongestBitonicSubsequence(arr2, sizeof(arr2) / sizeof(int)) << endl;
    cout << getLongestBitonicSubsequence(arr3, sizeof(arr3) / sizeof(int)) << endl;
	return 0;
}

