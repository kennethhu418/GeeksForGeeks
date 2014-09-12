// Quiz - Line Segment Overlay.cpp : 定义控制台应用程序的入口点。
//

//    给定x轴上的N（0<N<100）条线段，每个线段由它的二个端点a_I和b_I确定，I = 1, 2, ……N.这些坐标都是区间（－999，999）的整数。
//    有些线段之间会相互交叠或覆盖。请你编写一个程序，从给出的线段中去掉尽量少的线段，使得剩下的线段两两之间没有内部公共点。
//    所谓的内部公共点是指一个点同时属于两条线段且至少在其中一条线段的内部（即除去端点的部分）.

#include "stdafx.h"
#include <algorithm>
#include <iostream>
using namespace std;

/********* 第一版程序是基于图的实现，思想是每次去掉度数最大的线段。如果两个线段相交，那么就认为它们之间有边。时间复杂度为O(nlogn)，但是实现过于复杂**********/
/********* 这儿我们同样给出复杂度为O(nlogn)的解法，但是为实现非常简单的贪心算法**********/

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