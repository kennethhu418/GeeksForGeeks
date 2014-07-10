// Quiz - Pair Sum In BST.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <time.h>
#include <algorithm>

using namespace std;

typedef struct __TreeNode
{
    int                     val;
    __TreeNode  *left;
    __TreeNode  *right;
    __TreeNode(int v) : val(v), left(NULL), right(NULL) {}
}TreeNode;

typedef struct __TreeNodePair
{
    TreeNode    *node1;
    TreeNode    *node2;
    __TreeNodePair(TreeNode    *n1 = NULL, TreeNode* n2 = NULL) : node1(n1), node2(n2){}
}TreeNodePair;

class Solution
{
public:
    TreeNodePair    searchSumPair(TreeNode* root, int targetSum)
    {
        TreeNodePair    result;
        if (root == NULL)   return result;

        //Initialize stack
        InitializeStack(root);

        //Now begin search
        TreeNode    *curNode1 = NULL, *curNode2 = NULL;
        int curSum = 0;
        while (leftStack.top() != rightStack.top())
        {
            curNode1 = leftStack.top();
            curNode2 = rightStack.top();

            curSum = curNode1->val + curNode2->val;
            if (curSum == targetSum)
            {
                result.node1 = curNode1;
                result.node2 = curNode2;
                ClearStack();
                return result;
            }

            if (targetSum > curSum)
            {
                leftStack.pop();
                curNode1 = curNode1->right;
                while (curNode1)
                {
                    leftStack.push(curNode1);
                    curNode1 = curNode1->left;
                }
            }
            else
            {
                rightStack.pop();
                curNode2 = curNode2->left;
                while (curNode2)
                {
                    rightStack.push(curNode2);
                    curNode2 = curNode2->right;
                }
            }
        }

        ClearStack();
        return result; //did not find any pair, return the invalidated result
    }

private:
    stack<TreeNode*>    leftStack;
    stack<TreeNode*>    rightStack;

    void InitializeStack(TreeNode* root)
    {
        TreeNode*   curNode = root;
        while (curNode)
        {
            leftStack.push(curNode);
            curNode = curNode->left;
        }

        curNode = root;
        while (curNode)
        {
            rightStack.push(curNode);
            curNode = curNode->right;
        }
    }

    void ClearStack()
    {
        while (!leftStack.empty())
            leftStack.pop();
        while (!rightStack.empty())
            rightStack.pop();
    }
};

TreeNode* constructBST(int arr[], int start, int end)
{
    if (start > end)    return NULL;
    int mid = (start + end) / 2;

    TreeNode*   root = new TreeNode(arr[mid]);
    root->left = constructBST(arr, start, mid - 1);
    root->right = constructBST(arr, mid + 1, end);
    return root;
}

TreeNode*   constructBST(int arr[], int n)
{
    if (n == 0) return NULL;
    TreeNode*   root = constructBST(arr, 0, n - 1);
    return root;
}

void RandomFillArray(int arr[], int n, int maxVal)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (maxVal + 1);

    sort(arr, arr + n);
}

void PrintArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << "  ";
}

int _tmain(int argc, _TCHAR* argv[])
{
    const   unsigned int    MAX_ARRAY_LEN = 30;
    const   unsigned int    MAX_VAL = 50;
    int dataArr[MAX_ARRAY_LEN];
    int dataArrSize = 10;
    int targetSum;
    TreeNode*   root = NULL;
    Solution    so;
    TreeNodePair    result;

    srand(time(0));

    cout << "Input array length (ctrl + z to exit): ";
    while (cin >> dataArrSize)
    {
        if (dataArrSize == 0)
            dataArrSize = 1;
        else if (dataArrSize > MAX_ARRAY_LEN)
            dataArrSize = MAX_ARRAY_LEN;

        RandomFillArray(dataArr, dataArrSize, MAX_VAL);
        cout << "The array is:" << endl;
        PrintArray(dataArr, dataArrSize);
        cout << endl << endl;

        root = constructBST(dataArr, dataArrSize);
        cout << "Input target Sum (ctrl + z to exit): ";
        while (cin >> targetSum)
        {
            if (targetSum == -11)
                break;

            result = so.searchSumPair(root, targetSum);
            if (result.node1 == NULL)
                cout << "No match pair !" << endl;
            else
                cout << result.node1->val << ", " << result.node2->val << endl;

            cout << "Input target Sum (ctrl + z to exit): ";
        }

        cout << "============================================" << endl;
        cout << "Input array length (ctrl + z to exit): ";
    }

	return 0;
}

