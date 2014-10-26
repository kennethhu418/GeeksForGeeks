//Given a matrix (which is represented by a 1D array whose size is rowSize*colSize), write an algorithm to rotate the matrix by clockwise 90 degree and the algorithm
//should be a in-place algorithm

#include <iostream>
using namespace std;

class Solution
{
private:
    int m;
    int n;
    int incBase;

    void Initialize(int *matrix, int m, int n){
        this->m = m; this->n = n;
        incBase = matrix[0];
        int endIndex = m * n;
        for (int i = 0; i < endIndex; ++i) {
            if (matrix[i] > incBase) incBase = matrix[i];
        }
        ++incBase;
    }

    void rotateRound(int *matrix, int x, int y) {
        int orgIndex = x * n + y, r1 = 0, r2 = 0;
        int curVal = matrix[orgIndex], nextVal = 0;
        int curX = x, curY = y, nextX = 0, nextY = 0;
        while (true) {
            r1 = curX * n + curY;
            nextY = m - 1 - r1 / n; nextX = r1 - n * (r1 / n);
            r2 = nextX * m + nextY;

            nextVal = matrix[r2]; matrix[r2] = curVal + incBase;
            if (r2 == orgIndex) break;
            curX = r2 / n; curY = r2 - curX * n; curVal = nextVal;
        }
    }

public:
    void rotateMatrix(int * matrix, int m, int n) {
        if (m == 0 || n == 0) return;

        Initialize(matrix, m, n);
        int endIndex = m * n, curIndex = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j, ++curIndex) {
                if (matrix[curIndex] >= incBase) continue;
                rotateRound(matrix, i, j);
            }
        }
        for (int i = 0; i < endIndex; ++i)
            matrix[i] -= incBase;
    }
};


void OutputArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int matrixArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int m = 3, n = 5;
    Solution so;
    so.rotateMatrix(matrixArr, m, n);
    OutputArray(matrixArr, m * n);
    return 0;
}