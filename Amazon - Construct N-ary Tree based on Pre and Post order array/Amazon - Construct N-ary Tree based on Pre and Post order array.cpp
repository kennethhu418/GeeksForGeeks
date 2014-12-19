//  Given a pre order traversal array and a post order traversal array of a n-ary tree,
//  construct the tree based on them
//  The tree node structure is
//  struct TreeNode {
//      int data;
//      struct TreeNode *children[MAX];
//      int child_num;
//  }

#include <iostream>
#include <assert.h>
using namespace std;

#define MAX_CHILDREN_COUNT 5

typedef struct __TreeNode{
    int         data;
    __TreeNode  *children[MAX_CHILDREN_COUNT];
    unsigned int child_num;
    __TreeNode(int data) : data(data), child_num(0) {}
}TreeNode;

int search(int *arr, int start, int end, int target) {
    while (start <= end) {
        if (arr[start] == target) break;
        ++start;
    }
    return start;
}

TreeNode* constructTree(int *preArr, int *postArr, int n) {
    if (n <= 0) return NULL;
    TreeNode *root = new TreeNode(preArr[0]);
    if (n == 1) return root;

    int curChildRangeStartPre = 1, curChildRangeStartPost = 0, curChildRangeSize = 0;
    while (curChildRangeStartPre < n) {
        curChildRangeSize = search(postArr, curChildRangeStartPost, n - 1, preArr[curChildRangeStartPre]) - curChildRangeStartPost + 1;
        root->children[root->child_num++] = constructTree(preArr + curChildRangeStartPre, postArr + curChildRangeStartPost, curChildRangeSize);
        curChildRangeStartPre += curChildRangeSize;
        curChildRangeStartPost += curChildRangeSize;
    }
    return root;
}


/*****************  TEST CODES BELOW  ***********************/

void preOrderTraversal(TreeNode* root, int * arr, int &curPos) {
    if (root == NULL) return;
    arr[curPos++] = root->data;
    for (int i = 0; i < root->child_num; ++i)
        preOrderTraversal(root->children[i], arr, curPos);
}

void postOrderTraversal(TreeNode* root, int * arr, int &curPos) {
    if (root == NULL) return;
    for (int i = 0; i < root->child_num; ++i)
        postOrderTraversal(root->children[i], arr, curPos);
    arr[curPos++] = root->data;
}

bool isSameTree(TreeNode* root1, TreeNode* root2){
    if (root1 == NULL && root2 == NULL) return true;
    if (root1 == NULL || root2 == NULL) return false;
    if (root1->child_num != root2->child_num) return false;
    if (root1->data != root2->data) return false;

    for (int i = 0; i < root1->child_num; ++i) {
        if (!isSameTree(root1->children[i], root2->children[i])) return false;
    }
    return true;
}

void DestroyTree(TreeNode *root) {
    if (root == NULL) return;
    for (int i = 0; i < root->child_num; ++i)
        DestroyTree(root->children[i]);
    delete root;
}

int main()
{
    TreeNode node0(0);
    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);
    TreeNode node6(6);
    TreeNode node7(7);
    TreeNode node8(8);
    TreeNode node9(9);
    TreeNode node10(10);
    TreeNode node11(11);
    TreeNode node12(12);
    TreeNode node13(13);
    TreeNode node14(14);

    node0.child_num = 3;
    node0.children[0] = &node1;
    node0.children[1] = &node2;
    node0.children[2] = &node3;

    node1.child_num = 1;
    node1.children[0] = &node4;

    node2.child_num = 3;
    node2.children[0] = &node5;
    node2.children[1] = &node6;
    node2.children[2] = &node7;

    node3.child_num = 2;
    node3.children[0] = &node8;
    node3.children[1] = &node9;

    node5.child_num = 3;
    node5.children[0] = &node12;
    node5.children[1] = &node13;
    node5.children[2] = &node14;

    node9.child_num = 2;
    node9.children[0] = &node10;
    node9.children[1] = &node11;

    int preOrderTArr[15] = { 0 };
    int postOrderTArr[15] = { 0 };
    int preSize = 0, postSize = 0;
    preOrderTraversal(&node0, preOrderTArr, preSize);
    postOrderTraversal(&node0, postOrderTArr, postSize);
    assert(preSize == postSize);
    
    TreeNode* root = constructTree(preOrderTArr, postOrderTArr, preSize);
    assert(isSameTree(root, &node0));

    DestroyTree(root);
    return 0;
}