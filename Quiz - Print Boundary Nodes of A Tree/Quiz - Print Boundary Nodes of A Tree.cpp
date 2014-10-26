#include <iostream>
#include <stack>
using namespace std;

typedef struct __TreeNode
{
    int        val;
    __TreeNode *left;
    __TreeNode *right;
    __TreeNode(int val) : val(val), left(NULL), right(NULL) {}
}TreeNode;

class Solution
{
private:
    void print(TreeNode* node) {
        cout << node->val << " ";
    }

public:
    void printBoundaryNodes(TreeNode* root) {
        if (root == NULL) return;
        stack<TreeNode*> stackA;
        TreeNode *curNode = root;
        while (curNode) {
            stackA.push(curNode); print(curNode);
            curNode = curNode->left;
        }

        //the most left leaf node which is on the left boundary edge should
        //not be printed twice
        if (stackA.top()->left == NULL && stackA.top()->right == NULL) stackA.pop();

        while (!stackA.empty()) {
            curNode = stackA.top(); stackA.pop();
            if (curNode->left == NULL && curNode->right == NULL) print(curNode);
            curNode = curNode->right;
            while (curNode) {
                stackA.push(curNode); curNode = curNode->left;
            }
        }

        curNode = root;
        while (curNode) {
            stackA.push(curNode); curNode = curNode->right;
        }

        //the most right leaf node which is on the right boundary edge should
        //not be printed twice
        if (stackA.top()->left == NULL && stackA.top()->right == NULL) stackA.pop();
        while (stackA.size() > 1) { //root node has already been printed, so do not print it
            print(stackA.top()); stackA.pop();
        }
        cout << endl;
    }
};

int main(){
    TreeNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node10(10), node11(11);
    node1.left = &node2; node1.right = &node3;
    node2.left = &node4; node2.right = &node6;
    node3.right = &node5; node6.left = &node7;
    node5.left = &node10; node5.right = &node11;

    Solution so;
    so.printBoundaryNodes(&node1);
    return 0;
}