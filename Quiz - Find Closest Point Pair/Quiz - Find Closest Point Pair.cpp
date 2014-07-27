// Quiz - Find Closest Point Pair.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <assert.h>

#define MAX_DISTANCE 1000000

typedef struct __Point
{
    double     x;
    double     y;
    __Point(double x1 = 0, double y1 = 0) : x(x1), y(y1) {}
}Point;

class Solution
{
public:
    double     getClosestPointPair(Point *pointArr, int n, Point &p1, Point &p2)
    {
        if (n < 2)  return 0;

        for (int i = 0; i < n; i++)
        {
            pointArr_x_sorted.push_back(pointArr[i]);
            pointArr_y_sorted.push_back(pointArr[i]);
        }

        std::sort(pointArr_x_sorted.begin(), pointArr_x_sorted.end(), compareWithX);
        std::sort(pointArr_y_sorted.begin(), pointArr_y_sorted.end(), compareWithY);

        closestDistant = MAX_DISTANCE;

        getClosestPointPair(0, n - 1);
        p1 = closestPoint1;
        p2 = closestPoint2;
        pointArr_x_sorted.clear();
        pointArr_y_sorted.clear();
        return closestDistant;
    }

private:
    std::vector<Point>   pointArr_x_sorted;
    std::vector<Point>   pointArr_y_sorted;
    std::vector<Point>   pointQ;
    Point       closestPoint1;
    Point       closestPoint2;
    double   closestDistant;

    static  bool compareWithX(const Point &p1, const Point &p2)
    {
        return p1.x < p2.x;    
    }

    static  bool compareWithY(const Point &p1, const Point &p2)
    {
        return p1.y < p2.y;
    }

    inline double getDist(const Point &p1, const Point &p2)
    {
        return std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    }

    void getClosestPointPair(int start, int end)
    {
        if (start >= end)    return;

        if (end - start == 1)
        {
            double dist = getDist(pointArr_x_sorted[start], pointArr_x_sorted[end]);
            if (dist < this->closestDistant)
            {
                this->closestDistant = dist;
                closestPoint1 = pointArr_x_sorted[start];
                closestPoint2 = pointArr_x_sorted[end];
            }
            return;                
        }

        int mid = ((start + end) >> 1);

        getClosestPointPair(start, mid);
        getClosestPointPair(mid + 1, end);
        double startX = pointArr_x_sorted[mid].x - closestDistant, endX = pointArr_x_sorted[mid].x + closestDistant;

        //partition the points by distance.
        int n = pointArr_y_sorted.size();
        for (int i = 0; i < n; i++)
        {
            if (pointArr_y_sorted[i].x >= pointArr_x_sorted[start].x && pointArr_y_sorted[i].x <= pointArr_x_sorted[end].x
                && pointArr_y_sorted[i].x <= endX && pointArr_y_sorted[i].x >= startX)
                pointQ.push_back(pointArr_y_sorted[i]);
        }

        //Now merge the distance
        int curPos = 0, size = pointQ.size(), cmpPos = 1, checkedCnt = 0;
        double curDist = 0;
        while (curPos < size)
        {
            cmpPos = curPos + 1, checkedCnt = 0;
            while (cmpPos < size && checkedCnt < 5 && pointQ[cmpPos].y - pointQ[curPos].y <= closestDistant)
            {
                curDist = getDist(pointQ[cmpPos], pointQ[curPos]);
                if (curDist < closestDistant)
                {
                    closestDistant = curDist;
                    closestPoint1 = pointQ[cmpPos];
                    closestPoint2 = pointQ[curPos];
                }
                ++cmpPos; ++checkedCnt;
            }
            ++curPos;
        }

        pointQ.clear();
    }
};


class Solution_BruteForce
{
public:
    double     getClosestPointPair(Point *pointArr, int n, Point &p1, Point &p2)
    {
        double closestDist = MAX_DISTANCE, curDist = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                curDist = getDist(pointArr[i], pointArr[j]);
                if (curDist < closestDist)
                {
                    closestDist = curDist;
                    p1 = pointArr[i];
                    p2 = pointArr[j];
                }
            }
        }

        return closestDist;
    }

private:
    inline double getDist(const Point &p1, const Point &p2)
    {
        return std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    }
};

void generatePoints(Point* pointArr, int n, int maxX, int maxY)
{
    for (int i = 0; i < n; i++)
    {
        pointArr[i].x = rand() % maxX;
        pointArr[i].y = rand() % maxY;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    const int MAX_X = 3000;
    const int MAX_Y = 3000;
    const int MAX_TIMES = 1000;
    const int MIN_POINT_COUNT = 3000;
    const unsigned int MAX_POINT_COUNT = 300000;

    Solution so;
    Solution_BruteForce so_standard;
    double standard_ans = 0, my_ans = 0;
    Point p1, p2;
    Point   *pointArr = new Point[MAX_POINT_COUNT];
    unsigned int size = 0, tryTimes = 0;
    clock_t  startTime = 0, standard_time = 0, my_time = 0;

    using namespace std;

    while (tryTimes < MAX_TIMES)
    {
        size = rand() % (MAX_POINT_COUNT - MIN_POINT_COUNT + 1) + MIN_POINT_COUNT;
        generatePoints(&pointArr[0], size, MAX_X, MAX_Y);

        startTime = clock();
        standard_ans = so_standard.getClosestPointPair(&pointArr[0], size, p1, p2);
        standard_time += (clock() - startTime);

        startTime = clock();
        my_ans = so.getClosestPointPair(&pointArr[0], size, p1, p2);
        my_time += (clock() - startTime);

        if (abs(my_ans - standard_ans) >= 0.00001)
        {
            cout << "Oh, No!. Get different ans: standard = " << standard_ans << "  my = " << my_ans << endl;
            assert(0);
        }

        ++tryTimes;
    }

    cout << "My time: " << my_time << "  Standard time: " << standard_time << endl;

    system("PAUSE");
	return 0;
}

