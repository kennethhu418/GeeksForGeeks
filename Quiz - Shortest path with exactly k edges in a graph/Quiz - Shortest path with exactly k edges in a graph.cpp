// Given a directed and weighted graph (there can be cycles in it) and also given two vertices ¡®u¡¯ and ¡®v¡¯ in it, 
// find shortest path from ¡®u¡¯ to ¡®v¡¯ with exactly K edges on the path.
// Author : Kenneth
// Idea: DP
// Time complexity: O(KE), where E is the number of edges in the whole graph and K is the given steps
#include <iostream>
#include <vector>
using namespace std;

#define MAX_V 10
#define MAX_K 30
#define INVALID_DISTANCE 0x400000

static int resultArr[MAX_V][MAX_K + 1];
static int stepArr[MAX_V][MAX_K + 1];

typedef struct __GraphNode
{
    int                         label;
    vector<int>        neighbors;
    vector<int>        weights;
    __GraphNode(int label) : label(label) {}
}GraphNode;

int getMinDistance(const GraphNode* graphArr, int n, int src, int dest, int K, vector<int> &stepSolution) {
    stepSolution.clear();

    if (K == 0) {
        if (src == dest) {
            stepSolution.push_back(src); return 0;
        }
        return INVALID_DISTANCE;
    }

    for (int i = 0; i < n; ++i)
        resultArr[i][0] = INVALID_DISTANCE;
    resultArr[dest][0] = 0;

    vector<int>::const_iterator iter1, iter2;
    for (int k = 1; k <= K; ++k) {
        for (int i = 0; i < n; ++i) {
            resultArr[i][k] = INVALID_DISTANCE;
            for (iter1 = graphArr[i].neighbors.begin(), iter2 = graphArr[i].weights.begin(); iter1 != graphArr[i].neighbors.end(); iter1++, iter2++) {
                if (resultArr[i][k] > *iter2 + resultArr[*iter1][k - 1]) {
                    resultArr[i][k] = *iter2 + resultArr[*iter1][k - 1];
                    stepArr[i][k] = *iter1;
                }
            }
        }
    }

    if (resultArr[src][K] != INVALID_DISTANCE) {
        stepSolution.push_back(src);
        int curPos = src;
        for (int i = 0; i < K; ++i) {
            stepSolution.push_back(stepArr[curPos][K - i]);
            curPos = stepArr[curPos][K - i];
        }
    }

    return resultArr[src][K];
}

int main() {
    GraphNode graphArr[] = { 0, 1, 2, 3, 4 };
    int n = sizeof(graphArr) / sizeof(GraphNode);
    int src = 0, dest = 4, K = 1;
    vector<int> solutionArr;

    graphArr[0].neighbors.push_back(1); graphArr[0].weights.push_back(10);
    graphArr[0].neighbors.push_back(2); graphArr[0].weights.push_back(16);

    graphArr[1].neighbors.push_back(2); graphArr[1].weights.push_back(5);
    graphArr[1].neighbors.push_back(3); graphArr[1].weights.push_back(20);

    graphArr[2].neighbors.push_back(3); graphArr[2].weights.push_back(1);
    graphArr[2].neighbors.push_back(4); graphArr[2].weights.push_back(5);

    graphArr[3].neighbors.push_back(0); graphArr[3].weights.push_back(3);
    graphArr[3].neighbors.push_back(4); graphArr[3].weights.push_back(3);

    graphArr[4].neighbors.push_back(2); graphArr[4].weights.push_back(2);

    for (int K = 2; K <= MAX_K; ++K) {
        cout << "\n*****************************************************\n";
        cout << "Min Dist with " << K << " steps is " << getMinDistance(graphArr, n, src, dest, K, solutionArr) << endl;
        cout << "The walk path is: \n  ";
        for (int i = 0; i < solutionArr.size(); ++i) cout << solutionArr[i] << " ";
        cout << endl;
    }
    return 0;
}