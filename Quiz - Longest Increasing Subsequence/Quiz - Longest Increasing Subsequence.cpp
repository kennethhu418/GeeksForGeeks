#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

int search(const vector<int> &arr, int n, int target) {
    int start = 0, end = n - 1, mid = 0;
    while (start < end) {
        mid = ((start + end) >> 1);
        if (target >= arr[mid]) start = mid + 1;
        else end = mid - 1;
    }
    if (start > end || target < arr[start]) return start;
    return start + 1;
}

vector<int> calculateLongestSubSequence(const vector<int> &arr) {
    int n = arr.size(); vector<int> result;
    if (n == 0) return result;

    vector<int> seqTailArr(n);
    int L = 0, insertPos = 0;
    for (int i = 0; i < n; ++i) {
        insertPos = search(seqTailArr, L, arr[i]);
        seqTailArr[insertPos] = arr[i];
        if (insertPos >= L) {
            assert(L == insertPos);
            ++L;
        }
    }

    //Construct the sequence from tail Arr
    for (int i = 0; i < L; ++i) result.push_back(seqTailArr[i]);
    return result;
}

int main() {
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
    int n = sizeof(arr) / sizeof(int);
    vector<int> dataArr(arr, arr + n);
    vector<int> result = calculateLongestSubSequence(dataArr);
    for (int i = 0; i < result.size(); ++i) {
        cout << result.at(i) << " ";
    }
    cout << endl;
    return 0;
}