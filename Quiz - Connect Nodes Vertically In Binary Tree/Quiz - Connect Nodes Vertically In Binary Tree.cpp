// Quiz - Connect Nodes Vertically In Binary Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef struct __TreeNode
{
    int                     val;
    __TreeNode  *left;
    __TreeNode  *right;
    __TreeNode  *next;
    __TreeNode(int v) : val(v), left(NULL), right(NULL), next(NULL) {}
}TreeNode;

typedef  int    NODEDEGREE;

class Solution
{
public:
    void    connectNodesVertically(TreeNode*    root)
    {
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return;

        connectNodesVertically(root, 0);
    }

private:
    unordered_map<NODEDEGREE, TreeNode*>    mapA;
    unordered_set<TreeNode*>    visitedMap;

    void connectNodesVertically(TreeNode*    root, NODEDEGREE degree)
    {
        if (visitedMap.find(root) != visitedMap.end()) //this node has been visited. Just return.
            return;

        if (root->left)
            connectNodesVertically(root->left, degree - 1);
        if (root->right)
            connectNodesVertically(root->right, degree + 1);

        visitedMap.insert(root); //mark root as has been visited.

        if (mapA.find(degree) == mapA.end())
        {
            mapA[degree] = root;
            return;
        }

        root->next = mapA[degree];
        mapA[degree] = root;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

