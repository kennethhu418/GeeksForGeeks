//  Given a very large n - ary tree. Where the root node has some information which 
//  it wants to pass to all of its children down to the leaves with the constraint 
//  that it can only pass the information to one of its children at a time(take it 
//  as one iteration).Now in the next iteration the child node can transfer that 
//  information to only one of its children and at the same time instance the child¡¯s 
//  parent i.e.root can pass the info to one of its remaining children.Continuing in 
//  this way we have to find the minimum no of iterations required to pass the 
//  information to all nodes in the tree.
//  
//  Minimum no of iterations for tree below (see the attachment) is 6. 
//  Consider passing root information first to any child except A - B answer 
//  will come more then 7. So 6 is the minimum answer.

#include <iostream>
#include <queue>
using namespace std;

#define MAX_CHILDREN_COUNT 6
typedef struct __TreeNode
{
    char        data;
    __TreeNode  *children[MAX_CHILDREN_COUNT];
    int childrenCount;
    __TreeNode(char data = '\0') : data(data), childrenCount(0) {}
}TreeNode;

typedef priority_queue<int, vector<int>, less<int>> MaxHeap;

int calculateMinPasses(TreeNode *root) {
    if (root == NULL || root->childrenCount == 0) return 0;

    MaxHeap maxHeap;
    for (int i = 0; i < root->childrenCount; ++i)
        maxHeap.push(calculateMinPasses(root->children[i]));

    int curTime = 0;    // current time when we begin to pass information to one specific child
    int endTime = 0;   // current determined the end time of passing information
    int curChildPassingDuring = 0; // how many time units the current child should use to pass information to all its leaves
    int curChildPassingEndTime = 0; //the end time for current child to finish passing information to all its leaves
    while (!maxHeap.empty()) {
        curChildPassingDuring = maxHeap.top(); maxHeap.pop();
        ++curTime; //use 1 time unit to pass information to current child
        curChildPassingEndTime = curTime + curChildPassingDuring;
        if (curChildPassingEndTime > endTime)
            endTime = curChildPassingEndTime;    
    }
    return endTime;
}

int main()
{
    TreeNode nodeA('A'), nodeB('B'), nodeC('C'), nodeD('D'),
        nodeE('E'), nodeF('F'), nodeG('G'), nodeH('H'), nodeI('I'),
        nodeJ('J'), nodeK('K'), nodeL('L'), nodeM('M'), nodeN('N'),
        nodeO('O'), nodeP('P'), nodeQ('Q');
    nodeA.childrenCount = 6;
    nodeA.children[0] = &nodeB; nodeA.children[1] = &nodeC;
    nodeA.children[2] = &nodeD; nodeA.children[3] = &nodeE;
    nodeA.children[4] = &nodeF; nodeA.children[5] = &nodeG;
    nodeB.childrenCount = 3; nodeB.children[0] = &nodeH;
    nodeB.children[1] = &nodeI; nodeB.children[2] = &nodeJ;
    nodeE.childrenCount = 2; nodeE.children[0] = &nodeK; nodeE.children[1] = &nodeL;
    nodeG.childrenCount = 1; nodeG.children[0] = &nodeM;
    nodeH.childrenCount = 2; nodeH.children[0] = &nodeN; nodeH.children[1] = &nodeO;
    nodeK.childrenCount = 1; nodeK.children[0] = &nodeP;
    nodeL.childrenCount = 1; nodeL.children[0] = &nodeQ;
    cout << calculateMinPasses(&nodeA) << endl;
	return 0;
}

