// Quiz - Line Segment Overlay.cpp : 定义控制台应用程序的入口点。
//

//    给定x轴上的N（0<N<100）条线段，每个线段由它的二个端点a_I和b_I确定，I = 1, 2, ……N.这些坐标都是区间（－999，999）的整数。
//    有些线段之间会相互交叠或覆盖。请你编写一个程序，从给出的线段中去掉尽量少的线段，使得剩下的线段两两之间没有内部公共点。
//    所谓的内部公共点是指一个点同时属于两条线段且至少在其中一条线段的内部（即除去端点的部分）.

#include "stdafx.h"
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

/*********下面是基于图的实现，思想是每次去掉度数最大的线段。如果两个线段相交，那么就认为它们之间有边。时间复杂度为O(nlogn)**********/

typedef struct __Line
{
    int start;
    int end;
}Line;

typedef struct __Point
{
    int         val;
    int         index;
    bool     start;
    __Point(int val = 0, int index = -1, bool start = false) : val(val), index(index), start(start) {}
}Point;

static bool PointCmp(const Point &p1, const Point &p2)
{
    if (p1.val == p2.val){
        if (p1.index == p2.index)
            return p1.start;
        if (!p1.start && !p2.start)
            return p1.index < p2.index;
        if (!p1.start)  return true;
        if (!p2.start)  return false;
        return p1.index < p2.index;
    }
    return p1.val < p2.val;
}

typedef struct __LineConnectionNode
{
    int     index;
    int     degree;
    int     seq;
    __LineConnectionNode(int index = -1, int degree = 0, int seq = 0) : index(index), degree(degree), seq(seq){};
}LineConnectionNode;

class LineConnectionNodeCmp
{
public:
    bool    operator()(const LineConnectionNode &node1, const LineConnectionNode &node2){
        return node1.degree < node2.degree;
    }
};

class Solution
{
private:
    set<int>  hashA;
    Point   *pointArr;
    priority_queue<LineConnectionNode, vector<LineConnectionNode>, LineConnectionNodeCmp> maxHeap;
    bool        **overlayMatrix;
    int           *degreeArr;
    int           *validLineSeqArr;
    int            N;

    void AllocateMemory()
    {
        pointArr = new Point[N<<1];
        overlayMatrix = new bool*[N];
        for (int i = 0; i < N; ++i) {
            overlayMatrix[i] = new bool[N];
            memset(overlayMatrix[i], 0, sizeof(bool)*N);
        }
        degreeArr = new int[N];
        memset(degreeArr, 0, sizeof(int)*N);
        validLineSeqArr = new int[N];
        memset(validLineSeqArr, 0, sizeof(int)*N);
    }

    void FreeMemory()
    {
        delete[] pointArr;
        for (int i = 0; i < N; ++i)
            delete[] overlayMatrix[i];
        delete[] overlayMatrix;
        delete[] degreeArr;
        delete[] validLineSeqArr;
        hashA.clear();
        while (!maxHeap.empty())
            maxHeap.pop();
    }

    void CalculateOverlayMatrix(const Line * lineArr, int n){
        Point pt;
        for (int i = 0; i < n; ++i){
            pt.index = i;
            pt.val = lineArr[i].start;
            pt.start = true;
            pointArr[i << 1] = pt;
            pt.index = i;
            pt.val = lineArr[i].end;
            pt.start = false;            
            pointArr[(i << 1) + 1] = pt;
        }

        sort(pointArr, pointArr + (n << 1), PointCmp);

        hashA.insert(pointArr[0].index);
        for (int i = 1; i < (n << 1); ++i){
            if (pointArr[i].start){
                for (set<int>::iterator iter = hashA.begin(); iter != hashA.end(); ++iter){
                    overlayMatrix[pointArr[i].index][*iter] = true;
                    overlayMatrix[*iter][pointArr[i].index] = true;
                    ++degreeArr[*iter];
                    ++degreeArr[pointArr[i].index];
                }
                hashA.insert(pointArr[i].index);
            }
            else
                hashA.erase(pointArr[i].index);
        }
    }

    void FillHeapWithConnectionNode(){
        LineConnectionNode node;
        for (int i = 0; i < N; ++i){
            node.index = i;
            node.degree = degreeArr[i];
            node.seq = 0;
            maxHeap.push(node);
        }
    }

public:
    int getMaxNonOverlaySegments(const Line * lineArr, int n)
    {
        if (n < 2)  return n;

        this->N = n;
        int removedCount = 0;

        AllocateMemory();
        CalculateOverlayMatrix(lineArr, n);
        FillHeapWithConnectionNode();

        LineConnectionNode node;
        int removedIndex = 0, targetIndex = 0;
        while (!maxHeap.empty()){
            node = maxHeap.top(); maxHeap.pop();
            if (node.seq != validLineSeqArr[node.index]) continue;
            if (node.degree == 0) break;

            //remove this node
            ++removedCount;
            removedIndex = node.index;
            for (int i = 0; i < n; ++i) {
                if (overlayMatrix[removedIndex][i]){
                    overlayMatrix[i][removedIndex] = false;
                    overlayMatrix[removedIndex][i] = false;
                    --degreeArr[removedIndex];
                    --degreeArr[i];
                    ++validLineSeqArr[i];
                    node.degree = degreeArr[i];
                    node.index = i;
                    node.seq = validLineSeqArr[i];
                    maxHeap.push(node);
                }
            }
            ++validLineSeqArr[removedIndex];
        }

        FreeMemory();
        return n - removedCount;
    }
};

//int _tmain(int argc, _TCHAR* argv[])
//{
//    Line lineArr1[] = { { 3, 6 }, { 1, 3 }, {2, 5} };
//    Line lineArr2[] = { { 2, 10 }, { 4, 6 }, { 5, 15 }, { 12, 20 }, { 0, 2 }, {6, 10} };
//    Solution so;
//
//    int    n = sizeof(lineArr1) / sizeof(Line);
//    //cout << "Maximum Nonoverlapping Lines of line collection 1 is " << so.getMaxNonOverlaySegments(lineArr1, n) << endl;
//
//    n = sizeof(lineArr2) / sizeof(Line);
//    cout << "Maximum Nonoverlapping Lines of line collection 2 is " << so.getMaxNonOverlaySegments(lineArr2, n) << endl;
//	return 0;
//}


int main()
{
    int N;
    int start = 0, end = 0;
    cin >> N;

    if (N < 2){
        cout << N << endl;
        return 0;
    }

    Line *lineArr = new Line[N];
    for (int i = 0; i < N; ++i){
        cin >> start >> end;
        if (start > end)
            swap(start, end);
        lineArr[i].start = start;
        lineArr[i].end = end;
    }

    Solution so;
    cout << so.getMaxNonOverlaySegments(lineArr, N) << endl;
    return 0;
}

