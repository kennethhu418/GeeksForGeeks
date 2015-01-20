// The longest Increasing Subsequence(LIS) problem is to find the length of the longest subsequence
// of a given sequence such that all elements of the subsequence are sorted in increasing order.
// For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is
// { 10, 22, 33, 50, 60, 80 }.

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

//int search(const vector<int> &arr, const vector<int> &indiceArr, int target) {
//    int mid = 0, start = 0, end = indiceArr.size() - 1;
//    while (start < end) {
//        mid = ((start + end) >> 1);
//        if (target <= arr[indiceArr[mid]])
//            end = mid - 1;
//        else
//            start = mid + 1;
//    }
//    if (start > end || target <= arr[indiceArr[start]]) return start;
//    return start + 1;
//}

//vector<int> LIS(vector<int> &arr) {
//    int n = arr.size();
//    vector<int> resultArr;
//    if (n == 0) return resultArr;
//
//    vector<int> tailIndiceArr(1);
//    vector<int> prevIndiceArr(n);
//    prevIndiceArr[0] = -1;
//    tailIndiceArr[0] = 0;
//    int curTailLen = 1, insertPos = 0;
//
//    for (int i = 1; i < n; ++i) {
//        insertPos = search(arr, tailIndiceArr, arr[i]);
//        if (insertPos == tailIndiceArr.size())
//            tailIndiceArr.push_back(i);
//        else
//            tailIndiceArr[insertPos] = i;
//        if (insertPos == 0)
//            prevIndiceArr[i] = -1;
//        else
//            prevIndiceArr[i] = tailIndiceArr[insertPos - 1];
//    }
//
//    int curPos = tailIndiceArr[tailIndiceArr.size() - 1];
//    while (curPos >= 0) {
//        resultArr.push_back(arr[curPos]);
//        curPos = prevIndiceArr[curPos];
//    }
//
//    int start = 0, end = resultArr.size() - 1;
//    while (start < end)
//        swap(resultArr[start++], resultArr[end--]);
//
//    return resultArr;
//}

int search(const vector<int> &arr, int target) {
    int start = 0, end = arr.size() - 1, mid = 0;
    while (start < end) {
        mid = ((start + end) >> 1);
        if (target == arr[mid])
            return -1;
        if (target >= arr[mid])
            start = mid + 1;
        else
            end = mid - 1;
    }
    if (start > end || arr[start] > target) return start;
    if (arr[start] == target) return -1;
    return start + 1;
}

vector<int> LIS(const vector<int> &arr) {
    int n = arr.size();
    vector<int> resultArr;
    if (n == 0) return resultArr;

    vector<int> tailArr(1, arr[0]);
    int insertPos = 0;
    for (int i = 1; i < n; ++i) {
        insertPos = search(tailArr, arr[i]);
        if (insertPos < 0) continue;
        if (insertPos == tailArr.size())
            tailArr.push_back(arr[i]);
        else
            tailArr[insertPos] = arr[i];
    }

    return tailArr;
}

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
    for (int i = 0; i < arr.size(); ++i)
        arr[i] = 1 + rand() % MAX_VAL;
}

bool validate(const vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] >= arr[i + 1]) return false;
    }
    return true;
}

int main() {
    const int MAX_VAL = 10000;
    const int MAX_SIZE = 2000;
    vector<int> dataArr;
    vector<int> result;
    int n = 0;
    int tryTimes = 100000;

    srand(time(NULL));

    while (tryTimes-- > 0) {
        n = 1 + rand() % MAX_SIZE;
        dataArr.resize(n);
        generateArray(dataArr, MAX_VAL);

        result = LIS(dataArr);
        n = LIS_Count(dataArr);
        if (result.size() != n) {
            cerr << "Mismatch Size." << endl;
            system("PAUSE");
        }
        if (!validate(result)) {
            cerr << "Non Increasing Sequence." << endl;
            system("PAUSE");
        }
    }
    return 0;
}

//int main()
//{
//    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
//    vector<int> dataArr(arr, arr + sizeof(arr) / sizeof(int));
//    vector<int> result = LIS(dataArr);
//    for (int i = 0; i < result.size(); ++i)
//        cout << result[i] << " ";
//    cout << endl;
//    return 0;
//}