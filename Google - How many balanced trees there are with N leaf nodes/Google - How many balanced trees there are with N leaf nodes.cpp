// How many balanced binary tree there are with n leaf nodes? Prove and write codes.
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// DP Solution with brute force search
long long getBalancedTreeCount(int n) {
    if (n < 3)
        return n == 2 ? 2 : 1;

    vector<vector<long long>> resultArr(n + 1, vector<long long>(n + 1, 0));

    //Initialize DP
    resultArr[0][0] = resultArr[1][1] = 1;

    //Run DP
    for (int i = 2; i <= n; ++i) {
        for (int h = 2; h <= i; ++h) {
            for (int j = 0; j < i; ++j)
                resultArr[i][h] += resultArr[j][h - 1] * resultArr[i - 1 - j][h - 1] + resultArr[j][h - 2] * resultArr[i - 1 - j][h - 1] + resultArr[j][h - 1] * resultArr[i - 1 - j][h - 2];
        }
    }

    long long result = 0;
    for (int h = 2; h <= n; ++h)
        result += resultArr[n][h];

    return result;
}

// DP Solution with optimized search
long long getBalancedTreeCount_Optimized(int n) {
    if (n < 3)
        return n == 2 ? 2 : 1;

    vector<vector<long long>> resultArr(n + 1, vector<long long>(log2((long)n) + 3, 0));

    //Initialize DP
    resultArr[0][0] = resultArr[1][1] = 1;

    //Run DP
    int lowestHeight = 0;
    int highestHeight = 0;
    for (int i = 2; i <= n; ++i) {
        lowestHeight = log2((long)i) + 1;
        highestHeight = log2((long)i) + 2;
        for (int h = lowestHeight; h <= highestHeight; ++h) {
            for (int j = 0; j < i; ++j)
                resultArr[i][h] += resultArr[j][h - 1] * resultArr[i - 1 - j][h - 1] + resultArr[j][h - 2] * resultArr[i - 1 - j][h - 1] + resultArr[j][h - 1] * resultArr[i - 1 - j][h - 2];
        }    
    }

    return resultArr[n][log2((long)n) + 1] + resultArr[n][log2((long)n) + 2];
}





int main() {
    for (int i = 1; i < 20; ++i) {
        cout << "There are " << getBalancedTreeCount(i) << " balanced trees with " << i << " nodes" << endl;
        cout << "There are " << getBalancedTreeCount_Optimized(i) << " balanced trees with " << i << " nodes" << endl;
        cout << endl;
    }
    return 0;
}