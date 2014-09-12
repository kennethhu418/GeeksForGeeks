// Quiz - Line Segment Overlay.cpp : �������̨Ӧ�ó������ڵ㡣
//

//    ����x���ϵ�N��0<N<100�����߶Σ�ÿ���߶������Ķ����˵�a_I��b_Iȷ����I = 1, 2, ����N.��Щ���궼�����䣨��999��999����������
//    ��Щ�߶�֮����໥�����򸲸ǡ������дһ�����򣬴Ӹ������߶���ȥ�������ٵ��߶Σ�ʹ��ʣ�µ��߶�����֮��û���ڲ������㡣
//    ��ν���ڲ���������ָһ����ͬʱ���������߶�������������һ���߶ε��ڲ�������ȥ�˵�Ĳ��֣�.

#include "stdafx.h"
#include <algorithm>
#include <iostream>
using namespace std;

/********* ��һ������ǻ���ͼ��ʵ�֣�˼����ÿ��ȥ�����������߶Ρ���������߶��ཻ����ô����Ϊ����֮���бߡ�ʱ�临�Ӷ�ΪO(nlogn)������ʵ�ֹ��ڸ���**********/
/********* �������ͬ���������Ӷ�ΪO(nlogn)�Ľⷨ������Ϊʵ�ַǳ��򵥵�̰���㷨**********/

typedef struct __Line
{
    int start;
    int end;
}Line;

static bool LineCmp(const Line &l1, const Line &l2)
{
    return l1.end < l2.end;
}

class Solution
{
public:
    int getMaxNonOverlaySegments(Line * lineArr, int n)
    {
        if (n < 2)  return n;

        sort(lineArr, lineArr + n, LineCmp);

        int lastSegmentEnd = lineArr[0].end, count = 1;
        for (int i = 1; i < n; ++i){
            if (lineArr[i].start >= lastSegmentEnd){
                ++count;
                lastSegmentEnd = lineArr[i].end;
            }
        }

        return count;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Line lineArr1[] = { { 3, 6 }, { 1, 3 }, {2, 5} };
    Line lineArr2[] = { { 2, 10 }, { 4, 6 }, { 5, 15 }, { 12, 20 }, { 0, 2 }, {6, 10} };
    Solution so;

    int    n = sizeof(lineArr1) / sizeof(Line);
    cout << "Maximum Nonoverlapping Lines of line collection 1 is " << so.getMaxNonOverlaySegments(lineArr1, n) << endl;

    n = sizeof(lineArr2) / sizeof(Line);
    cout << "Maximum Nonoverlapping Lines of line collection 2 is " << so.getMaxNonOverlaySegments(lineArr2, n) << endl;
	return 0;
}