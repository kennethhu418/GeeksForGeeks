// Quiz - Matrix Search.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <unordered_set>

/*******************************************************************************************************
            Given a matrix that is sorted both horizontally and vertically, algo and code for finding an element in it.
*******************************************************************************************************/

class Solution
{
public:
    bool    searchMatrix(int** matrix, int m, int n, int target)
    {
        if (matrix == NULL || m == 0 || n == 0) return false;

        this->matrix = matrix;
        this->m = m; this->n = n; this->target = target;

        return searchMatrix(0, 0, m - 1, n - 1);
    }

private:
    int**   matrix;
    int         m;
    int         n;
    int         target;

    bool searchMatrix(int x1, int y1, int x2, int y2)
    {
        if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0
            || x1 >= m || x2 >= m || y1 >= n || y2 >= n
            || x1 > x2 || y1 > y2)
            return false;

        int  midRow = (x1 + x2) / 2, insertPos = -1;
        if (searchArray(matrix[midRow], y1, y2, target, insertPos))
            return true;

        if (searchMatrix(midRow + 1, y1, x2, insertPos))
            return true;

        return searchMatrix(x1, insertPos + 1, midRow - 1, y2);
    }

    bool searchArray(int* arr, int start, int end, int target, int &insertPos)
    {
        if (start > end){ insertPos = -1; return false; }
        int mid = 0;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (arr[mid] == target) { insertPos = mid; return true; }
            if (arr[mid] > target) { end = mid - 1; continue; }
            start = mid + 1;
        }
        if (start > end){ insertPos = end; return false; }
        if (arr[start] == target) { insertPos = start; return true; }
        if (target < arr[start]) { insertPos = start - 1; return false; }
        insertPos = start; return false;
    }
};

inline bool searchMatrixBruteForce(int** matrix, int m, int n, int target)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == target)
                return true;
        }
    }
    return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
    const   unsigned    int     ROW_SIZE = 6;
    const   unsigned    int     COL_SIZE = 5;

    using namespace std;
    unordered_set<int>  mapA;
    Solution    so;

    int matrix_raw[ROW_SIZE][COL_SIZE] = {
    {3,     9,      20,     35,     60},
    {8,     17,     22,     56,     70},
    {14,    17,    22,      90,    91},
    {21,    22,     90,     99,     110},
    {90,    99,     110,    116,    124},
    {100,   115,    123,    124, 150}
    };

    int ** matrix = new int*[ROW_SIZE];
    for (int i = 0; i < ROW_SIZE; i++)
        matrix[i] = new int[COL_SIZE];
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            matrix[i][j] = matrix_raw[i][j];
            if (mapA.find(matrix_raw[i][j]) == mapA.end())
                mapA.insert(matrix_raw[i][j]);
        }
    }

    srand(time(0));
    unsigned __int64 times = 3000000;
    int target = 0;
    int existingElems = 0, nonExistingElems = 0;

    while (times-- > 0)
    {
        target = rand() % 180;
        if (mapA.find(target) != mapA.end())
        {
            existingElems++;
            //cout << "Search existing element: " << target << endl;
            if (!so.searchMatrix(matrix, ROW_SIZE, COL_SIZE, target))
            {
                cout << "Fail to find the expected number : " << target << endl;
            }
            continue;
        }

        //cout << "Search new element: " << target << endl;
        if (so.searchMatrix(matrix, ROW_SIZE, COL_SIZE, target))
        {
            cout << "Found the unexpected number : " << target << endl;
        }
        nonExistingElems++;
    }

    cout << endl << "++++++++++++++++++ TEST END ++++++++++++++++++" << endl;
    cout << "Totally " << existingElems << " existing elems tested and " << nonExistingElems << " non existing elems tested." << endl;
	
    system("PAUSE");
    return 0;
}