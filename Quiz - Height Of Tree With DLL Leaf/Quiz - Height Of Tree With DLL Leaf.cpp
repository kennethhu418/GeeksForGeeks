//Given a binary tree all the leaf nodes in the form of a doubly linked list.Find the height of the tree.
#include "stdafx.h"
#include <iostream>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

//Given a binary tree all the leaf nodes in the form of a doubly linked list.Find the height of the tree.
typedef struct __TreeNode
{
    int            val;
    __TreeNode     *left;
    __TreeNode     *right;
    __TreeNode(int val) : val(val), left(NULL), right(NULL) {}
}TreeNode;

class Solution
{
private:
    unordered_set<TreeNode*> mSet;

    TreeNode* searchFirstLeaf(TreeNode* root) {
        if (root == NULL) return NULL;
        if (mSet.find(root) != mSet.end()) return root;
        mSet.insert(root);

        TreeNode* result = searchFirstLeaf(root->left);
        if (result) { mSet.erase(root);  return result; }
        result = searchFirstLeaf(root->right);
        mSet.erase(root);
        return result;
    }

public:
    int getTreeHeight(TreeNode* root) {
        if (root == NULL) return 0;
        TreeNode* firstLeaf = searchFirstLeaf(root);
        TreeNode* curNode = firstLeaf->right;
        mSet.insert(firstLeaf);
        while (curNode != firstLeaf) {
            mSet.insert(curNode); curNode = curNode->right;
        }

        queue<TreeNode*> q1, q2, *curQ = &q1, *nextQ = &q2;
        curQ->push(root);
        int height = 0;
        while (!curQ->empty()) {
            while (!curQ->empty()) {
                curNode = curQ->front(); curQ->pop();
                if (mSet.find(curNode) != mSet.end()) continue;
                if (curNode->left) nextQ->push(curNode->left);
                if (curNode->right) nextQ->push(curNode->right);
            }
            swap(curQ, nextQ); ++height;
        }

        mSet.clear();
        return height;
    }
};


int main()
{
    Solution so;
    TreeNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7);
    n1.left = &n2; n1.right = &n4; n2.right = &n3; n4.left = &n5; n4.right = &n7; n5.right = &n6;
    n3.right = &n6; n3.left = &n7; n6.left = &n3; n6.right = &n7; n7.left = &n6; n7.right = &n3;

    cout << so.getTreeHeight(&n1) << endl;
    return 0;
}