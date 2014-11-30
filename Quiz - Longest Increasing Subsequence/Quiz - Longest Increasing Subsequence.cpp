// The longest Increasing Subsequence(LIS) problem is to find the length of the longest subsequence
// of a given sequence such that all elements of the subsequence are sorted in increasing order.
// For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is
// { 10, 22, 33, 50, 60, 80 }.

#include <iostream>
#include <vector>
using namespace std;

int search(const vector<int> &arr, const vector<int> &indiceArr, int target) {
    int mid = 0, start = 0, end = indiceArr.size() - 1;
    while (start < end) {
        mid = ((start + end) >> 1);
        if (target <= arr[indiceArr[mid]])
            end = mid - 1;
        else
            start = mid + 1;
    }
    if (start > end || target <= arr[indiceArr[start]]) return start;
    return start + 1;
}

vector<int> LIS(vector<int> &arr) {
    int n = arr.size();
    vector<int> resultArr;
    if (n == 0) return resultArr;

    vector<int> tailIndiceArr(1);
    vector<int> prevIndiceArr(n);
    prevIndiceArr[0] = -1;
    tailIndiceArr[0] = 0;
    int curTailLen = 1, insertPos = 0;

    for (int i = 1; i < n; ++i) {
        insertPos = search(arr, tailIndiceArr, arr[i]);
        if (insertPos == tailIndiceArr.size())
            tailIndiceArr.push_back(i);
        else
            tailIndiceArr[insertPos] = i;
        if (insertPos == 0)
            prevIndiceArr[i] = -1;
        else
            prevIndiceArr[i] = tailIndiceArr[insertPos - 1];
    }

    int curPos = tailIndiceArr[tailIndiceArr.size() - 1];
    while (curPos >= 0) {
        resultArr.push_back(arr[curPos]);
        curPos = prevIndiceArr[curPos];
    }

    int start = 0, end = resultArr.size() - 1;
    while (start < end)
        swap(resultArr[start++], resultArr[end--]);

    return resultArr;
}

int main()
{
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
    vector<int> dataArr(arr, arr + sizeof(arr) / sizeof(int));
    vector<int> result = LIS(dataArr);
    for (int i = 0; i < result.size(); ++i)
        cout << result[i] << " ";
    cout << endl;
    return 0;
}