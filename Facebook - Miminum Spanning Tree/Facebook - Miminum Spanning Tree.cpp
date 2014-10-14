//  prim algorithm determine Minimum Spanning Tree 

#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
using namespace std;

class GraphNode;

class Edge
{
public:
    GraphNode*    from;
    GraphNode*    to;
    int           weight;
    Edge(GraphNode* from = NULL, GraphNode* to = NULL, int weight = 0) : from(from), to(to), weight(weight) {}
};

class EdgeComparor
{
public:
    bool operator() (const Edge &e1, const Edge &e2) {
        return e1.weight > e2.weight;
    }
};

class GraphNode
{
public:
    char        data;
    vector<GraphNode*> neighbors;
    vector<int> weights;
    GraphNode(char data = '\0') :data(data) {}
};

class Solution
{
public:
    vector<Edge> searchMST(GraphNode* rootNode) {
        vector<Edge> resultArr;
        if (rootNode == NULL) return resultArr;

        unordered_set<GraphNode*> visitedNodes;
        priority_queue<Edge, vector<Edge>, EdgeComparor> minHeap;

        //Initialize minHeap
        for (int i = 0; i < rootNode->neighbors.size(); ++i) {
            Edge e(rootNode, rootNode->neighbors[i], rootNode->weights[i]);
            minHeap.push(e);
        }
        visitedNodes.insert(rootNode);

        //Run logic
        while (!minHeap.empty()) {
            Edge e = minHeap.top(); minHeap.pop();
            if (visitedNodes.find(e.to) != visitedNodes.end()) continue;
            rootNode = e.to;

            resultArr.push_back(e);
            visitedNodes.insert(e.to);

            for (int i = 0; i < rootNode->neighbors.size(); ++i) {
                if (visitedNodes.find(rootNode->neighbors[i]) != visitedNodes.end()) continue;
                Edge e(rootNode, rootNode->neighbors[i], rootNode->weights[i]);
                minHeap.push(e);
            }
        }
        return resultArr;
    }
};

int main()
{
    GraphNode nodeA('A');
    GraphNode nodeB('B');
    GraphNode nodeC('C');
    GraphNode nodeD('D');
    GraphNode nodeE('E');
    GraphNode nodeF('F');

    nodeA.neighbors.push_back(&nodeB); nodeA.weights.push_back(5);
    nodeA.neighbors.push_back(&nodeD); nodeA.weights.push_back(8);
    nodeA.neighbors.push_back(&nodeF); nodeA.weights.push_back(4);

    nodeB.neighbors.push_back(&nodeA); nodeB.weights.push_back(5);
    nodeB.neighbors.push_back(&nodeD); nodeB.weights.push_back(6);

    nodeD.neighbors.push_back(&nodeA); nodeD.weights.push_back(8);
    nodeD.neighbors.push_back(&nodeB); nodeD.weights.push_back(6);
    nodeD.neighbors.push_back(&nodeE); nodeD.weights.push_back(7);
    nodeD.neighbors.push_back(&nodeC); nodeD.weights.push_back(2);
    nodeD.neighbors.push_back(&nodeF); nodeD.weights.push_back(3);

    nodeE.neighbors.push_back(&nodeC); nodeE.weights.push_back(8);
    nodeE.neighbors.push_back(&nodeD); nodeE.weights.push_back(7);

    nodeC.neighbors.push_back(&nodeF); nodeC.weights.push_back(5);
    nodeC.neighbors.push_back(&nodeD); nodeC.weights.push_back(2);
    nodeC.neighbors.push_back(&nodeE); nodeC.weights.push_back(8);

    nodeF.neighbors.push_back(&nodeA); nodeF.weights.push_back(4);
    nodeF.neighbors.push_back(&nodeD); nodeF.weights.push_back(3);
    nodeF.neighbors.push_back(&nodeC); nodeF.weights.push_back(5);

    Solution so;
    vector<Edge> resultArr = so.searchMST(&nodeA);
    return 0;
}