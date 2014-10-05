//Create an iterator to traverse a binary tree. When the next function is called on the 
//binary tree return the value at the next node as if you are doing an inorder traversal
//of the tree.Restrictions: Nodes do not have pointers to their parent node and you 
//can't use recursion. 

#include <iostream>
#include <stack>
using namespace std;

class TreeNode
{
public:
    int 		val;
    TreeNode	*left;
    TreeNode	*right;
    TreeNode(int val) : val(val), left(NULL), right(NULL) {}
};

class TreeIterator
{
private:
    stack<TreeNode*> stackA;

public:
    TreeIterator(TreeNode *root = NULL){
        while (root){
            stackA.push(root);
            root = root->left;
        }
    }

    TreeNode* getNext(){
        if (stackA.empty()) return NULL;

        TreeNode *target = stackA.top(); stackA.pop();
        TreeNode *node = target->right;
        while (node){
            stackA.push(node);
            node = node->left;
        }
        return target;
    }
};


int main() {
    TreeNode node10(10);
    TreeNode node7(7);
    TreeNode node12(12);
    TreeNode node3(3);
    TreeNode node8(8);
    TreeNode node11(11);
    TreeNode node18(18);
    TreeNode node15(15);

    node10.left = &node7;
    node10.right = &node12;
    node7.left = &node3;
    node7.right = &node8;
    node12.left = &node11;
    node12.right = &node18;
    node18.left = &node15;

    TreeIterator iter(&node10);
    TreeNode *node = iter.getNext();
    while (node){
        cout << node->val << " ";
        node = iter.getNext();
    }
    cout << endl;
    return 0;
}