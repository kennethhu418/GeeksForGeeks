// Quiz - Interceptor Missile.cpp : 定义控制台应用程序的入口点。
//
/*
作者:T-Dog
题目:p1044 拦截导弹
链接:http://codevs.cn/problem/1044/
*/

//  某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度，
//  但是以后每一发炮弹都不能高于前一发的高度。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，
//  因此有可能不能拦截所有的导弹。
//  程序输入导弹依次飞来的高度(飞来的导弹的个数不会超过20个)，程序输出
//  (1) 这套系统最多能拦截多少导弹
//  (2) 如果要拦截所有导弹最少要配备多少套这种导弹拦截系统

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_COUNT 20

class Solution
{
public:
    int getLongestDecreasingSequence(const int *arr, int n)
    {
        if (n < 2)   return n;
        int * resultArr = new int[n];

        resultArr[n - 1] = 1;
        int maxLen = 1;
        for (int i = n - 2; i >= 0; --i){
            resultArr[i] = 1;
            for (int j = i + 1; j < n; j++){
                if (arr[j] <= arr[i])
                    resultArr[i] = max(resultArr[i], 1 + resultArr[j]);
            }
            if (resultArr[i] > maxLen) maxLen = resultArr[i];
        }

        delete[] resultArr;
        return maxLen;
    }

    int getMinDecreasingSeuqnceCount(int * arr, int n)
    {
        if (n < 2) return 1;

        int *trailingArr = new int[n];
        int  decSeqCount = 0;

        int curPos = 0, curLen = 0, minTrailingIndex = 0;
        while (curPos < n){
            curLen = getDecreasingLen(arr, n, curPos);
            minTrailingIndex = -1;
            for (int i = 0; i < decSeqCount; ++i){
                if (trailingArr[i] >= arr[curPos]){
                    if (minTrailingIndex == -1 || trailingArr[i] < trailingArr[minTrailingIndex])
                        minTrailingIndex = i;
                }
            }

            if (minTrailingIndex >= 0)
                trailingArr[minTrailingIndex] = arr[curPos + curLen - 1];
            else
                trailingArr[decSeqCount++] = arr[curPos + curLen - 1];

            curPos += curLen;
        }

        delete[] trailingArr;
        return decSeqCount;
    }

private:
    int getDecreasingLen(int * arr, int n, int start)
    {
        if (start >= n) return 0;
        int count = 1;
        while (start < n - 1 && arr[start] >= arr[start + 1]){
            ++start; ++count;
        }
        return count;
    }
};


//Test Sequence:  300 250 275 252 200 138 245
int main()
{
    int arr[MAX_COUNT];
    int n = 0, curNum = -1;
    while (cin >> curNum){
        arr[n++] = curNum;
    }

    Solution so;

    cout << so.getLongestDecreasingSequence(arr, n) << endl << so.getMinDecreasingSeuqnceCount(arr, n) << endl;
    return 0;
}