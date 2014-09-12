// Quiz - Interceptor Missile.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
����:T-Dog
��Ŀ:p1044 ���ص���
����:http://codevs.cn/problem/1044/
*/

//  ĳ��Ϊ�˷����й��ĵ���Ϯ������չ��һ�ֵ�������ϵͳ���������ֵ�������ϵͳ��һ��ȱ�ݣ���Ȼ���ĵ�һ���ڵ��ܹ���������ĸ߶ȣ�
//  �����Ժ�ÿһ���ڵ������ܸ���ǰһ���ĸ߶ȡ�ĳ�죬�״ﲶ׽���й��ĵ�����Ϯ�����ڸ�ϵͳ�������ý׶Σ�����ֻ��һ��ϵͳ��
//  ����п��ܲ����������еĵ�����
//  �������뵼�����η����ĸ߶�(�����ĵ����ĸ������ᳬ��20��)���������
//  (1) ����ϵͳ��������ض��ٵ���
//  (2) ���Ҫ�������е�������Ҫ�䱸���������ֵ�������ϵͳ

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