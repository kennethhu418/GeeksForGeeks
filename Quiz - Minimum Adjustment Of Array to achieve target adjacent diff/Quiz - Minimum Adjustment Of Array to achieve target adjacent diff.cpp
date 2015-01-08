//  Give an integer array, adjust each integers so that the difference of every
//  adjacent integers are not greater than a given number target.If the array
//  before adjustment is A, the array after adjustment is B, you should minimize
//  the sum of abs(A[i] - B[i])
//  
//  You can assume each number in the array is a positive integer and not
//  greater than 100. The elements in the adjusted array should also be
//  not greater than 100.
//  
//  Example:
//  
//  Given[1, 4, 2, 3] and target = 1, one of the solutions is[2, 3, 2, 3] or [1, 2, 2, 3], 
//  the adjustment cost is 2 and it's minimal. Return 2.

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_NUMBER  100

class Solution {
public:
    int getMinimumAdjust(int *arr, int n, int targetMaxDiff) {
        static int result1[MAX_NUMBER + 1], result2[MAX_NUMBER + 1];
        if (n < 2)
            return 0;

        int *prevResult = &result1[0], *curResult = &result2[0];

        //Initialize with the last element of array
        for (int i = 0; i <= MAX_NUMBER; ++i)
            prevResult[i] = abs(arr[n - 1] - i);
    
        // Run DP
        int minK = 0, maxK = 0, curDiff = INT_MAX;
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= MAX_NUMBER; ++j) {
                minK = max(0, j - targetMaxDiff);
                maxK = min(MAX_NUMBER, j + targetMaxDiff);
                curResult[j] = INT_MAX;

                for (int k = minK; k <= maxK; ++k)
                    curResult[j] = min(curResult[j], abs(j - arr[i]) + prevResult[k]);
            }

            swap(prevResult, curResult);
        }

        curDiff = INT_MAX;
        for (int i = 0; i <= MAX_NUMBER; ++i)
            curDiff = min(curDiff, prevResult[i]);
        return curDiff;
    }
};

int main() {
    Solution so;

    int arr1[] = {8, 4, 6, 3};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int target = 2;

    cout << "Min Cost of arr1 is " << so.getMinimumAdjust(arr1, n, target) << endl;

    return 0;
}