//Given two positive integers n and k, print all increasing sequences of length k such that the elements in every sequence are from first n natural numbers.
//
//Examples:
//
//Input : k = 2, n = 3
//Output : 
//         1 2
//         1 3
//         2 3
//
//Input : k = 5, n = 5
//Output : 1 2 3 4 5
//
//Input : k = 3, n = 5
//Output : 
//        1 2 3
//        1 2 4
//        1 2 5
//        1 3 4
//        1 3 5
//        1 4 5
//        2 3 4
//        2 3 5
//        2 4 5
//        3 4 5

#include <iostream>
using namespace std;

void print(const int *arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void printIncreasingNumbers(int n, int k) {
    if (k == 0) return;
    int *startNumArr = new int[k];
    for (int i = 0; i < k; ++i) startNumArr[i] = 1 + i;

    int curPos = k - 1;
    while (curPos >= 0) {
        print(startNumArr, k);
        while (curPos >= 0) {
            ++startNumArr[curPos];
            if (n - startNumArr[curPos] >= k - curPos - 1) {
                for (int i = 1; i <= k - curPos - 1; ++i)
                    startNumArr[curPos + i] = startNumArr[curPos] + i;
                curPos = k - 1; break;
            }
            else
                --curPos;
        }
    }
    delete[] startNumArr;
}

int main() {
    int n = 7, k = 3;
    printIncreasingNumbers(n, k);
    return 0;
}