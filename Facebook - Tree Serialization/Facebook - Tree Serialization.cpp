#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define NULL_NODE '$'

typedef struct __TreeNode
{
    char        data;
    __TreeNode  *left;
    __TreeNode  *right;
    __TreeNode(char data) : data(data), left(NULL), right(NULL) {}
}TreeNode;

class Solution
{
public:
    string serializeTree(TreeNode* root){
        if (root == NULL) return "";
        string result;
        serializeTree(root, result);
        return result;
    }

    TreeNode* deserializeTree(const string &str) {
        if (str.empty()) return NULL;
        int pos = 0;
        return deserializeTree(str, pos);
    }

private:
    void serializeTree(TreeNode* root, string &result){
        if (root == NULL) {
            result += NULL_NODE; return;
        }

        result += root->data;
        serializeTree(root->left, result);
        serializeTree(root->right, result);
    }

    TreeNode* deserializeTree(const string &str, int &pos){
        if (pos >= str.size()) return NULL;
        if (str[pos] == NULL_NODE) {
            ++pos; return NULL;
        }

        TreeNode* root = new TreeNode(str[pos++]);
        root->left = deserializeTree(str, pos);
        root->right = deserializeTree(str, pos);
        return root;
    }
};

int main()
{
    TreeNode nodeA('A');
    TreeNode nodeB('B');
    TreeNode nodeD('D');
    TreeNode nodeE('E');
    TreeNode nodeC('C');
    TreeNode nodeF('F');
    TreeNode nodeG('G');

    nodeA.left = &nodeB; nodeA.right = &nodeC;
    nodeB.right = &nodeD; nodeD.left = &nodeE;
    nodeC.left = &nodeF; nodeC.right = &nodeG;

    Solution so;
    string serializedStr = so.serializeTree(&nodeA);
    cout << "Serialized Tree is " << serializedStr.c_str() << endl;

    TreeNode* root = so.deserializeTree(serializedStr);
    serializedStr = so.serializeTree(root);
    cout << "Serialized Tree again is " << serializedStr.c_str() << endl;
    return 0;
}