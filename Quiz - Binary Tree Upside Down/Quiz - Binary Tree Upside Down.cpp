// Given a binary tree where all the right nodes are leaf nodes, flip it upside down and turn it into a tree with left leaf nodes.
/* for example, turn these:
*
*        1                 1
*       / \               / \
*      2   3          2   3
*     / \
*    4   5
*   / \
*  6   7
*
* into these:
*
*     6                   2
*    / \                 / \
*   7   4             3   1
*        / \
*       5   2
*            / \
*          3   1      */


#include <iostream>
#include <stack>
#include "BinaryTree.h"
using namespace std;

TreeNode* upsideDown(TreeNode* root){
    if (root == NULL) return root;

    stack<TreeNode*> stackA;
    TreeNode *curNode = root, *parent = NULL;
    while (curNode) {
        stackA.push(curNode); curNode = curNode->left;
    }

    root = stackA.top();
    while (!stackA.empty()) {
        curNode = stackA.top(); stackA.pop();
        if (stackA.empty()) parent = NULL;
        else parent = stackA.top();

        curNode->left = parent ? parent->right : NULL;
        curNode->right = parent;
    }
    return root;
}


int main()
{
    int arr[] = { 1, 2, 4, 6, END_NODE_FLAG, END_NODE_FLAG, 7, END_NODE_FLAG, END_NODE_FLAG, 5, END_NODE_FLAG, END_NODE_FLAG, 3, END_NODE_FLAG, END_NODE_FLAG};
    TreeNode *root = constructBinaryTreeByPreorder(arr, sizeof(arr) / sizeof(int));
    root = upsideDown(root);
	return 0;
}

