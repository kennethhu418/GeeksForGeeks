//Given two sorted linked lists, construct a linked list that contains maximum sum path 
//from start to end.The result list may contain nodes from both input lists.
//When constructing the result list, we may switch to the other input list only at the 
//point of intersection(which mean the two node with the same value in the lists).
//You should construct the list in place.
//
//Input:
//List1 = -1->3->3->3->30->90->120->180
//List2 = -4-> - 3->3->12->32->90->100->120->130
//
//Output : Following is maximum sum linked list out of two input lists
//         list = -1->3->12->32->90->100->120->180
//         we switch at 3 and 240 to get above maximum sum linked list
//         After constructing the result list, the original two lists become
//         List1 = 3->3->30->90->120
//         List2 = -4->-3->3->130

#include <iostream>
using namespace std;

typedef struct __ListNode
{
    int         val;
    __ListNode  *next;
    __ListNode(int val) : val(val), next(NULL) {}
}ListNode;

class Solution
{
private:
    void addLists(ListNode *&head, ListNode *&tail, ListNode *targetHead, ListNode *targetTail) {
        if (head == NULL) {
            head = targetHead; tail = targetTail;
            return;
        }
        tail->next = targetHead;
        tail = targetTail;
    }

public:
    ListNode* constructMaxSumListInPlace(ListNode *&head1, ListNode *&head2){
        if (head1 == NULL) return head2;
        if (head2 == NULL) return head1;

        int curSum1 = 0, curSum2 = 0;
        ListNode *resultHead = NULL, *resultTail = NULL, \
            *curList1Head = NULL, *curList1Tail = NULL, \
            *curList2Head = NULL, *curList2Tail = NULL, \
            *newList1Head = NULL, *newList1Tail = NULL, \
            *newList2Head = NULL, *newList2Tail = NULL, \
            *nextNode = NULL, *curNode1 = head1, *curNode2 = head2;

        while (curNode1 && curNode2) {
            if (curNode1->val == curNode2->val) {
                while (curNode1 && curNode2 && curNode1->val == curNode2->val) {
                    nextNode = curNode1->next; curSum1 += curNode1->val;
                    addNode(curList1Head, curList1Tail, curNode1); curNode1 = nextNode;
                    nextNode = curNode2->next; curSum2 += curNode2->val;
                    addNode(curList2Head, curList2Tail, curNode2); curNode2 = nextNode;
                }
                //Compare prev sum and merge to result lists
                if (curSum1 >= curSum2) {
                    addLists(resultHead, resultTail, curList1Head, curList1Tail);
                    addLists(newList2Head, newList2Tail, curList2Head, curList2Tail);
                }
                else {
                    addLists(resultHead, resultTail, curList2Head, curList2Tail);
                    addLists(newList1Head, newList1Tail, curList1Head, curList1Tail);
                }

                curSum1 = curSum2 = 0;
                curList1Head = curList1Tail = curList2Head = curList2Tail = NULL;
                continue;
            }

            if (curNode1->val < curNode2->val) {
                nextNode = curNode1->next; curSum1 += curNode1->val;
                addNode(curList1Head, curList1Tail, curNode1); curNode1 = nextNode;
            }
            else {
                nextNode = curNode2->next; curSum2 += curNode2->val;
                addNode(curList2Head, curList2Tail, curNode2); curNode2 = nextNode;
            }
        }

        while (curNode1) {
            nextNode = curNode1->next; curSum1 += curNode1->val;
            addNode(curList1Head, curList1Tail, curNode1); curNode1 = nextNode;
        }
        while (curNode2) {
            nextNode = curNode2->next; curSum2 += curNode2->val;
            addNode(curList2Head, curList2Tail, curNode2); curNode2 = nextNode;
        }

        if (curSum1 >= curSum2) {
            addLists(resultHead, resultTail, curList1Head, curList1Tail);
            addLists(newList2Head, newList2Tail, curList2Head, curList2Tail);
        }
        else {
            addLists(resultHead, resultTail, curList2Head, curList2Tail);
            addLists(newList1Head, newList1Tail, curList1Head, curList1Tail);
        }

        head1 = newList1Head; head2 = newList2Head;
        return resultHead;
    }

    void addNode(ListNode* &head, ListNode* &tail, ListNode *node) {
        node->next = NULL;
        if (head == NULL)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
};

void OutputList(ListNode *head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
}

int main() {
    //Linked List 1 : -1->3->3->3->30->90->120->180->NULL
    //Linked List 2 : -4->-3->3->12->32->90->100->120->130->NULL
    Solution so;

    ListNode node1_1(-1), node1_2(3), node1_2_2(3), node1_3(3), node1_4(30), node1_5(90),
        node1_6(120), node1_7(180);
    ListNode *head1 = NULL, *tail1 = NULL;
    so.addNode(head1, tail1, &node1_1);
    so.addNode(head1, tail1, &node1_2);
    so.addNode(head1, tail1, &node1_2_2);
    so.addNode(head1, tail1, &node1_3);
    so.addNode(head1, tail1, &node1_4);
    so.addNode(head1, tail1, &node1_5);
    so.addNode(head1, tail1, &node1_6);
    so.addNode(head1, tail1, &node1_7);

    ListNode node2_1(-4), node2_2(-3), node2_3(3), node2_4(12), node2_5(32),
        node2_6(90), node2_7(100), node2_8(120), node2_9(130);
    ListNode *head2 = NULL, *tail2 = NULL;
    so.addNode(head2, tail2, &node2_1);
    so.addNode(head2, tail2, &node2_2);
    so.addNode(head2, tail2, &node2_3);
    so.addNode(head2, tail2, &node2_4);
    so.addNode(head2, tail2, &node2_5);
    so.addNode(head2, tail2, &node2_6);
    so.addNode(head2, tail2, &node2_7);
    so.addNode(head2, tail2, &node2_8);
    so.addNode(head2, tail2, &node2_9);

    ListNode* result = so.constructMaxSumListInPlace(head1, head2);

    cout << "Result List: ";
    OutputList(result);
    cout << endl;
    cout << "List1: ";
    OutputList(head1);
    cout << endl;
    cout << "List2: ";
    OutputList(head2);
    cout << endl;
    return 0;
}
