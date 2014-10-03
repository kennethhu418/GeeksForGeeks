/*******************************************************************************************************
 * Given a dictionary of words and a regular expression target word (where '.' represents any single character), find
 * whether there is matched word in the dictionary
 *******************************************************************************************************/

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
using namespace std;

class TreeNode
{
private:
    char	data;
    bool    isEnd;
    unordered_map<char, TreeNode*> children;

public:
    TreeNode(char data = '\0', bool isEnd = false) : data(data), isEnd(isEnd) {}

    ~TreeNode(){
        for (unordered_map<char, TreeNode*>::iterator iter = children.begin();
            iter != children.end(); ++iter){
            delete iter->second;
        }
    }

    bool searchWord(const string &str, int curPos = -1){
        if (curPos == str.size() - 1) return isEnd;

        if (str[curPos + 1] == '.'){
            for (unordered_map<char, TreeNode*>::iterator iter = children.begin();
                iter != children.end(); ++iter){
                if (iter->second->searchWord(str, curPos + 1)) return true;
            }
            return false;
        }

        if (children.find(str[curPos + 1]) == children.end())
            return false;
        return children[str[curPos + 1]]->searchWord(str, curPos + 1);
    }

    void addWord(const string &str, int curPos = -1)
    {
        if (curPos == str.size() - 1){
            isEnd = true;
            return;
        }

        TreeNode* child = NULL;
        if (children.find(str[curPos + 1]) == children.end()){
            child = new TreeNode(str[curPos + 1]);
            children[str[curPos + 1]] = child;
        }
        else
            child = children[str[curPos + 1]];

        child->addWord(str, curPos + 1);
    }
};

class Trie
{
private:
    TreeNode *root;

public:
    Trie(){
        root = new TreeNode;
    }

    ~Trie(){
        delete root;
    }

    void addWord(const string &str){
        root->addWord(str);
    }

    bool searchWord(const string &str){
        return root->searchWord(str);
    }
};

int main() {
    Trie trie;
    const string dictionary[] = { "Microsoft", "Visual", "Studio", "Project", "Facebook", "Success", "Kenneth" };
    const int n = sizeof(dictionary) / sizeof(string);

    for (int i = 0; i < n; ++i)
        trie.addWord(dictionary[i]);

    char temp[50];
    string searchTarget;
    cout << "------------------------------------------------------" << endl;
    while (cin >> temp){
        cout << trie.searchWord(temp) << endl;
        cout << "------------------------------------------------------" << endl;
    }

    return 0;
}