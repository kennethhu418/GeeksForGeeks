//Given two arrays X[] and Y[] of positive integers, find number of pairs such that x^y > y^x where x is an element from X[] and y is an element from Y[].
//
//Examples:
//
//Input : X[] = { 2, 1, 6 }, Y = { 1, 5 }
//Output: 3
//    // There are total 3 pairs where pow(x, y) is greater than pow(y, x)
//    // Pairs are (2, 1), (2, 5) and (6, 1)
//
//
//Input : X[] = { 10, 19, 18 }, Y[] = { 11, 15, 9 };
//Output: 2
//    // There are total 2 pairs where pow(x, y) is greater than pow(y, x)
//    // Pairs are (10, 11) and (10, 15)


//Basic idea:
//If x^y > y^x, ylogx > xlogy
// For ylogx > xlogy, when y increases, this equation still holds
// For xlogy > ylogx, when x increases, this equation still holds
// The only exception is that x = 1 or 2 and y = 1 or 2.

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int getPairCount(int *arrX, int n1, int * arrY, int n2) {
    if (n1 == 0 || n2 == 0) return 0;
    sort(arrX, arrX + n1);
    sort(arrY, arrY + n2);

    int x1Count = 0, y1Count = 0, x2Count = 0, y2Count = 0;
    for (int i = 0; i < n1; ++i) {
        if (arrX[i] == 1) ++x1Count;
        else if (arrX[i] == 2) ++x2Count;
        else break;
    }
    for (int i = 0; i < n2; ++i) {
        if (arrY[i] == 1) ++y1Count;
        else if (arrY[i] == 2) ++y2Count;
        else break;
    }

    int totalPairs = (n1 - x1Count) * y1Count;
    for (int i = 0; i < n1; ++i) {
        if (2 * log2(arrX[i]) > arrX[i]) totalPairs += y2Count;
    }
    for (int i = y1Count + y2Count; i < n2; ++i) {
        if (arrY[i] > 2 * log2(arrY[i])) totalPairs += x2Count;
    }

    int xpos = x1Count + x2Count, ypos = y1Count + y2Count;
    while (xpos < n1 && ypos < n2) {
        if (arrY[ypos] * log2(arrX[xpos]) > arrX[xpos] * log2(arrY[ypos])) {
            totalPairs += n2 - ypos;
            ++xpos;
        }
        else
            ++ypos;
    }

    return totalPairs;
}

int main()
{
    int X[] = { 2, 1, 1, 6 }, Y[] = { 1, 5 , 6, 8, 2};
    cout << getPairCount(X, sizeof(X) / sizeof(int), Y, sizeof(Y) / sizeof(int)) << endl;
    return 0;
}