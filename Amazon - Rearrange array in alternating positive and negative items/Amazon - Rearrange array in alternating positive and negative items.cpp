// Given an array of positive and negative numbers, arrange them in an alternate fashion such that every positive number is followed by negative and vice-versa.
// No need to maintain the original item order.
#include <iostream>
#include <assert.h>
#include <unordered_map>
using namespace std;


class Solution {
public:
    void RearrangeArray(int *arr, int n) {
        if (n < 2) return;
        int nextPositive = getNext(arr, n, 0, true);
        int nextNegative = getNext(arr, n, 0, false);
        for (int i = 0; i < n && nextPositive < n && nextNegative < n; ++i) {
            if (i & 1) {
                swap(arr[i], arr[nextNegative]);
                nextNegative = getNext(arr, n, nextNegative + 1, false);
                nextPositive = getNext(arr, n, nextPositive, true);
            }
            else {
                swap(arr[i], arr[nextPositive]);
                nextPositive = getNext(arr, n, nextPositive + 1, true);
                nextNegative = getNext(arr, n, nextNegative, false);
            }
        }
    }

private:
    int getNext(int *arr, int n, int start, bool positive) {
        while (start < n) {
            if (positive && arr[start] >= 0) break;
            if (!positive && arr[start] < 0) break;
            ++start;
        }
        return start;
    }
};

/**************************** Tests Codes **********************************/

void generateArray(int *arr, int n, int MAX_VAL) {
    for (int i = 0; i < n; ++i) {
        arr[i] = 1 + rand() % MAX_VAL;
        if (rand() & 1)
            arr[i] = -arr[i];
    }
}

void Output(int *arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

bool checkArray(int *arr, int n) {    
    if (n < 2) return true;

    bool allNegative = false;
    int i = 0;
    for (i = 0; i < n - 1; ) {
        if (arr[i] >= 0 && arr[i + 1] < 0) {
            i += 2; continue;
        }
        if (arr[i] < 0 && arr[i + 1] >= 0)
            return false;
        break;
    }

    if (i < n && arr[i] < 0)
        allNegative = true;

    for (; i < n; ++i) {
        if (allNegative && arr[i] >= 0) return false;
        if (!allNegative && arr[i] < 0) return false;
    }

    return true;
}

bool checkComplementary(int *orgArr, int *curArr, int n) {
    unordered_map<int, int> mapA;
    for (int i = 0; i < n; ++i)
        mapA[orgArr[i]]++;

    for (int i = 0; i < n; ++i) {
        if (mapA.find(curArr[i]) == mapA.end()) return false;
        mapA[curArr[i]]--;
        if (mapA[curArr[i]] == 0)
            mapA.erase(curArr[i]);
    }

    return true;
}

int main() {
    const int MAX_N = 2000;
    const int MAX_VAL = 100000;
    int     orgArr[MAX_N];
    int     soArr[MAX_N];
    int     n = 0;
    int tryTimes = 10000;
    Solution so;

    while (tryTimes-- > 0) {
        n = 1 + rand() % MAX_N;
        generateArray(orgArr, n, MAX_VAL);
        memmove(soArr, orgArr, n * sizeof(int));

        so.RearrangeArray(soArr, n);

        assert(checkComplementary(orgArr, soArr, n));
        assert(checkArray(soArr, n));
    }
    return 0;
}