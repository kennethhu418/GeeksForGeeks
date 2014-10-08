// Facebook - Sink Zero in Binary Tree.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "BinaryTree.h"
using namespace std;

int  SinkTopDown(TreeNode* root)
{
    if (root->val == 0) return 0;

    int val = root->val;

    if (root->left == NULL && root->right == NULL)
        root->val = 0;
    else if (root->left == NULL)
        root->val = SinkTopDown(root->right);
    else if (root->right == NULL)
        root->val = SinkTopDown(root->left);
    else if (root->left->val == 0)
        root->val = SinkTopDown(root->right);
    else
        root->val = SinkTopDown(root->left);

    return val;
}

void SinkZero(TreeNode* root)
{
    if (root == NULL)   return;

    SinkZero(root->left);
    SinkZero(root->right);

    if (root->val != 0) return;

    if (root->left == NULL && root->right == NULL) return;
    if (root->left == NULL)
        root->val = SinkTopDown(root->right);
    else if (root->right == NULL)
        root->val = SinkTopDown(root->left);
    else if (root->left->val == 0)
        root->val = SinkTopDown(root->right);
    else
        root->val = SinkTopDown(root->left);
}

void OutputArray(int arr[], int n)
{
    cout << "Size = " << n << endl;
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    const int MAX_SIZE = 200;

    int orgArr[] = { 0, 8, 9, 20, END_NODE_FLAG, END_NODE_FLAG, END_NODE_FLAG, \
        11, 0, 7, END_NODE_FLAG, END_NODE_FLAG, 9, END_NODE_FLAG, END_NODE_FLAG, \
        END_NODE_FLAG, 7, 0, 13, END_NODE_FLAG, END_NODE_FLAG, END_NODE_FLAG, 0, 12, \
        END_NODE_FLAG, END_NODE_FLAG, 0, 0, 1, END_NODE_FLAG, END_NODE_FLAG, 0, END_NODE_FLAG, \
        END_NODE_FLAG, 14, END_NODE_FLAG, END_NODE_FLAG };
    int n = sizeof(orgArr) / sizeof(int);

    int sinkedArr[MAX_SIZE] = {0};
    int sinkedn = 0;

    cout << "Original Tree is: " << endl;
    OutputArray(orgArr, n);
    TreeNode* root = constructBinaryTreeByPreorder(orgArr, n);

    cout << endl << "Sinked Zero Tree is: " << endl;
    SinkZero(root);
    sinkedn = generatePreorderSequence(root, sinkedArr);
    OutputArray(sinkedArr, sinkedn);
    return 0;
}

