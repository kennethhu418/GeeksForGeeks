// The longest Increasing Subsequence(LIS) problem is to find the length of the longest subsequence
// of a given sequence such that all elements of the subsequence are sorted in increasing order.
// For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is
// { 10, 22, 33, 50, 60, 80 }.

#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int search(const vector<int> &arr, const vector<int> &tailIndexArr, int target) {
    int start = 0, end = tailIndexArr.size() - 1, mid = -1;
    while (start < end) {
        mid = ((start + end) >> 1);
        if (arr[tailIndexArr[mid]] == target)
            return -1;
        if (target > arr[tailIndexArr[mid]])
            start = mid + 1;
        else
            end = mid - 1;
    }

    if (start > end)    return start;
    if (arr[tailIndexArr[start]] == target) return -1;
    return arr[tailIndexArr[start]] > target ? start : start + 1;
}

vector<int> LIS(const vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return arr;
    
    vector<int> parentIndexArr(n, -1);
    vector<int> tailIndexArr(1, 0);
    int     insertPos = -1;

    for (int i = 1; i < n; ++i) {
        insertPos = search(arr, tailIndexArr, arr[i]);
        if (insertPos < 0) continue;
        if (insertPos == tailIndexArr.size()) {
            parentIndexArr[i] = tailIndexArr.back();
            tailIndexArr.push_back(i);
        }
        else{
            parentIndexArr[i] = (insertPos == 0 ? -1 : tailIndexArr[insertPos - 1]);
            tailIndexArr[insertPos] = i;
        }
    }
   
    vector<int> result(tailIndexArr.size(), 0);
    int curPos = tailIndexArr.back();  insertPos = tailIndexArr.size() - 1;
    while (curPos >= 0) {
        result[insertPos--] = arr[curPos];
        curPos = parentIndexArr[curPos];
    }
    return result;
}


/************** TESTS CODES BELOW ****************************/
int LIS_Count(const vector<int> &arr) {
    int n = arr.size();
    if (n < 2) return n;
    vector<int> resultArr(n, 0);
    resultArr[n - 1] = 1;
    int maxLen = 1;
    for (int i = n - 2; i >= 0; --i) {
        resultArr[i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[i] && (1 + resultArr[j]) > resultArr[i])
                resultArr[i] = 1 + resultArr[j];
        }
        if (maxLen < resultArr[i])
            maxLen = resultArr[i];
    }
    return maxLen;
}

void generateArray(vector<int> &arr, int MAX_VAL) {
    unordered_set<int>  usedArr;
    for (int i = 0; i < arr.size();) {
        arr[i] = 1 + rand() % MAX_VAL;
        if (usedArr.find(arr[i]) == usedArr.end())
            usedArr.insert(arr[i++]);
    }
}

bool validate(const vector<int> &orgArr, const vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] >= arr[i + 1]) return false;
    }

    unordered_map<int, int> mapA;
    for (int i = 0; i < orgArr.size(); ++i)
        mapA[orgArr[i]] = i;

    vector<int> indexArr(arr.size(), -1);
    for (int i = 0; i < n; ++i)
        indexArr[i] = mapA[arr[i]];

    for (int i = 0; i < n - 1; ++i) {
        if (indexArr[i] >= indexArr[i + 1]) return false;
    }
    return true;
}

int main() {
    const int MAX_VAL = 100000;
    const int MAX_SIZE = 2000;
    vector<int> dataArr;
    vector<int> result;
    int n = 0;
    int tryTimes = 10000;

    srand(time(NULL));

    while (tryTimes-- > 0) {
        cout << tryTimes << endl;
        n = 1 + rand() % MAX_SIZE;
        dataArr.resize(n);
        generateArray(dataArr, MAX_VAL);

        result = LIS(dataArr);
        n = LIS_Count(dataArr);
        if (result.size() != n) {
            cerr << "Mismatch Size." << endl;
            system("PAUSE");
        }
        if (!validate(dataArr, result)) {
            cerr << "Non Increasing Sequence." << endl;
            system("PAUSE");
        }
    }
    return 0;
}