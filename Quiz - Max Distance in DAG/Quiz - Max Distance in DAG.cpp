// Quiz - Max Distance in DAG.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

#define INVALID_DISTANCE  0x80000000

typedef struct __GraphNode
{
    int                             label;
    vector<__GraphNode*>  neighbors;
    vector<int>             weights;
    __GraphNode(int label) : label(label){}
}GraphNode;

class Solution
{
public:
    vector<int> getMaxDistancesSingleSource(GraphNode* srcNode, int maxLabel)
    {
        vector<int> result(maxLabel + 1);
        for (int i = 0; i <= maxLabel; ++i) result[i] = INVALID_DISTANCE;
        if (srcNode == NULL)    return result;

        initialize(maxLabel + 1);
        sortGraphNodes(srcNode);
        result[srcNode->label] = 0;

        GraphNode*  curNode = NULL, *curNeighbor = NULL;
        for (int i = topologySortedNodes.size() - 1; i >= 0; --i)
        {
            curNode = topologySortedNodes.at(i);
            for (int j = 0; j < curNode->neighbors.size(); ++j)
            {
                curNeighbor = curNode->neighbors.at(j);
                if (curNode->weights[j] + result[curNode->label] > result[curNeighbor->label])
                    result[curNeighbor->label] = curNode->weights[j] + result[curNode->label];
            }
        }

        return result;
    }

private:
    vector<GraphNode*>     topologySortedNodes;
    vector<bool>        visited;

    void initialize(int n)
    {
        visited.resize(n);
        topologySortedNodes.clear();
        for (int i = 0; i < n; i++) visited[i] = false;
    }

    void    sortGraphNodes(GraphNode*   startingNode)
    {
        int n = startingNode->neighbors.size();
        for (int i = 0; i < n; i++)
        {
            if (visited[startingNode->neighbors[i]->label]) continue;
            sortGraphNodes(startingNode->neighbors[i]);
        }
        visited[startingNode->label] = true;
        topologySortedNodes.push_back(startingNode);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    GraphNode   node0(0);
    GraphNode   node1(1);
    GraphNode   node2(2);
    GraphNode   node3(3);
    GraphNode   node4(4);
    GraphNode   node5(5);

    node0.neighbors.push_back(&node1);
    node0.neighbors.push_back(&node2);
    node0.weights.push_back(8);
    node0.weights.push_back(3);

    node1.neighbors.push_back(&node2);
    node1.neighbors.push_back(&node4);
    node1.neighbors.push_back(&node5);
    node1.weights.push_back(7);
    node1.weights.push_back(9);
    node1.weights.push_back(2);

    node2.neighbors.push_back(&node3);
    node2.neighbors.push_back(&node4);
    node2.weights.push_back(1);
    node2.weights.push_back(10);

    node3.neighbors.push_back(&node4);
    node3.weights.push_back(4);

    Solution so;
    vector<int> distantArr = so.getMaxDistancesSingleSource(&node0, 5);

	return 0;
}

