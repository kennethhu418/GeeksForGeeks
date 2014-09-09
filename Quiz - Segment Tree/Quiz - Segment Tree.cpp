// Quiz - Segment Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

/***********************************************************************
* 线段树参考：
* http://www.cnblogs.com/TenosDoIt/p/3453089.html
* http://blog.csdn.net/wmn_wmn/article/details/8108223
* 本cpp参考上述第二个链接实现了用线段树求矩形并的周长和面积
*
***********************************************************************/

#define MAX_RECTANGLE_EDGE_X 900
#define MAX_RECTANGLE_EDGE_Y 900

class Rectangle
{
public:
    int x;
    int y;
    int w;
    int h;
    Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) : x(x), y(y), w(w), h(h) {}
};

class Segment
{
public:
    int segStart;
    int segEnd;
    int segKey;
    int flag; //0: start line of the rectangle 1: end line of the rectangle
    Segment(int start = -1, int end = -1, int key = 0, int flag = 0) : segStart(start), segEnd(end), segKey(key), flag(flag) {}
};

static bool compare_segment(const Segment &s1, const Segment &s2)
{
    if (s1.segKey == s2.segKey)
        return s1.flag < s2.flag;
    return s1.segKey < s2.segKey;
}

class SegmentTree
{
private:
    typedef struct __TreeNode
    {
        int rangeL;
        int rangeR;
        int coverTimes;
        int segLengthInThisRange;
        __TreeNode(int rangeL = -1, int rangeR = -1) : rangeL(rangeL), rangeR(rangeR), coverTimes(0), segLengthInThisRange(0) {}
        int getMid()
        {
            return ((rangeL + rangeR) >> 1);
        }
    }TreeNode;

    TreeNode    *nodeArr;
    int         size;

    void PushDownCoveredRange(int coveredTimes, int pos)
    {
        nodeArr[pos].coverTimes += coveredTimes;        
        nodeArr[pos].segLengthInThisRange = nodeArr[pos].rangeR - nodeArr[pos].rangeL + 1;
    }

    void    InitializeSegments(int rL, int rR, int pos)
    {
        nodeArr[pos].rangeL = rL;
        nodeArr[pos].rangeR = rR;
        if (rL == rR)   return;

        int mid = nodeArr[pos].getMid();
        InitializeSegments(rL, mid, (pos << 1) + 1);
        InitializeSegments(mid + 1, rR, (pos << 1) + 2);
    }

public:
    void    Initialize(int rangeStart, int rangeEnd)
    {
        nodeArr = new TreeNode[(rangeEnd - rangeStart + 1)*6];
        InitializeSegments(rangeStart, rangeEnd, 0);
    }

    void    Release()
    {
        delete[] nodeArr;
    }

    void    ReSet(int pos = 0)
    {
        nodeArr[pos].coverTimes = nodeArr[pos].segLengthInThisRange = 0;
        ReSet((pos << 1) + 1);
        ReSet((pos << 1) + 2);
    }

    int     InsertSegment(int segStart, int segEnd, int pos = 0)
    {
        if (segEnd < nodeArr[pos].rangeL || segStart > nodeArr[pos].rangeR)
            return 0;

        if (nodeArr[pos].rangeL >= segStart && nodeArr[pos].rangeR <= segEnd)
        {
            nodeArr[pos].coverTimes++;
            nodeArr[pos].segLengthInThisRange = nodeArr[pos].rangeR - nodeArr[pos].rangeL + 1;
            return nodeArr[pos].segLengthInThisRange;
        }

        if (nodeArr[pos].coverTimes > 0)
        {
            PushDownCoveredRange(nodeArr[pos].coverTimes, (pos << 1) + 1);
            PushDownCoveredRange(nodeArr[pos].coverTimes, (pos << 1) + 2);
            nodeArr[pos].coverTimes = 0;
        }

        nodeArr[pos].segLengthInThisRange = InsertSegment(segStart, segEnd, (pos << 1) + 1) + InsertSegment(segStart, segEnd, (pos << 1) + 2);
        return nodeArr[pos].segLengthInThisRange;
    }

    int RemoveSegment(int segStart, int segEnd, int pos = 0)
    {
        if (segEnd < nodeArr[pos].rangeL || segStart > nodeArr[pos].rangeR)
            return 0;

        if (nodeArr[pos].rangeL >= segStart && nodeArr[pos].rangeR <= segEnd)
        {
            if (nodeArr[pos].coverTimes > 0)
            {
                nodeArr[pos].coverTimes--;
                if (nodeArr[pos].coverTimes == 0)
                {
                    if (nodeArr[pos].rangeL == nodeArr[pos].rangeR)
                        nodeArr[pos].segLengthInThisRange = 0;
                    else
                        nodeArr[pos].segLengthInThisRange = nodeArr[(pos << 1) + 1].segLengthInThisRange + nodeArr[(pos << 1) + 2].segLengthInThisRange;
                }
            }
            else
                nodeArr[pos].segLengthInThisRange = RemoveSegment(segStart, segEnd, (pos << 1) + 1) + RemoveSegment(segStart, segEnd, (pos << 1) + 2);
            return nodeArr[pos].segLengthInThisRange;
        }

        if (nodeArr[pos].coverTimes > 0)
        {
            PushDownCoveredRange(nodeArr[pos].coverTimes, (pos << 1) + 1);
            PushDownCoveredRange(nodeArr[pos].coverTimes, (pos << 1) + 2);
            nodeArr[pos].coverTimes = 0;
        }

        nodeArr[pos].segLengthInThisRange = RemoveSegment(segStart, segEnd, (pos << 1) + 1) + RemoveSegment(segStart, segEnd, (pos << 1) + 2);
        return nodeArr[pos].segLengthInThisRange;
    }
};

