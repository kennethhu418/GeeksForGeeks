#include <iostream>
#include <assert.h>
using namespace std;

typedef struct __TreeNode
{
    int         val;
    __TreeNode  *left;
    __TreeNode  *right;
    __TreeNode(int val) : val(val), left(NULL), right(NULL) {}
}TreeNode;

class BinarySearchTree
{
private:
    TreeNode*   mRoot;

    bool add(TreeNode* root, int target) {
        if (root->val == target)
            return false;
        if (target > root->val) {
            if (root->right == NULL) {
                root->right = new TreeNode(target);
                return true;
            }
            return add(root->right, target);
        }
        if (root->left == NULL) {
            root->left = new TreeNode(target);
            return true;
        }
        return add(root->left, target);
    }

    bool find(TreeNode * root, int target) {
        if (root == NULL) return false;
        if (root->val == target) return true;
        if (root->val > target) return find(root->left, target);
        return find(root->right, target);
    }

    void remove(TreeNode * root, TreeNode * parent, int target) {
        if (root == NULL) return;
        if (target > root->val) {
            remove(root->right, root, target);
            return;
        }
        else if (target < root->val) {
            remove(root->left, root, target);
            return;
        }

        if (root->left == NULL && root->right == NULL) {
            if (parent == NULL)
                mRoot = NULL;
            else if (parent->left == root)
                parent->left = NULL;
            else
                parent->right = NULL;
            delete root;
            return;
        }

        TreeNode* curNode = NULL;
        if (root->left) {
            curNode = root->left; parent = root;
            while (curNode->right) {
                parent = curNode;
                curNode = parent->right;
            }
        }
        else {
            curNode = root->right; parent = root;
            while (curNode->left) {
                parent = curNode;
                curNode = parent->left;
            }
        }

        root->val = curNode->val;
        remove(curNode, parent, curNode->val);
    }

public:
    BinarySearchTree() {
        mRoot = NULL;
    }

    bool add(int target) {
        if (mRoot == NULL) {
            mRoot = new TreeNode(target);
            return true;
        }

        return add(mRoot, target);
    }

    bool find(int target) {
        return find(mRoot, target);
    }

    void remove(int target) {
        if (mRoot == NULL)
            return;
        remove(mRoot, NULL, target);
    }
};

int main()
{
    BinarySearchTree tree;
    bool found = tree.find(40);
    assert(found == false);

    assert(tree.add(40));
    assert(tree.add(30));
    assert(tree.add(20));
    assert(tree.add(28));
    assert(tree.add(59));
    assert(tree.add(54));
    assert(tree.add(57));
    assert(tree.add(80));
    assert(tree.add(20) == false);

    assert(tree.find(40));
    assert(tree.find(30));
    assert(tree.find(20));
    assert(tree.find(28));
    assert(tree.find(59));
    assert(tree.find(54));
    assert(tree.find(57));
    assert(tree.find(80));

    assert(tree.find(31) == false);

    tree.remove(30);
    tree.remove(40);
    tree.remove(57);

    assert(tree.find(40) == false);
    assert(tree.find(30) == false);
    assert(tree.find(20));
    assert(tree.find(28));
    assert(tree.find(59));
    assert(tree.find(54));
    assert(tree.find(57) == false);
    assert(tree.find(80));

    return 0;
}