//Implement a flatten iterator for NestedList
//eg : {{ 1, 2 }, 3, { 4, { 5, 6 } }}
//不断调用iterator的next()返回的序列是 1 2 3 4 5 6

//  Solution :
//  The recursive traverse of the nested linked list code is
//      void traverseNestedList(ListNode * head) {
//          if (head == NULL) return;
//          visit(head);
//          traverseNestedList(head->verticalNext);
//          traverseNestedList(head->horizonalNext);
//      }
//  We can see it is exactly the same with the preorder traversal of a binary tree
//  The difference here is that we need to implement an iterator rather than
//   just traverse the tree

#include <stack>
#include <iostream>
using namespace std;

typedef struct __ListNode
{
    int                         val;
    __ListNode         *verticalNext;
    __ListNode         *horizonalNext;
    __ListNode(int val = 0) : val(val), verticalNext(NULL), horizonalNext(NULL) {}
}ListNode;

class ListNodeIterator
{
private:
    stack<ListNode*>     mStack;
    ListNode    *mHead;

public:
    ListNodeIterator(ListNode *head = NULL) {
        reInitialize(head);
    }

    void reInitialize(ListNode *head) {
        while (!mStack.empty())
            mStack.pop();
        mHead = head;    
    }

    ListNode* next() {
        if (mStack.empty() && mHead == NULL)
            return NULL;

        // We have not visited any node, so visit the root first
        if (mStack.empty()) {
            mStack.push(mHead);
            mHead = NULL;
            return mStack.top();
        }

        //The top of the stack is the node which is just visited, based on the recursive
        //traversal code (see the "Solution" comments at the beginning of this cpp),
        //we should visit the verticalNext child of it.
        ListNode* nextNode = mStack.top()->verticalNext;
        if (nextNode) {
            mStack.push(nextNode);
            return nextNode;
        }


        //The verticalNext child of the latest visited node is NULL, based on the 
        //recursive traversal code, we should visit the horizonalNext child of it
        //now. 
        //If the horizonalNext child is not NULL, return the horizonalNext
        //child as the next visited node and push it to the stack.
        //If the horizonalNext child is NULL, we should return to the parent
        //node and check the parent's horizonalNext child (the parent has 
        //already visited its verticalNext child and has not visited the horizonalNext
        //child, that is why it is still in the stack).

        while (!mStack.empty()) {
            nextNode = mStack.top()->horizonalNext;
            mStack.pop();
            if (nextNode) {
                mStack.push(nextNode);
                return nextNode;
            }        
        }
        return NULL;    
    }
};

int main()
{
    //     1    -    7  -    8
    //     |                    |
    //     2 - 3 - 6        9 - 10
    //          |
    //          4 - 5
    ListNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9), node10(10);
    node1.horizonalNext = &node7; node1.verticalNext = &node2;
    node2.horizonalNext = &node3; node3.horizonalNext = &node6; node3.verticalNext = &node4;
    node4.horizonalNext = &node5; node7.horizonalNext = &node8; node8.verticalNext = &node9;
    node9.horizonalNext = &node10;

    ListNodeIterator iter(&node1);
    ListNode* curNode = iter.next();
    while (curNode) {
        cout << curNode->val << "  ";
        curNode = iter.next();    
    }
    return 0;
}