class Solution_Perimeter
{
private:
    Segment *segArr1;
    Segment *segArr2;
    int      size;

    void    AllocateMemory()
    {
        segArr1 = new Segment[size];
        segArr2 = new Segment[size];
    }

    void    FreeMemory()
    {
        delete[] segArr1;
        delete[] segArr2;
    }

    void FillAndSortVerticalSegments(const Rectangle *rectArr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            segArr1[i << 1].segStart = rectArr[i].y;
            segArr1[i << 1].segEnd = rectArr[i].y + rectArr[i].h - 1;
            segArr1[i << 1].segKey = rectArr[i].x;
            segArr1[i << 1].flag = 0;

            segArr1[(i << 1) + 1].segStart = rectArr[i].y;
            segArr1[(i << 1) + 1].segEnd = rectArr[i].y + rectArr[i].h - 1;
            segArr1[(i << 1) + 1].segKey = rectArr[i].x + rectArr[i].w - 1;
            segArr1[(i << 1) + 1].flag = 1;
        }

        sort(segArr1, segArr1 + (n << 1), compare_segment);
    }

    void FillAndSortHorizonalSegments(const Rectangle *rectArr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            segArr2[i << 1].segStart = rectArr[i].x;
            segArr2[i << 1].segEnd = rectArr[i].x + rectArr[i].w - 1;
            segArr2[i << 1].segKey = rectArr[i].y;
            segArr2[i << 1].flag = 0;

            segArr2[(i << 1) + 1].segStart = rectArr[i].x;
            segArr2[(i << 1) + 1].segEnd = rectArr[i].x + rectArr[i].x - 1;
            segArr2[(i << 1) + 1].segKey = rectArr[i].y + rectArr[i].h - 1;
            segArr2[(i << 1) + 1].flag = 1;
        }

        sort(segArr2, segArr2 + (n << 1), compare_segment);
    }

public:
    int getRectanglePerimeter(const Rectangle *rectArr, int n)
    {
        if (n == 0) return 0;
        this->size = (n << 1);
        AllocateMemory();

        FillAndSortVerticalSegments(rectArr, n);
        FillAndSortHorizonalSegments(rectArr, n);

        SegmentTree segTree;
        segTree.Initialize(MAX_RECTANGLE_EDGE_X, MAX_RECTANGLE_EDGE_Y);

        int permimeter = 0;
        int prevVerticalLineLength = 0, curVerticalLineLength = 0;
        
        //Run with vertical edges firstly
        for (int i = 0; i < size; ++i)
        {
            if (segArr1[i].flag == 0)
                curVerticalLineLength = segTree.InsertSegment(segArr1[i].segStart, segArr1[i].segEnd);
            else
                curVerticalLineLength = segTree.RemoveSegment(segArr1[i].segStart, segArr1[i].segEnd);

            permimeter += abs(curVerticalLineLength - prevVerticalLineLength);
            prevVerticalLineLength = curVerticalLineLength;
        }

        //Run with horizonal edges secondly
        segTree.ReSet();
        int prevHorizonalLineLength = 0, curHorizonalLineLength = 0;
        for (int i = 0; i < size; ++i)
        {
            if (segArr2[i].flag == 0)
                curHorizonalLineLength = segTree.InsertSegment(segArr2[i].segStart, segArr2[i].segEnd);
            else
                curHorizonalLineLength = segTree.RemoveSegment(segArr2[i].segStart, segArr2[i].segEnd);

            permimeter += abs(curHorizonalLineLength - prevHorizonalLineLength);
            prevHorizonalLineLength = curHorizonalLineLength;
        }        

        segTree.Release();
        FreeMemory();

        return permimeter;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    const int   MAX_RECTANGLE_COUNT = 300;
    Rectangle rectArr[MAX_RECTANGLE_COUNT];
    int n = 0;

    ifstream fin;
    fin.open("D:\\rect_tests.txt");
    if (fin.bad()) { cout << "Bad File!" << endl; return -1;}

    while (!fin.eof())
    {
        fin >> rectArr[n].x;
        if (fin.eof()) break;
        fin >> rectArr[n].y >> rectArr[n].w >> rectArr[n].h;
        ++n;
    }

    Solution_Perimeter so;
    cout << so.getRectanglePerimeter(rectArr, n) << endl;

	return 0;
}

