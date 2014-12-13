//A batch of time intervals like{ 2 / 3 - 2 / 20, 2, 6 - 3 / 5 }.
//need to split the intervals to{ 2 / 3 - 2 / 6, 2 / 7 - 2 / 20, 2 / 21 - 3 / 5 }.
//Solve it with minimum time complexity.How to do it ?

#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;

typedef struct __Point
{
    int     val;
    bool    isEnd;
}Point;

typedef struct __Interval
{
    int     start;
    int     end;
}Interval;

static bool comparePoint(const Point &p1, const Point &p2)
{
    if (p1.val == p2.val)
    {
        if (p1.isEnd == false && p2.isEnd == true) return true;
        return false;
    }

    return p1.val < p2.val;
}

vector<Interval> splitIntervals(const vector<Interval> &intervalArr) {
    int n = intervalArr.size();
    if (n < 2) return intervalArr;

    vector<Point>   pointArr;
    Point pt;
    for (int i = 0; i < n; ++i) {
        pt.val = intervalArr[i].start;
        pt.isEnd = false;
        pointArr.push_back(pt);
        pt.val = intervalArr[i].end;
        pt.isEnd = true;
        pointArr.push_back(pt);
    }

    sort(pointArr.begin(), pointArr.end(), comparePoint);

    vector<Interval> resultArr;
    Interval interval = { -1, -1 };
    int startCount = 0; n <<= 1;
    for (int i = 0; i < n; ++i) {
        if (startCount == 0) {
            assert(pointArr[i].isEnd == false);
            interval.start = pointArr[i].val;
            ++startCount;
        }
        else {
            interval.end = pointArr[i].val;
            if (resultArr.size() && interval.start == resultArr.back().end)
                ++interval.start;
            if (interval.start <= interval.end)
                resultArr.push_back(interval);

            interval.start = interval.end;
            if (pointArr[i].isEnd) --startCount;
            else ++startCount;
        }
    }

    return resultArr;
}


int main()
{
    Interval intervalArr[] = {
        {5, 30},
        {40, 40},
        {49, 55},
        {8, 12},
        {12, 20},
        {20, 38}
    };

    vector<Interval> intervalVec(intervalArr, intervalArr + sizeof(intervalArr) / sizeof(Interval));
    vector<Interval> resultArr = splitIntervals(intervalVec);
    for (int i = 0; i < resultArr.size(); ++i)
        cout << resultArr[i].start << "--" << resultArr[i].end << "  ";
    cout << endl;
	return 0;
}