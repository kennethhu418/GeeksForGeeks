//In graph theory, a biconnected graph is a connected and "nonseparable" graph, meaning that if any vertex were to be removed, 
//the graph will remain connected. Therefore a biconnected graph has no articulation vertices.
//To be more specific, in a graph,  we can remove any one vertex. If any two nodes in the remaining graph still have path to each other, 
//then the graph is called biconnected.
//
//A biconnected component is a maximal biconnected subgraph.
//
//Please find all biconnected component in a given graph.
//
//http://www.geeksforgeeks.org/biconnectivity-in-a-graph/
//http ://www.geeksforgeeks.org/biconnected-components/

//Solution:
//Algorithm is based on Disc and Low Values discussed in Strongly Connected Components.

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

typedef struct __Edge
{
    int         src;
    int         dest;
    __Edge(int src = 0, int dest = 0) : src(src), dest(dest) {}
}Edge;

class UndirectedGraph
{
public:
    UndirectedGraph(int n = 10) {
        mVertexCount = n;
        mAdjMatrix = new bool*[n];
        for (int i = 0; i < n; ++i) {
            mAdjMatrix[i] = new bool[n];
            memset(mAdjMatrix[i], 0, n * sizeof(bool));
        }
    }

    ~UndirectedGraph() {
        for (int i = 0; i < mVertexCount; ++i)
            delete[] mAdjMatrix[i];
        delete mAdjMatrix;
    }

    void addEdge(int src, int dest) {
        mAdjMatrix[src][dest] = true;
        mAdjMatrix[dest][src] = true;
    }

    void removeEdge(int src, int dest) {
        mAdjMatrix[src][dest] = false;
        mAdjMatrix[dest][src] = false;
    }

    int getVertexCount() const {
        return mVertexCount;
    }

    bool hasEdge(int src, int dest) const {
        return mAdjMatrix[src][dest];
    }

private:
    int                     mVertexCount;
    bool                 **mAdjMatrix;
};

class Solution {
public:
    vector<vector<int>> searchBiconnectedComponents(const UndirectedGraph &graph) {
        int n = graph.getVertexCount();
        Initialize(n);
        if (n == 0) return mResultArr;
    
        for (int i = 0; i < n; ++i) {
            if (mStampArr[i]) continue;
            search(graph, i);
        }

        Free();
        return mResultArr;
    }

private:
    vector<vector<int>> mResultArr;
    stack<Edge>  mStack;
    unordered_set<int> mSet;
    int *mStampArr;
    int mStampVal;

    void Initialize(int n) {
        if (n == 0) return;
        mResultArr.clear();        
        mStampArr = new int[n];
        memset(mStampArr, 0, n * sizeof(int));
        mStampVal = 1;
    }

    void Free() {
        while (!mStack.empty()) mStack.pop();
        delete[] mStampArr;
        mStampArr = NULL;
        mStampVal = 0;
    }

    int search(const UndirectedGraph &graph, int curNode) {
        mStampArr[curNode] = mStampVal++;

        Edge edge;
        int childCount = 0, n = graph.getVertexCount(), lowestStamp = mStampArr[curNode], childStamp = 0;
        for (int i = 0; i < n; ++i) {
            if (!graph.hasEdge(curNode, i)) continue;
            if (mStampArr[i]) {
                if (mStampArr[i] < lowestStamp) {
                    lowestStamp = mStampArr[i];
                    edge.src = curNode; edge.dest = i;
                    mStack.push(edge);
                }
            }
            else {
                ++childCount;
                edge.src = curNode; edge.dest = i;
                mStack.push(edge);
                childStamp = search(graph, i);
                if (childStamp == mStampArr[curNode])
                    constructComponent(edge);
                else
                    lowestStamp = min(lowestStamp, childStamp);
            }        
        }

        if (childCount == 0 && mStack.size() == 1)
            constructComponent(curNode);

        return lowestStamp;
    }

    void constructComponent(Edge targetEdge) {
        vector<int> result;
        Edge curEdge;
        while (!mStack.empty()) {
            curEdge = mStack.top(); mStack.pop();
            if (mSet.find(curEdge.src) == mSet.end()) mSet.insert(curEdge.src);
            if (mSet.find(curEdge.dest) == mSet.end()) mSet.insert(curEdge.dest);
            if (targetEdge.src == curEdge.src && targetEdge.dest == curEdge.dest) break;
        }
        for (unordered_set<int>::iterator iter = mSet.begin(); iter != mSet.end(); iter++)
            result.push_back(*iter);
        sort(result.begin(), result.end());
        mResultArr.push_back(result);
        mSet.clear();
    }
};

void OutputArray(const vector<vector<int>> &resultArr) {
    cout << "There are totally " << resultArr.size() << " biconnected components." << endl;
    for (int i = 0; i < resultArr.size(); ++i) {
        cout << "The " << i + 1 << " Component:" << endl;
        for (int j = 0; j < resultArr[i].size(); ++j)
            cout << resultArr[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Please see the attachment "test example.png" under the project folder for the example illustration
    UndirectedGraph graph(12);
    graph.addEdge(0, 1); graph.addEdge(0, 6);
    graph.addEdge(1, 2); graph.addEdge(1, 3);  graph.addEdge(1, 5);
    graph.addEdge(2, 3); graph.addEdge(2, 4);    
    graph.addEdge(3, 4);
    graph.addEdge(5, 6); graph.addEdge(5, 7); graph.addEdge(5, 8);
    graph.addEdge(7, 8);
    graph.addEdge(8, 9);
    graph.addEdge(10, 11);

    Solution so;
    vector<vector<int>> resultArr = so.searchBiconnectedComponents(graph);
    OutputArray(resultArr);
    return 0;
}