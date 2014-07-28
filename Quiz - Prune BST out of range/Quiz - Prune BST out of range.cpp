// Quiz - Prune BST out of range.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;

typedef struct __TreeNode
{
    int         val;
    __TreeNode* left;
    __TreeNode* right;
    __TreeNode(int v = 0) : val(v), left(NULL), right(NULL) {}
}TreeNode;

class Solution
{
public:
    TreeNode* pruneBST(TreeNode* root, int minVal, int maxVal, vector<TreeNode*> &deletedNodes)
    {
        if (root == NULL)   return NULL;

        if (root->val < minVal)
        {
            TreeNode* rightTree = root->right;
            root->right = NULL;
            DestroyTree(root, deletedNodes);
            TreeNode* newRoot = pruneBST(rightTree, minVal, maxVal, deletedNodes);
            return newRoot;
        }

        if (root->val > maxVal)
        {
            TreeNode* leftTree = root->left;
            root->left = NULL;
            DestroyTree(root, deletedNodes);
            TreeNode* newRoot = pruneBST(leftTree, minVal, maxVal, deletedNodes);
            return newRoot;
        }

        root->left = pruneBST(root->left, minVal, maxVal, deletedNodes);
        root->right = pruneBST(root->right, minVal, maxVal, deletedNodes);
        return root;
    }

private:
    void DestroyTree(TreeNode* root, vector<TreeNode*> &deletedNodes)
    {
        if (root == NULL)   return;
        DestroyTree(root->left, deletedNodes);
        DestroyTree(root->right, deletedNodes);
        root->left = root->right = NULL;
        deletedNodes.push_back(root);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    TreeNode    node18(18);
    TreeNode    node10(10);
    TreeNode    node30(30);
    TreeNode    node6(6);
    TreeNode    node12(12);
    TreeNode    node25(25);
    TreeNode    node40(40);
    TreeNode    node8(8);
    TreeNode    node3(3);
    TreeNode    node11(11);
    TreeNode    node15(15);
    TreeNode    node42(42);
    TreeNode    node48(48);

    node18.left = &node10;
    node18.right = &node30;
    node10.left = &node6;
    node10.right = &node12;
    node30.left = &node25;
    node30.right = &node40;
    node6.left = &node3;
    node6.right = &node8;
    node12.left = &node11;
    node12.right = &node15;
    node40.left = &node42;
    node40.right = &node48;

    Solution so;
    vector<TreeNode*>   deletedNodes;
    int target1 = 7, target2 = 28;
    TreeNode* result = so.pruneBST(&node18, target1, target2, deletedNodes);

	return 0;
}

