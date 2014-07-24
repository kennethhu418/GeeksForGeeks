// Quiz - Maintain Median Value In a stream.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>
#include <vector>
#include <functional>
#include <iostream>

class MedianStream
{
public:
    void    insert(int  data)
    {
        if (empty())
        {
            leftHeap.push(data);
            return;
        }

        if (leftHeap.size() == rightHeap.size())
        {
            if (data <= rightHeap.top())
                leftHeap.push(data);
            else
            {
                int popedData = rightHeap.top();
                rightHeap.pop();
                leftHeap.push(popedData);
                rightHeap.push(data);
            }
            return;
        }

        if (data >= leftHeap.top())
            rightHeap.push(data);
        else
        {
            int poppedData = leftHeap.top();
            leftHeap.pop();
            rightHeap.push(poppedData);
            leftHeap.push(data);
        }
    }

    bool      empty()
    {
        return leftHeap.empty();
    }

    int      getMedian()
    {
        if (empty())    return -1;
        return leftHeap.top();
    }

private:
    std::priority_queue<int, std::vector<int>, std::less<int>>     leftHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>>     rightHeap;
};

int _tmain(int argc, _TCHAR* argv[])
{
    MedianStream    so;

    using namespace std;

    int  curVal;
    cout << "Input a new number: ";
    while (cin >> curVal)
    {
        so.insert(curVal);
        cout << "Current Median is " << so.getMedian() << endl;
        cout << "**************************************" << endl;
        cout << "Input a new number: ";
    }

	return 0;
}

