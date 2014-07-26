// Quiz - Get Minimum Number for Multiply With Only 1 and 0.cpp : 定义控制台应用程序的入口点。
//

/************************************************************************************
 * 给定正整数M (M > 1)，求最小的正整数N，使得N * M的十进制表示中只由0与1构成
 ************************************************************************************/

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <time.h>
using namespace std;

typedef unordered_map<unsigned __int64, unsigned __int64>::iterator pmap;

inline bool checkResult(unsigned __int64 n)
{
    if (n == 0) return false;

    unsigned int r = 0;
    while (n)
    {
        r = n % 10;
        if (r > 1)  return false;
        n /= 10;
    }

    return true;
}

class Solution
{
public:
    unsigned __int64 getMinNWithMul(unsigned __int64 M)
    {
        unordered_map<unsigned __int64, unsigned __int64> residuleMap;
        vector<unsigned __int64>    tempResidule;
        vector<unsigned __int64>    tempNumber;

        unsigned __int64 base = 1, curResidule = 0, newResidule = 0;
        residuleMap[0] = 0;
        residuleMap[1] = 1;

        while (true)
        {
            base *= 10;

            curResidule = base % M;
            if (curResidule == 0)   return base / M;

            if (residuleMap.find(M - curResidule) != residuleMap.end())
                return (base + residuleMap[M - curResidule]) / M;
            
            for (pmap iter = residuleMap.begin(); iter != residuleMap.end(); ++iter)
            {
                newResidule = (iter->first + curResidule) % M;
                if (residuleMap.find(newResidule) == residuleMap.end())
                {
                    tempResidule.push_back(newResidule);
                    tempNumber.push_back(base + iter->second);
                }
            }

            for (int i = 0; i < tempResidule.size(); i++)
                residuleMap[tempResidule[i]] = tempNumber[i];
            tempResidule.clear(); tempNumber.clear();
        }

        return 0;
    }
};

class Solution_BruteForce
{
public:
    unsigned __int64 getMinNWithMul(unsigned __int64 M)
    {
        unsigned __int64    N = 1;
        while (true)
        {
            if (checkResult(N * M))
                return N;
            ++N;
        }
        return 0;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    const   unsigned __int64 MAX_M = 1000;
    unsigned __int64 M = 0, N = 0, N2 = 0, mulRes = 0;
    unsigned    int tryTimes = 60;
    Solution so;
    Solution_BruteForce so_brute;

    srand(time(0));

    while (tryTimes-- > 0)
    {
        M = 2 + rand() % (MAX_M - 3);
        N = so.getMinNWithMul(M);
        N2 = so_brute.getMinNWithMul(M);
        if (!checkResult(N * M) || N != N2)
        {
            cout << "Oh. No! M = " << M << " N = " << N << " N2 = " << N2 <<endl;
            system("PAUSE");
        }
    }

	return 0;
}

