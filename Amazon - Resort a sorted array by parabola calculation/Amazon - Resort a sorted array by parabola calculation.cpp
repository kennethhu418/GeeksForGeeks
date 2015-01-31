// Given a sorted array, output a new array where the original array elements are rearranged
// based on ax^2 + bx + c

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Solution {
public:
    vector<int> sortByTransform(const vector<int>  &arr, int a, int b, int c) {
        if (arr.size() < 2) return arr;
        vector<int> result;
        if (a == 0) {
            if (b >= 0) return arr;
            result = arr;
            reverse(result);
            return result;
        }

        double bk = -b / (2.0 * a);
        int start = 0, end = search(arr, bk);
        start = end - 1; bk = -bk;
        while (start >= 0 && end < arr.size()) {
            if (abs(arr[start] + bk) < abs(arr[end] + bk))
                result.push_back(arr[start--]);
            else
                result.push_back(arr[end++]);
        }
        while (start >= 0) result.push_back(arr[start--]);
        while (end < arr.size()) result.push_back(arr[end++]);
        if (a < 0)
            reverse(result);
        return result;
    }

private:
    void reverse(vector<int> &arr) {
        int start = 0, end = arr.size() - 1;
        while (start < end)
            swap(arr[start++], arr[end--]);
    }

    int search(const vector<int> &arr, double target) {
        if (arr.size() == 0)    return 0;
        int start = 0, end = arr.size() - 1, mid = 0;
        while (start < end) {
            mid = ((start + end) >> 1);
            if (target >= arr[mid])
                start = mid + 1;
            else
                end = mid - 1;
        }

        if (start > end || target < arr[start]) return start;
        return start + 1;
    }
};

class Verifier {
public:
    bool verify(const vector<int> &arr, int a, int b, int c) {
        for (int i = 0; i < arr.size() - 1; ++i) {
            if (transform(arr[i], a, b, c) > transform(arr[i + 1], a, b, c))
                return false;
        }
        return true;
    }

    void generateArray(vector<int> &arr, int MAX_VAL) {
        for (int i = 0; i < arr.size(); ++i) {
            arr[i] = rand() % MAX_VAL;
            if (rand() % 5 < 2)
                arr[i] = -arr[i];
        }
    }

private:
    int transform(int num, int a, int b, int c) {
        return a * num * num + b * num + c;
    }
};

int main() {
    int a = 0, b = 0, c = 0;
    const int MAX_COEFF = 90;
    const int MAX_VAL = 10000;
    const int MAX_N = 500;
    const int MAX_TRY = 1000;

    vector<int>     dataArr;
    vector<int>     resultArr;
    Solution so;
    Verifier  v;
    int n = 0;
    int tryTimes = 0;

    srand(time(NULL));
    while (tryTimes++ < MAX_TRY) {
        cout << tryTimes << endl;
        n = 1 + rand() % MAX_N;
        a = rand() % MAX_COEFF;
        b = rand() % MAX_COEFF;
        c = rand() % MAX_COEFF;
        if (rand() % 7 < 3)
            a = -a;
        if (rand() % 7 < 3)
            b = -b;
        if (rand() % 7 < 3)
            c = -c;

        dataArr.resize(n);
        v.generateArray(dataArr, MAX_VAL);

        resultArr = so.sortByTransform(dataArr, a, b, c);
        v.verify(resultArr, a, b, c);
        cout << "----------------------------------" << endl;
    }
    return 0;
}