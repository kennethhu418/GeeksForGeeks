// Quiz - Sort a K sorted array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>

template <class T>
class MinHeap
{
public:
    bool    empty();

    void     clear();

    T          removeMin();

    T&       peekMin();

    void    insert(const T &target);

};


class Solution
{
public:
    void sortKSortedArray(int arr[], int n, int k)
    {
        assert(k <= n);

        for (int i = 0; i < k; i++)
            utilityHeap.insert(arr[i]);

        int targetPos = 0;
        int curArrPos = k;
        while (!utilityHeap.empty())
        {
            arr[targetPos++] = utilityHeap.removeMin();
            if (curArrPos < n)
                utilityHeap.insert(arr[curArrPos++]);
        }

        return;
    }

private:
    MinHeap<int>    utilityHeap;
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

