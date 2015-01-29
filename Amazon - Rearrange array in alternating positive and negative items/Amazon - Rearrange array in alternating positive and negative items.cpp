// Given an array of positive and negative numbers, arrange them in an alternate fashion such that every positive number is followed by negative and vice-versa.
// No need to maintain the original item order.
#include <iostream>
#include <assert.h>
#include <unordered_map>
using namespace std;

void reArrangeArray(int *arr, int n) {
    if (n < 2)	return;
    int start = 0, end = n - 1;
    while (start < end) {
        while (start < end && arr[start] >= 0)
            ++start;
        if (start == end) break;
        while (start < end && arr[end] < 0)
            --end;
        if (start == end) break;
        swap(arr[start++], arr[end]);
    }
    int positiveStart = 0, negativeStart = start;
    if (arr[start] >= 0) ++negativeStart;
    int curExpectedNegPos = 1;
    while (negativeStart < n && curExpectedNegPos < negativeStart) {
        swap(arr[curExpectedNegPos], arr[negativeStart++]);
        curExpectedNegPos += 2;
    }
}

void generateArray(int *arr, int n, int MAX_VAL) {
    bool negativeMore = (rand() & 1);
    int curNum = 0;
    for (int i = 0; i < n; ++i) {
        curNum = 1 + rand() % MAX_VAL;
        if (rand() % 3 == 0)
            arr[i] = negativeMore ? curNum : -curNum;
        else
            arr[i] = negativeMore ? -curNum : curNum;
    }
}

bool validate(int *arr, int n) {
    if (n < 2)	return true;
    int curPos = 0;
    bool shouldBeNegative = false;
    while (curPos < n) {
        if (curPos & 1) {
            if (arr[curPos] < 0) ++curPos;
            else break;
        }
        else {
            if (arr[curPos] >= 0) ++curPos;
            else {
                shouldBeNegative = true;
                break;
            }
        }
    }

    while (curPos < n) {
        if ((shouldBeNegative && arr[curPos] >= 0)
            || (!shouldBeNegative && arr[curPos] < 0))
            return false;
        ++curPos;
    }
    return true;
}

bool validate2(const int *arr1, const int *arr2, int n) {
    unordered_map<int, int>	mapA;
    unordered_map<int, int>	mapA2;
    for (int i = 0; i < n; ++i)
        mapA[arr1[i]]++;
    for (int i = 0; i < n; ++i) {
        if (mapA.find(arr2[i]) == mapA.end())
            return false;
        mapA2[arr2[i]]++;
        if (mapA2[arr2[i]] > mapA[arr2[i]])
            return false;
    }
    return true;
}

int main() {
    const int MAX_SIZE = 500;
    const int MAX_VAL = 10000;
    const int MAX_TRIES = 10000;
    int	arr[MAX_SIZE];
    int    testArr[MAX_SIZE];
    int 	n;
    int	tryTimes = 0;
    while (tryTimes++ < MAX_TRIES) {
        cout << tryTimes << endl;
        if (tryTimes == 38)
            cout << endl;
        n = 1 + rand() % MAX_SIZE;
        generateArray(arr, n, MAX_VAL);
        memmove(testArr, arr, n * sizeof(int));

        reArrangeArray(testArr, n);

        assert(validate(testArr, n));
        assert(validate2(arr, testArr, n));
    }
    return 0;
}