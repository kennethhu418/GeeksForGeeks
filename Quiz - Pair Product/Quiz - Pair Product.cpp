//Given an integer array and a constant number X, print all pair of number in the array whose product is equal to X.
//follow ups : how will you do in O(n) ? how will you handle duplicate pairs ?

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

static bool compareabs(const int &a, const int &b) {
    return abs(a) < abs(b);
}

vector<int> searchPairProduct(int arr[], int n, int target) {
    vector<int>	result;
    if (n < 2) return result;

    if (target == 0) {
        int i = 0;
        for (; i < n; ++i) {
            if (arr[i] == 0) break;
        }
        if (i < n) {
            result.push_back(0);
            result.push_back(i == 0 ? arr[1] : arr[0]);
        }
        return result;
    }

    if (target > 0) {
        sort(arr, arr + n);

        int negStart = 0, posStart = 0;
        while (negStart < n && arr[negStart] < 0) ++negStart;
        --negStart; 	posStart = negStart + 1;
        while (posStart < n && arr[posStart] == 0) ++posStart;

        int start = negStart, end = 0, mulVal = 0;
        while (end < start) {
            mulVal = arr[start] * arr[end];
            if (mulVal == target) {
                result.push_back(arr[start]);
                result.push_back(arr[end]);
                return result;
            }
            else if (mulVal > target) ++end;
            else --start;
        }
        start = posStart; end = n - 1;
        while (start < end) {
            mulVal = arr[start] * arr[end];
            if (mulVal == target) {
                result.push_back(arr[start]);
                result.push_back(arr[end]);
                return result;
            }
            else if (mulVal > target) --end;
            else ++start;
        }
        return result;
    }

    sort(arr, arr + n, compareabs);
    int start = 0, end = n - 1, mulVal = 0;
    while (start < n && arr[start] == 0) ++start;
    while (start < end) {
        mulVal = arr[start] * arr[end];
        if (abs(mulVal) == -target) {
            if (mulVal < 0){
                result.push_back(arr[start]); result.push_back(arr[end]);
                return result;
            }
            else  {
                ++start; --end;
            }
        }
        else if (abs(mulVal) < -target) ++start;
        else --end;
    }
    return result;
}

int main() {
    int arr[] = { -12, -8, -7, -3, -1, 0, 0, -3, -1, 1, 3, 0, 7, 9, 10, 12 };
    int n = sizeof(arr) / sizeof(int);
    int tempArr[30] = { 0 };
    int target[] = { 56, -56, -7, 0, 63, 12, 16, 14, -63 };
    int targetCount = sizeof(target) / sizeof(int);
    vector<int> result;

    for (int i = 0; i < targetCount; ++i) {
        memmove(tempArr, arr, sizeof(arr));
        result = searchPairProduct(tempArr, n, target[i]);
        cout << "Result for target " << target[i] << " : ";
        if (result.size())
            cout << result[0] << ", " << result[1] << endl;
        else
            cout << "none" << endl;
    }

    return 0;
}