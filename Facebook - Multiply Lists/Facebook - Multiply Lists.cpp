//Given two extremely large numbers - each number is stored in a Singly Linked list, with the MSB at the head.
//You are not allowed to reverse the Linked lists.Write a program to multiply them in optimum space and time.

#include <iostream>
#include <cstring>
using namespace std;

typedef struct __ListNode
{
    int			val;
    __ListNode  *next;
    __ListNode(int val) : val(val), next(NULL) {}
}ListNode;

class Solution
{
public:
    ListNode* MultiplyLists(ListNode *list1, ListNode* list2, ListNode* &freedNodes){
        int n1 = getLength(list1), n2 = getLength(list2);
        if (n1 == 1 && list1->val == 0) { freedNodes = list2; return list1; }
        if (n2 == 1 && list2->val == 0) { freedNodes = list1; return list2; }
        if (n1 == 1 && list1->val == 1) { freedNodes = list1; return list2; }
        if (n2 == 1 && list2->val == 1) { freedNodes = list2; return list1; }
        ListNode* resultHead = NULL, *freedTail = NULL, *curNode1 = NULL, *curNode2 = NULL;

        int *buffer = new int[n1 + n2], i = 0, j = 0;
        memset(buffer, 0, sizeof(int)*(n1 + n2));
        for (i = n1 - 1, curNode1 = list1; i >= 0; --i, curNode1 = curNode1->next){
            for (j = n2 - 1, curNode2 = list2; j >= 0; --j, curNode2 = curNode2->next)
                buffer[i + j] += curNode1->val * curNode2->val;
        }

        int curResult = 0, carry_on = 0, curPos = 0;
        curNode1 = list1; curNode2 = NULL;
        while (curPos < n1 + n2){
            curResult = buffer[curPos++] + carry_on;
            carry_on = curResult / 10;
            curResult -= 10 * carry_on;
            if (curNode1 == NULL) curNode1 = list2;
            curNode2 = curNode1->next;
            curNode1->val = curResult;
            curNode1->next = resultHead;
            resultHead = curNode1;
            curNode1 = curNode2;
        }

        freedNodes = NULL;
        while (resultHead->val == 0){
            curNode2 = resultHead->next;
            addNode(freedNodes, freedTail, resultHead);
            resultHead = curNode2;
        }

        delete[] buffer;
        return resultHead;
    }

private:
    void addNode(ListNode *&head, ListNode *&tail, ListNode *node){
        node->next = NULL;
        if (head == NULL) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }

    int getLength(ListNode *list){
        int cnt = 0;
        while (list) { ++cnt; list = list->next; }
        return cnt;
    }
};

int main()
{
    ListNode node7(7);
    ListNode node8(8);
    ListNode node9(9);
    ListNode node1(1);
    ListNode node2(2);

    node7.next = &node8;
    node8.next = &node9;
    node1.next = &node2;

    Solution so;
    ListNode* result = NULL, *freedNodes = NULL;
    result = so.MultiplyLists(&node7, &node1, freedNodes);

    cout << "Result is ";
    while (result){
        cout << result->val;
        result = result->next;
    }

    cout << endl << "freed count is : ";
    int cnt = 0;
    while (freedNodes){
        ++cnt; freedNodes = freedNodes->next;
    }
    cout << cnt << endl;
    return 0;
}