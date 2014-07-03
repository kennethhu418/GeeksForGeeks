// Quiz - Optimal Strategy for a game.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>

class Solution
{
public:
    int getMaxCoins(int coins[], int n)
    {
        if (n == 0) return 0;
        if (n == 2) return std::max(coins[0], coins[1]);

        AllocateMemory(n + 1);

        //Initialize
        for (int i = 0; i < n; i++)
        {
            resultArr[i][1] = coins[i];
            trackArr[i][1] = i;
        }

        for (int i = 0; i < n - 1; i++)
        {
            resultArr[i][2] = std::max(coins[i], coins[i+1]);
            trackArr[i][2] = coins[i] > coins[i + 1] ? i : (i + 1);
        }

        int curCoins = 0;
        //Run DP
        for (int k = 3; k <= n; k++)
        {
            for (int curStart = 0; curStart <= n - k; curStart++)
            {
                //first coin taken?
                curCoins = coins[curStart];
                if (trackArr[curStart + 1][k - 1] == curStart + 1)
                    curCoins += resultArr[curStart + 2][k - 2];
                else
                    curCoins += resultArr[curStart + 1][k - 2];
                resultArr[curStart][k] = curCoins;
                trackArr[curStart][k] = curStart;

                //last coin taken?
                curCoins = coins[curStart + k - 1];
                if (trackArr[curStart ][k - 1] == curStart)
                    curCoins += resultArr[curStart + 1][k - 2];
                else
                    curCoins += resultArr[curStart][k - 2];

                if (curCoins > resultArr[curStart][k])
                {
                    resultArr[curStart][k] = curCoins;
                    trackArr[curStart][k] = curStart + k - 1;
                }
            }
        }

        int maxCoins = resultArr[0][n];
        FreeMemory();
        return maxCoins;
    }

private:
    int **resultArr;
    int **trackArr;
    int     size;

    void AllocateMemory(int n)
    {
        resultArr = new int*[n];
        trackArr = new int*[n];
        for (int i = 0; i < n; i++)
        {
            resultArr[i] = new int[n];
            trackArr[i] = new int[n];
        }

        this->size = n;
    }

    void FreeMemory()
    {
        for (int i = 0; i < size; i++)
        {
            delete [] resultArr[i];
            delete [] trackArr[i];
        }

        delete[] resultArr;
        delete[] trackArr;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    int arr1[] = { 20, 30, 2, 2, 2, 10 };
    int n = sizeof(arr1) / sizeof(arr1[0]);

    using namespace std;

    Solution so;
    cout << so.getMaxCoins(arr1, n) << endl;

	return 0;
}