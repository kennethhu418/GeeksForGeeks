// Quiz - Least Common Ansestor.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct __TreeNode
{
    int val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int data) : val(data), left(NULL), right(NULL){}
}TreeNode;

class Solution
{
public:
    TreeNode*   getLCA(TreeNode* root, TreeNode* target1, TreeNode* target2)
    {
        TreeNode* foundTarget = NULL;
        foundOneOfTarget = false;

        return getLCA(root, target1, target2, foundTarget);
    }

private:
    bool foundOneOfTarget;

    TreeNode*   getLCA(TreeNode* root, TreeNode* target1, TreeNode* target2, TreeNode* &foundTarget)
    {
        if (root == NULL)
            return NULL;

        TreeNode* lcaNode = NULL;
        TreeNode* foundTargetLeft = NULL;
        TreeNode* foundTargetRight = NULL;

        if (root == target1 || root == target2)
        {
            if (foundOneOfTarget)
            {
                foundTarget = root;
                return NULL;
            }

            lcaNode = getLCA(root->left, target1, target2, foundTargetLeft);
            if (foundTargetLeft)
                return root;
            lcaNode = getLCA(root->right, target1, target2, foundTargetRight);
            if (foundTargetRight)
                return root;

            foundTarget = root;
            foundOneOfTarget = true;
            return NULL;
        }

        lcaNode = getLCA(root->left, target1, target2, foundTargetLeft);
        if (lcaNode)
            return lcaNode;
        lcaNode = getLCA(root->right, target1, target2, foundTargetRight);
        if (lcaNode)
            return lcaNode;

        if (foundTargetLeft && foundTargetRight)
            return root;

        foundTarget = foundTargetLeft ? foundTargetLeft : foundTargetRight;
        return NULL;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{

}

