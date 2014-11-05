// Given an array whose size is n and whose elements are in range [0, n), find all duplicate numbers in the array and output them. The output should contain no dulicate elements
// For example, the given array is {4, 1, 3, 3, 2, 0}, the output should be { 3 }

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <assert.h>
using namespace std;

vector<int> searchDuplicateElements(vector<int> &arr, int n) {
    vector<int>	resultArr;
    if (n < 2) return resultArr;

    int curPos = 0, curVal = 0;
    while (curPos < n) {
        curVal = arr[curPos];
        if (curVal >= n) { ++curPos; continue; }
        if (curVal == curPos) { arr[curPos++] += n; continue; }
        else if (curVal < curPos) {
            if (arr[curVal] < 2 * n) {
                if (arr[curVal] >= n) arr[curVal] += n;
                else arr[curVal] = n + curVal;
            }
            ++curPos;
        }
        else {
            if (arr[curVal] < 2 * n) {
                if (arr[curVal] >= n) arr[curVal] += n;
                else {
                    swap(arr[curVal], arr[curPos]);
                    arr[curVal] = n + curVal;
                    continue;
                }
            }
            ++curPos;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (arr[i] < n) continue;
        if (arr[i] < 2 * n) { arr[i] -= n; continue; }
        arr[i] -= 2 * n;
        resultArr.push_back(arr[i]);
    }
    return resultArr;
}

/************************************************************************
*                       Test Codes Below
* *********************************************************************/

vector<int> searchDuplicateElements_map(const vector<int> &arr, int n) {
    vector<int>	resultArr;
    unordered_map<int, int> mapA;
    for (int i = 0; i < n; ++i) {
        mapA[arr[i]]++;
        if (mapA[arr[i]] == 2) resultArr.push_back(arr[i]);
    }
    return resultArr;
}

void generateArray(vector<int> &arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % n;
}

bool compare(vector<int> &arr1, vector<int> &arr2) {
    if (arr1.size() != arr2.size()) return false;
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    for (int i = 0; i < arr1.size(); ++i) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

void debug_print(const vector<int> &arr, int n) {
    for (int i = 0; i < arr.size(); ++i) cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    const int MAX_SIZE = 1200;
    vector<int> arr(MAX_SIZE);
    int n;
    int tryTimes = 30;

    srand(time(0));

    vector<int> result1, result2;
    while (tryTimes-- > 0) {
        n = 1 + rand() % MAX_SIZE;
        generateArray(arr, n);
        debug_print(arr, n);
        result2 = searchDuplicateElements_map(arr, n);
        result1 = searchDuplicateElements(arr, n);
        assert(compare(result1, result2));
        debug_print(result1, result1.size());
        cout << "=============================================" << endl << endl;
    }
    return 0;
}