// Quiz - Equally divide cards.cpp : 定义控制台应用程序的入口点。

//  题目来源: http://codevs.cn/problem/1098/
//  有 N 堆纸牌，编号分别为 1，2，…, N。每堆上有若干张，但纸牌总数必为 N 的倍数。可以在任一堆上取若于张纸牌，然后移动。
//  移牌规则为：在编号为 1 堆上取的纸牌，只能移到编号为 2 的堆上；在编号为 N 的堆上取的纸牌，只能移到编号为 N - 1 的堆上；
//  其他堆上取的纸牌，可以移到相邻左边或右边的堆上。
//  现在要求找出一种移动方法，用最少的移动次数使每堆上纸牌数都一样多。
//  
//  例如 N = 4，4 堆纸牌数分别为：
//  ①　9　②　8　③　17　④　6
//  移动3次可达到目的：
//  从 ③ 取 4 张牌放到 ④ （9 8 13 10）->从 ③ 取 3 张牌放到 ②（9 11 10 10）->从 ② 取 1 张牌放到①（10 10 10 10）。


//  思路：
//  先算出均分情况下每个堆上应有的牌数K。
//  然后从头至尾遍历每一个堆，算出
//  a)到当前堆为止总的牌数count_actual
//  b)在均分的情况下到当前堆为止的牌数count_ideal
//  如果count_actual < count_ideal, 则继续遍历下一个堆
//  如果count_actual == count_ideal，则从当前堆开始向前回溯每个堆并移动多余的牌至前一个堆
//  如果count_actual > count_ideal，则首先从当前堆移动出(count_actual - count_ideal)个数的牌给下一个堆，
//  然后从当前堆开始向前回溯每个堆并移动多余的牌至前一个堆

#include <iostream>
#include <assert.h>
using namespace std;

int getMinMoveTimes(int * arr, int n)
{
    if (n < 2)	return 0;
    int avgCount = 0;
    for (int i = 0; i < n; ++i)
        avgCount += arr[i];
    assert(avgCount % n == 0);
    avgCount /= n;

    int curSum = 0, curTargetSum = 0, movedTimes = 0, j = 0;
    for (int i = 0; i < n; ++i){
        curSum += arr[i]; curTargetSum += avgCount;
        if (curSum < curTargetSum) continue;
        if (curSum >= curTargetSum) {
            if (curSum > curTargetSum){
                arr[i + 1] += (curSum - curTargetSum);
                ++movedTimes;
                arr[i] -= (curSum - curTargetSum);
            }

            j = i;
            while (true){
                if (arr[j] == avgCount) break;
                assert(arr[j] > avgCount);
                arr[j - 1] += (arr[j] - avgCount);
                arr[j] = avgCount;
                ++movedTimes;
                --j;
            }

            curSum = 0;
            curTargetSum = 0;
        }
    }

    return movedTimes;
}

int main() {
    int arr[] = {9, 8, 17, 6};
    cout << "Moving times is " << getMinMoveTimes(arr, sizeof(arr) / sizeof(arr[0])) << endl;
    return 0;
}