//Given an undirected graph and a number m, determine if the graph can be colored with at most m 
//colors such that no two adjacent vertices of the graph are colored with same color.
//Here coloring of a graph means assignment of colors to all vertices.
//
//Input:
//1) A 2D array graph[V][V] where V is the number of vertices in graph and graph[V][V] is 
//   adjacency matrix representation of the graph.A value graph[i][j] is 1 if there is a direct 
//   edge from i to j, otherwise graph[i][j] is 0.
//2) An integer m which is maximum number of colors that can be used.
//
//Output:
//An array color[V] that should have numbers from 1 to m.color[i] should represent the color 
//assigned to the ith vertex.The code should also return false if the graph cannot be colored 
//with m colors.
#include <iostream>
using namespace std;

#define MAX_VERTICE_COUNT 9

class Solution
{
public:
    bool canMColoring(const bool matrix[][MAX_VERTICE_COUNT], int n, int M, int *colorArr) {
        if (n == 0) return true;
        if (M == 0) return false;
        if (n == 1) { colorArr[0] = 0; return true; }

        mColorUsageArr = new bool[M];
        memset(colorArr, 0xFF, n * sizeof(int));
        mUsedColorCount = 0;
        mMaxColorCount = M;

        bool canColor = canGraphColor(matrix, n, 0, colorArr);
        delete[] mColorUsageArr;
        return canColor;
    }

private:
    bool *mColorUsageArr;
    int  mUsedColorCount;
    int  mMaxColorCount;

    bool canGraphColor(const bool matrix[][MAX_VERTICE_COUNT], int n, int v, int *colorArr) {
        memset(mColorUsageArr, 0, mUsedColorCount*sizeof(bool));
        for (int i = 0; i < n; ++i) {
            if (i == v) {
                if (matrix[v][v]) return false;
                continue;
            }

            if (matrix[v][i] && colorArr[i] >= 0)
                mColorUsageArr[colorArr[i]] = true;
        }

        int myColor = 0;
        for (myColor = 0; myColor < mUsedColorCount; ++myColor) {
            if (!mColorUsageArr[myColor]) break;
        }

        if (myColor == mUsedColorCount) {
            ++mUsedColorCount;
            if (mUsedColorCount > mMaxColorCount) return false;
        }

        colorArr[v] = myColor;
        for (int i = 0; i < n; ++i) {
            if (matrix[v][i] && colorArr[i] < 0) {
                if (!canGraphColor(matrix, n, i, colorArr)) return false;
            }
        }
        return true;    
    }
};

int main()
{
    bool adjMatrix[MAX_VERTICE_COUNT][MAX_VERTICE_COUNT] = \
    {   //     0  1  2  3  4  5  6  7  8
        /*0*/{ 0, 1, 0, 0, 0, 0, 1, 0, 0},
        /*1*/{ 1, 0, 1, 1, 1, 0, 0, 0, 0 },
        /*2*/{ 0, 1, 0, 1, 0, 0, 0, 0, 0 },
        /*3*/{ 0, 1, 1, 0, 0, 1, 0, 0, 0 },
        /*4*/{ 0, 1, 0, 0, 0, 1, 0, 0, 1 },
        /*5*/{ 0, 0, 0, 1, 1, 0, 0, 0, 1 },
        /*6*/{ 1, 0, 0, 0, 0, 0, 0, 1, 1 },
        /*7*/{ 0, 0, 0, 0, 0, 0, 1, 0, 1 },
        /*8*/{ 0, 0, 0, 0, 1, 1, 1, 1, 0 }
    };

    Solution so;
    int colorArr[MAX_VERTICE_COUNT];
    int n = MAX_VERTICE_COUNT;
    bool canColor = false;

    for (int M = 1; M <= MAX_VERTICE_COUNT; ++M) {
        canColor = so.canMColoring(adjMatrix, n, M, colorArr);
        if (!canColor)
            cout << "Cannot color with only " << M << " colors!" << endl;
        else{
            cout << "Coloring with " << M << " colors:" << endl;
            for (int i = 0; i < n; ++i)
                cout << colorArr[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}