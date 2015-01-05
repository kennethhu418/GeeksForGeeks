//  In "the 100 game," two players take turns adding, to a running
//  total, any integer from 1..10.The player who first causes the running
//  total to reach or exceed 100 wins.
//  What if we change the game so that players cannot re - use integers ?
//  For example, if two players might take turns drawing from a common pool of numbers
//  of 1..15 without replacement until they reach a total >= 100. This problem is
//  to write a program that determines which player would win with ideal play.
//  
//  Write a procedure, "Boolean canIWin(int maxChoosableInteger, int desiredTotal)",
//  which returns true if the first player to move can force a win with optimal play.
//  
//  Your priority should be programmer efficiency; don't focus on minimizing 
//  either space or time complexity.

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int getMax(int *dataArr, int n) {
    int maxVal = INT_MIN;
    for (int i = 0; i < n; ++i)
        maxVal = max(maxVal, dataArr[i]);
    return maxVal;
}

bool canIWin(int *dataArr, int n, int desiredTotal) {
    if (getMax(dataArr, n) >= desiredTotal)
        return true;

    for (int i = 0; i < n; ++i) {
        swap(dataArr[i], dataArr[n - 1]);
        if (!canIWin(dataArr, n - 1, desiredTotal - dataArr[n - 1])) {
            swap(dataArr[i], dataArr[n - 1]);
            return true;
        }
        swap(dataArr[i], dataArr[n - 1]);
    }
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    int *dataArr = new int[maxChoosableInteger];
    for (int i = 0; i < maxChoosableInteger; ++i)
        dataArr[i] = i + 1;

    bool canWin = canIWin(dataArr, maxChoosableInteger, desiredTotal);
    delete[] dataArr;
    return canWin;
}

int main() {
    int target = 100;
    for (int i = 14; i < 21; ++i) {
        cout << "When max choosable number is " << i << " and target sum is " << target << endl;
        if (canIWin(i, target))
            cout << "I can win!" << endl << endl;
        else
            cout << "I cannot win!" << endl << endl;
    }
    return 0;
}