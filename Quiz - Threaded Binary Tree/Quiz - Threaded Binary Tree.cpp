//  Inorder traversal of a Binary tree is either be done using recursion or with the use of a auxiliary stack.The idea of threaded binary trees is to 
//  make inorder traversal faster and do it without stack and without recursion.A binary tree is made threaded by making all right child pointers 
//  that would normally be NULL point to the inorder successor of the node(if it exists).
//  
//  There are two types of threaded binary trees.
//  Single Threaded : Where a NULL right pointers is made to point to the inorder successor(if successor exists)
//  
//  Double Threaded : Where both left and right NULL pointers are made to point to inorder predecessor and inorder successor respectively.
//  The predecessor threads are useful for reverse inorder traversal and postorder traversal.
//  
//  The threads are also useful for fast accessing ancestors of a node.
//  
//  http ://geeksquiz.com/threaded-binary-tree/
//
//  In this solution we only focus on single threaded binary tree, but for both inorder and preorder traversal

#include <iostream>
#include <vector>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class ThreadedTreeOperator
{
public:
    virtual void makeThreadedTree(TreeNode* root) = 0;

    virtual vector<int> traverseThreadedTree(TreeNode* root) = 0;
};

class Inorder_ThreadedTreeOperator : public ThreadedTreeOperator
{
public:
    void makeThreadedTree(TreeNode* root) {
        if (root == NULL) return;

        TreeNode *curNode = root, *prevNode = NULL;
        stack<TreeNode*> stackA;
        while (curNode) {
            stackA.push(curNode); curNode = curNode->left;
        }

        while (!stackA.empty()) {
            curNode = stackA.top(); stackA.pop();
            if (prevNode && prevNode->right == NULL) {
                prevNode->right = curNode;
                prevNode->right_threaded = true;
            }
            prevNode = curNode;

            // @@@@@@@@@@@@@ PAY ATTENTION: if it is right threaded, then it means it does not have right child actually. 
            // @@@@@@@@@@@@@ The right pointer is assigned during previous processing
            if (curNode->right_threaded)
                curNode = NULL;
            else
                curNode = curNode->right;
            while (curNode) {
                stackA.push(curNode); curNode = curNode->left;
            }
        }    
    }

    vector<int> traverseThreadedTree(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;

        TreeNode *curNode = root;
        while (curNode->left) curNode = curNode->left;

        while (curNode) {
            result.push_back(curNode->val);
            if (curNode->right == NULL) break;
            if (curNode->right_threaded)
                curNode = curNode->right;
            else {
                curNode = curNode->right;
                while (curNode->left) curNode = curNode->left;
            }
        }

        return result;
    }
};


class Preorder_ThreadedTreeOperator : public ThreadedTreeOperator
{
public:
    void makeThreadedTree(TreeNode* root) {
        if (root == NULL) return;

        TreeNode *curNode = root, *prevNode = NULL;
        stack<TreeNode*> stackA;
        while (curNode) {
            if (prevNode && prevNode->right == NULL) {
                prevNode->right = curNode; prevNode->right_threaded = true;
            }
            stackA.push(curNode); prevNode = curNode;
            curNode = curNode->left;
        }

        while (!stackA.empty()) {
            curNode = stackA.top(); stackA.pop();

            // @@@@@@@@@@@@@ PAY ATTENTION: if it is right threaded, then it means it does not have right child actually. 
            // @@@@@@@@@@@@@ The right pointer is assigned during previous processing
            if (curNode->right_threaded) 
                curNode = NULL;
            else
                curNode = curNode->right;
            while (curNode) {
                if (prevNode && prevNode->right == NULL) {
                    prevNode->right = curNode; prevNode->right_threaded = true;
                }
                stackA.push(curNode); prevNode = curNode;
                curNode = curNode->left;
            }
        }
    }

    vector<int> traverseThreadedTree(TreeNode* root) {
        vector<int> result;
        if (root == NULL) return result;

        TreeNode *curNode = root;
        while (curNode) {
            result.push_back(curNode->val);
            if (curNode->left)
                curNode = curNode->left;
            else
                curNode = curNode->right; //no matter it is right threaded or not, just go to right child
        }

        return result;
    }
};


void OutputArray(const vector<int> &dataArr) {
    for (vector<int>::const_iterator iter = dataArr.begin(); iter != dataArr.end(); iter++)
        cout << *iter << " ";
    cout << endl;
}

int main()
{
    ThreadedTreeOperator * treeOperator = NULL;
    TreeNode * tree = NULL;
    int treeArr[] = { 18, 10, 5, 1, END_NODE_FLAG, END_NODE_FLAG, END_NODE_FLAG, 12, END_NODE_FLAG, END_NODE_FLAG , 20, 19, \
        END_NODE_FLAG, END_NODE_FLAG, 25, 23, END_NODE_FLAG, END_NODE_FLAG, 29, END_NODE_FLAG, END_NODE_FLAG };
    vector<int> traverseResult;

    /**************** Test inorder threaded tree ****************/
    tree = constructBinaryTreeByPreorder(treeArr, sizeof(treeArr) / sizeof(int));
    treeOperator = new Inorder_ThreadedTreeOperator;
    treeOperator->makeThreadedTree(tree);
    traverseResult = treeOperator->traverseThreadedTree(tree);
    DestroyTree(tree); delete treeOperator;
    OutputArray(traverseResult);

    /**************** Test preorder threaded tree ****************/
    tree = constructBinaryTreeByPreorder(treeArr, sizeof(treeArr) / sizeof(int));
    treeOperator = new Preorder_ThreadedTreeOperator;
    treeOperator->makeThreadedTree(tree);
    traverseResult = treeOperator->traverseThreadedTree(tree);
    DestroyTree(tree); delete treeOperator;
    OutputArray(traverseResult);

	return 0;
}

