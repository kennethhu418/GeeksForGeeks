// Quiz - Square of Float Number.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
using namespace std;

#define SAME_DIFF_THRESHOLD 0.0000001

double square(double n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    double start = 0, end = n, mid = 0, res = 0;
    if (n < 1) { start = n; end = 1; } // ====================PAY ATTENTION HERE====================
    while (end - start > SAME_DIFF_THRESHOLD) {
        mid = (start + end) / 2; res = mid * mid;
        if (-SAME_DIFF_THRESHOLD < res - n && res - n < SAME_DIFF_THRESHOLD) return mid;
        if (res > n) end = mid;
        else start = mid;
    }
    return start;
}

int main() {
    double n = 0;
    while (cin >> n)
        cout << "sqrt(" << n << ") = " << square(n) << endl;
    return 0;
}