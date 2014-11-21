#include <iostream>
#include <algorithm>
using namespace std;

// We take directed graph as example. Undirected graph is the same process and could be more simpler.
// Author: Kenneth Hu
// Date : 11/20/2014

class Solution {
public:
    //Graph Represented by adjacent Matrix, where adjMatrix[i][j] = there is an edge from i to j
    bool determineEulerianCycle(const bool **adjMatrix, int n, int *eulerianPath, int &edgeCount) {
        if (n == 0) return false;

        Initialize(n);

        if (!isEulerianCyclePreliminarily(adjMatrix, n)) {
            edgeCount = mTotalEdgeCount;
            Free();
            return false;
        }

        edgeCount = mTotalEdgeCount;

        //Start Recursively Walk from any node, here we start from node 0
        walkEulerianCycle(adjMatrix, n, 0, eulerianPath);

        //Check that all edges should be traversed. 
        //If there is still untraversed edge, it means the graph is not a connected graph. So it
        //is not a Eulerian Cycle of course.
        if (mCurTraversedEdgeCount < mTotalEdgeCount) {
            Free(); return false;
        }

        //Reverse the eulerianPath to get the forwarding direction path
        int start = 0, end = mTotalEdgeCount;
        while (start < end) swap(eulerianPath[start++], eulerianPath[end--]);

        Free();
        return true;
    }

private:
    int     *mInDegree;
    int     *mOutDegree;
    bool  *mEdgeVisitedArr; // used to label whether an edge has been visited. If edge from i to j is visited, then mEdgeVisitedArr[i * n + j] is set to true
    int       mCurTraversedEdgeCount;
    int       mTotalEdgeCount;

    void Initialize(int n) {
        mInDegree = new int[n];
        mOutDegree = new int[n];
        mEdgeVisitedArr = new bool[n * n];
        memset(mInDegree, 0, n * sizeof(int));
        memset(mOutDegree, 0, n * sizeof(int));
        memset(mEdgeVisitedArr, 0, n * n * sizeof(int));
        mCurTraversedEdgeCount = 0;
        mTotalEdgeCount = 0;
    }

    void Free() {
        delete[] mInDegree;
        delete[] mOutDegree;
    }

    // Preliminarily determine whether the graph could be a Eulerian Cycle
    // It is a "Preliminarily" determination because we did not check whether
    // the graph is a connected graph here. We only check in degree and out
    // degree here. The check of connected graph is performed in later stage.
    bool isEulerianCyclePreliminarily(const bool **adjMatrix, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j]) {
                    ++mInDegree[j];
                    ++mOutDegree[i];
                    ++mTotalEdgeCount;
                }
            }
        }

        // Now check each node's in degree and out degree.
        for (int i = 0; i < n; ++i) {
            if (mInDegree[i] != mOutDegree[i]) return false;
        }

        return true;
    }

    // The walkEulerianPath is very very simple. It is just a recursively traverse of all edges. 
    // You can draw analogy of this to the traverse of nodes of a graph. How would you traverse nodes of a graph.
    //
    //       void traverseNodes(const bool **adjMatrix, int n, int curNode, int *nodeTraverseArr) {
    //           for (int i = 0; i < n; ++i) {
    //               if (!adjMatrix[curNode][i]) continue;
    //               if (hasVisited[i]) continue; // If node i has already been visited (i.e., recorded in nodeTraverseArr), do not visit again.
    //               hasVisited[i] = true;
    //               traverseNodes(adjMatrix, n, i, nodeTraverseArr);
    //           }
    //           nodeTraverseArr[mTraversedNodeCount++] = curNode;
    //       }
    //
    // Apply this to Eulerian Cycle, the traversed entity is edge, not node now. We just replace node in the above codes with edge :)
    // curNode parameter is the destination node of currently traversing edge
    void walkEulerianCycle(const bool **adjMatrix, int n, int curNode, int *eulerianPath) {
        // Traverse next un-tranversed edges to continue the Eulerian path.
        for (int i = 0; i < n; ++i) {
            if (!adjMatrix[curNode][i]) continue;
            if (mEdgeVisitedArr[curNode*n + i]) continue; //If the edge has already been visited, do not visit again

            mEdgeVisitedArr[curNode*n + i] = true;
            walkEulerianCycle(adjMatrix, n, i, eulerianPath);
        }

        // Then add the current traversing edge into the eulerianPath
        eulerianPath[mCurTraversedEdgeCount++] = curNode;
    }
};

int main()
{
    // Please see the "Eulerian_Path.png" figure in the same folder for the example graph
    const int N = 7, MAX_EDGE_NUM = 50;
    bool r0[] = { false, true, false, false, false, false, false };
    bool r1[] = { false, false, true, true, true, false, false };
    bool r2[] = { false, true, false, false, false, false, false };
    bool r3[] = { false, false, false, false, true, false, false };
    bool r4[] = { false, false, false, false, false, true, true };
    bool r5[] = { false, false, false, false, false, false, true };
    bool r6[] = { true, true, false, false, false, false, false };
    const bool *adjMatrix[N] = { r0, r1, r2, r3, r4, r5, r6 };

    int edgeCount = 0;
    int eulerianPath[MAX_EDGE_NUM];
    Solution so;

    bool isEulerianPath = so.determineEulerianCycle(adjMatrix, N, eulerianPath, edgeCount);
    return 0;
}