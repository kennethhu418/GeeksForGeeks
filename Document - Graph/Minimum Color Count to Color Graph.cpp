// Calculate the miminum count of color that can be used to color a graph so that no adjacent nodes have the same color

#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;

#define MAX_VERTEX_COUNT 30

class Solution
{
public:
    int getMinimumGraphColoring(bool **adjMatrix, int n, int *colorArr) {
        if (n == 0) return 0;
        if (n == 1) {
            colorArr[0] = 0;
            return 1;
        }

        // Binary Search to get the minimum count of color
        int endColorCount = getMaxDegree(adjMatrix, n) + 1;
        int startColorCount = 1, midColorCount = -1;
        while (startColorCount < endColorCount) {
            midColorCount = ((startColorCount + endColorCount) >> 1);
            if (colorWithMChoices(adjMatrix, n, colorArr, midColorCount))
                endColorCount = midColorCount - 1;
            else
                startColorCount = midColorCount + 1;
        }

        if (startColorCount > endColorCount || colorWithMChoices(adjMatrix, n, colorArr, startColorCount)) return startColorCount;
        assert(colorWithMChoices(adjMatrix, n, colorArr, startColorCount + 1));
        return startColorCount + 1;
    }

private:
    int getMaxDegree(bool **adjMatrix, int n) {
        int maxDegree = 0, curDegree = 0;
        for (int i = 0; i < n; ++i) {
            curDegree = 0;
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j]) ++curDegree;
            }
            if (curDegree > maxDegree) maxDegree = curDegree;
        }
        return maxDegree;
    }

    bool colorWithMChoices(bool **adjMatrix, int n, int *colorArr, int M) {
        memset(colorArr, 0xFF, n * sizeof(int));
        return colorWithMChoices(adjMatrix, n, 0, colorArr, M);
    }

    bool isSafe(bool *adjArr, int n, int *colorArr, int targetColor) {
        for (int i = 0; i < n; ++i) {
            if (adjArr[i] && colorArr[i] == targetColor) return false;
        }
        return true;
    }

    bool colorWithMChoices(bool **adjMatrix, int n, int curNode, int *colorArr, int M) {
        if (curNode == n) return true;
        colorArr[curNode] = -1;
        for (int curColor = 0; curColor < M; ++curColor) {
            if (!isSafe(adjMatrix[curNode], n, colorArr, curColor)) continue;
            colorArr[curNode] = curColor;
            if (colorWithMChoices(adjMatrix, n, curNode + 1, colorArr, M))
                return true;
            colorArr[curNode] = -1;
        }
        return false;
    }
};

int main()
{
    const unsigned int NODE_N = 6;
    bool b0[] = { 0, 1, 1, 1, 1, 1 };
    bool b1[] = { 1, 0, 0, 1, 1, 0 };
    bool b2[] = { 1, 0, 0, 0, 1, 1 };
    bool b3[] = { 1, 1, 0, 0, 1, 1 };
    bool b4[] = { 1, 1, 1, 1, 0, 0 };
    bool b5[] = { 1, 0, 1, 1, 0, 0 };
    bool *adjMatrix[NODE_N] = { b0, b1, b2, b3, b4, b5 };
    int colorArr[NODE_N] = { -1 };

    Solution so;
    int colorCount = so.getMinimumGraphColoring(adjMatrix, NODE_N, colorArr);
    cout << "Color count is " << colorCount << endl;
    for (int i = 0; i < NODE_N; ++i)
        cout << colorArr[i] << ' ';
    cout << endl;
    return 0;
}