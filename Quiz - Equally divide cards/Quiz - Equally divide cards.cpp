// Quiz - Equally divide cards.cpp : �������̨Ӧ�ó������ڵ㡣

//  ��Ŀ��Դ: http://codevs.cn/problem/1098/
//  �� N ��ֽ�ƣ���ŷֱ�Ϊ 1��2����, N��ÿ�����������ţ���ֽ��������Ϊ N �ı�������������һ����ȡ������ֽ�ƣ�Ȼ���ƶ���
//  ���ƹ���Ϊ���ڱ��Ϊ 1 ����ȡ��ֽ�ƣ�ֻ���Ƶ����Ϊ 2 �Ķ��ϣ��ڱ��Ϊ N �Ķ���ȡ��ֽ�ƣ�ֻ���Ƶ����Ϊ N - 1 �Ķ��ϣ�
//  ��������ȡ��ֽ�ƣ������Ƶ�������߻��ұߵĶ��ϡ�
//  ����Ҫ���ҳ�һ���ƶ������������ٵ��ƶ�����ʹÿ����ֽ������һ���ࡣ
//  
//  ���� N = 4��4 ��ֽ�����ֱ�Ϊ��
//  �١�9���ڡ�8���ۡ�17���ܡ�6
//  �ƶ�3�οɴﵽĿ�ģ�
//  �� �� ȡ 4 ���Ʒŵ� �� ��9 8 13 10��->�� �� ȡ 3 ���Ʒŵ� �ڣ�9 11 10 10��->�� �� ȡ 1 ���Ʒŵ��٣�10 10 10 10����


//  ˼·��
//  ��������������ÿ������Ӧ�е�����K��
//  Ȼ���ͷ��β����ÿһ���ѣ����
//  a)����ǰ��Ϊֹ�ܵ�����count_actual
//  b)�ھ��ֵ�����µ���ǰ��Ϊֹ������count_ideal
//  ���count_actual < count_ideal, �����������һ����
//  ���count_actual == count_ideal����ӵ�ǰ�ѿ�ʼ��ǰ����ÿ���Ѳ��ƶ����������ǰһ����
//  ���count_actual > count_ideal�������ȴӵ�ǰ���ƶ���(count_actual - count_ideal)�������Ƹ���һ���ѣ�
//  Ȼ��ӵ�ǰ�ѿ�ʼ��ǰ����ÿ���Ѳ��ƶ����������ǰһ����

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