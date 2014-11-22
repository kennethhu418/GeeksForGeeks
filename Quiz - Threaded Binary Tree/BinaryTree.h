#pragma once

#ifndef __BINARY__TREE__
#define __BINARY__TREE__

#include <cstdlib>

#define END_NODE_FLAG 0xF5EEDAC0

typedef struct __TreeNode
{
    int             val;
    __TreeNode      *left;
    __TreeNode      *right;
    bool         right_threaded; //its right pointer is not actually its right child, the right pointer is actually a threaded edge
    __TreeNode(int val) : val(val), left(NULL), right(NULL), right_threaded (false) {}
}TreeNode;

static TreeNode *constructBinaryTreeByPreorder(int dataArr[], int n, int &curPos)
{
    if (curPos == n) return NULL;
    if (dataArr[curPos] == END_NODE_FLAG){
        ++curPos;
        return NULL;
    }

    TreeNode *root = new TreeNode(dataArr[curPos++]);
    root->left  = constructBinaryTreeByPreorder(dataArr, n, curPos);
    root->right = constructBinaryTreeByPreorder(dataArr, n, curPos);
    return root;
}

static TreeNode *constructBinaryTreeByPreorder(int dataArr[], int n)
{
    int pos = 0;
    TreeNode* root = constructBinaryTreeByPreorder(dataArr, n, pos);
    return root;
}

static void DestroyTree(TreeNode* root)
{
    if (root == NULL) return;
    DestroyTree(root->left);
    if (!root->right_threaded)
        DestroyTree(root->right);
    delete root;
}

static void generatePreorderSequenceTopDown(TreeNode* root, int arr[], int &n)
{
    if (root == NULL){
        arr[n++] = END_NODE_FLAG;
        return;
    }

    arr[n++] = root->val;
    generatePreorderSequenceTopDown(root->left, arr, n);
    generatePreorderSequenceTopDown(root->right, arr, n);
}

static int generatePreorderSequence(TreeNode* root, int arr[])
{
    if (root == NULL) return 0;
    int curPos = 0;
    generatePreorderSequenceTopDown(root, arr, curPos);
    return curPos;
}

#endif