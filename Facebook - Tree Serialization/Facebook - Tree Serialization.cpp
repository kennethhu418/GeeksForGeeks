#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define END_FLAG '\"'

class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};


class Solution {
public:
    /**
    * This method will be invoked first, you should design your own algorithm
    * to serialize a binary tree which denote by a root node to a string which
    * can be easily deserialized by your own "deserialize" method later.
    */
    string serialize(TreeNode *root) {
        string serialStr;
        if (root)  serialize(root, serialStr);
        return serialStr;
    }

    /**
    * This method will be invoked second, the argument data is what exactly
    * you serialized at method "serialize", that means the data is not given by
    * system, it's given by your own serialize method. So the format of data is
    * designed by yourself, and deserialize it here as you serialize it in
    * "serialize" method.
    */
    TreeNode *deserialize(const string &data) {
        if (data.empty()) return NULL;
        int pos = 0;
        return deserialize(data, pos);
    }

private:
    string itoa(int n) {
        if (n == 0) return "0";
        string result;
        if (n < 0) result = "-";
        n = abs(n);
        while (n) {
            result += '0' + n % 10;
            n /= 10;
        }
        int s = 0, e = result.size() - 1;
        if (result[0] == '-') ++s;
        while (s < e)
            swap(result[s++], result[e--]);
        return result;
    }

    void removeLeadingSpaces(const string &str, int &pos) {
        while (pos < str.size() && str[pos] == ' ')
            ++pos;
    }

    int atoi(const string &str, int &pos) {
        bool negative = false;
        if (str[pos] == '-') {
            negative = true; ++pos;
        }

        unsigned int num = 0;
        while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9')
            num = 10 * num + str[pos++] - '0';

        return negative ? -(int)num : num;
    }

    void serialize(TreeNode *root, string &serialStr) {
        if (root == NULL)
            serialStr += END_FLAG;
        else {
            serialStr += itoa(root->val);
            serialStr += ' ';
            serialize(root->left, serialStr);
            serialStr += ' ';
            serialize(root->right, serialStr);
            serialStr += ' ';
        }
    }

    TreeNode* deserialize(const string &serialStr, int &pos) {
        removeLeadingSpaces(serialStr, pos);
        if (pos == serialStr.size()) return NULL;

        if (serialStr[pos] == END_FLAG) {
            ++pos;
            return NULL;
        }

        TreeNode *root = new TreeNode(atoi(serialStr, pos));
        root->left = deserialize(serialStr, pos);
        root->right = deserialize(serialStr, pos);
        return root;
    }
};

int main()
{
    TreeNode nodeA(11);
    TreeNode nodeB(222);
    TreeNode nodeD(33);
    TreeNode nodeE(4444);
    TreeNode nodeC(55555);
    TreeNode nodeF(666666);
    TreeNode nodeG(777);

    nodeA.left = &nodeB; nodeA.right = &nodeC;
    nodeB.right = &nodeD; nodeD.left = &nodeE;
    nodeC.left = &nodeF; nodeC.right = &nodeG;

    Solution so;
    string serializedStr = so.serialize(&nodeA);
    cout << "Serialized Tree is " << serializedStr.c_str() << endl;

    TreeNode* root = so.deserialize(serializedStr);
    serializedStr = so.serialize(root);
    cout << "Serialized Tree again is " << serializedStr.c_str() << endl;
    return 0;
}