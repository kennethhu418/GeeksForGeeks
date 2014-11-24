#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include "BinaryTree.h"
using namespace std;

class Solution
{
public:
    vector<int> topView(TreeNode* root) {
        vector<int>  resultArr;
        if (root == NULL) return resultArr;

        // First get globally min and max vertical levels
        // Here we use iterative implementation.
        int minL = INT_MAX, maxL = INT_MIN, curLevel = 0;
        stack<TreeNode*> nodeStack; stack<int> levelStack;
        TreeNode* node = root;
        while (node) {
            if (curLevel < minL) minL = curLevel;
            if (curLevel > maxL) maxL = curLevel;
            levelStack.push(curLevel);
            nodeStack.push(node);
            node = node->left;
            curLevel--;
        }

        while (!nodeStack.empty()) {
            node = nodeStack.top(); curLevel = levelStack.top();
            nodeStack.pop(); levelStack.pop();
            node = node->right; curLevel++;
            while (node) {
                if (curLevel < minL) minL = curLevel;
                if (curLevel > maxL) maxL = curLevel;
                levelStack.push(curLevel);
                nodeStack.push(node);
                node = node->left;
                curLevel--;
            }
        }
        
        int levelCount = maxL - minL + 1;
        resultArr.resize(levelCount);

        // Now let's do level order traversal
        queue<TreeNode*> nodeQ; queue<int> levelQ;
        nodeQ.push(root); levelQ.push(0);
        int curSeenMinLevel = INT_MAX, curSeenMaxLevel = INT_MIN;
        while (!nodeQ.empty()) {
            node = nodeQ.front(); curLevel = levelQ.front();
            nodeQ.pop(); levelQ.pop();

            if (node->left) {
                nodeQ.push(node->left); levelQ.push(curLevel - 1);
            }
            if (node->right) {
                nodeQ.push(node->right); levelQ.push(curLevel + 1);
            }

            if (curLevel < curSeenMinLevel) {
                curSeenMinLevel = curLevel;
                resultArr[curLevel - minL] = node->val;
            }
            if (curLevel > curSeenMaxLevel) {
                curSeenMaxLevel = curLevel;
                resultArr[curLevel - minL] = node->val;
            }
        }      

        return resultArr;
    }
};

int main()
{
    int arr[] = { 0, 1, 9, END_NODE_FLAG, END_NODE_FLAG, 8, 3, 10, 11, END_NODE_FLAG, END_NODE_FLAG, \
        END_NODE_FLAG, END_NODE_FLAG, END_NODE_FLAG, 4, 6, END_NODE_FLAG, 19, END_NODE_FLAG, 21, END_NODE_FLAG, \
        END_NODE_FLAG, 7, END_NODE_FLAG, END_NODE_FLAG };
    TreeNode* root = constructBinaryTreeByPreorder(arr, sizeof(arr) / sizeof(int));
    Solution so;
    vector<int>  result = so.topView(root);
    DestroyTree(root);
    for (int i = 0; i < result.size(); ++i) cout << result.at(i) << "  ";
    cout << endl;
    return 0;
}