#include <iostream>
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
public:
    int    calculateDistance(TreeNode* root, TreeNode *target1, TreeNode *target2) {
        if (root == NULL || target1 == NULL || target2 == NULL) return 0;
        mFoundResult = false;
        return calculateDistanceInternal(root, target1, target2);
    }

private:
    bool    mFoundResult;
    int calculateDistanceInternal(TreeNode* root, TreeNode *target1, TreeNode *target2) {
        if (root == NULL) return 0;
        if (root == target1 || root == target2) {
            if (target2 == NULL) return 1;
            int childHeight = calculateDistanceInternal(root->left, target1 == root ? target2 : target1, NULL);
            if (childHeight > 0) {
                mFoundResult = true; return childHeight;
            }
            childHeight = calculateDistanceInternal(root->right, target1 == root ? target2 : target1, NULL);
            if (childHeight > 0) {
                mFoundResult = true; return childHeight;
            }
            return 1;
        }

        int leftDist = 0, rightDist = 0;
        leftDist = calculateDistanceInternal(root->left, target1, target2);
        if (mFoundResult) return leftDist;
        rightDist = calculateDistanceInternal(root->right, target1, target2);
        if (mFoundResult) return rightDist;
        if (leftDist > 0 && rightDist > 0) {
            mFoundResult = true; return (leftDist + rightDist);
        }
        if (leftDist > 0) return 1 + leftDist;
        if (rightDist > 0) return 1 + rightDist;
        return 0;
    }
};

int main(){
    TreeNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7);
    node1.left = &node2; node1.right = &node3;
    node2.left = &node4; node2.right = &node6;
    node3.right = &node5; node6.left = &node7;

    Solution so;
    cout << "Dist between node1 and node6 is " << so.calculateDistance(&node1, &node1, &node6) << endl;
    cout << "Dist between node2 and node7 is " << so.calculateDistance(&node1, &node2, &node7) << endl;
    cout << "Dist between node4 and node7 is " << so.calculateDistance(&node1, &node4, &node7) << endl;
    cout << "Dist between node6 and node5 is " << so.calculateDistance(&node1, &node5, &node6) << endl;
    return 0;
}