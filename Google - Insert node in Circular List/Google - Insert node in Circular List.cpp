//  Add a key(integer type) into a circular single linked list so that the list
//  maintains a sorted order.The given head of the list may not be the
//  smallest number

#include <iostream>
#include <assert.h>
using namespace std;

typedef struct __ListNode {
    int                     val;
    __ListNode      *next;
    __ListNode(int val = 0) : val(val), next(NULL) {}
}ListNode;

ListNode* insertNode(ListNode* head, int target) {
    ListNode *targetNode = new ListNode(target);
    targetNode->next = targetNode;
    if (head == NULL)   return targetNode;
    if (head->next == head) {
        head->next = targetNode;
        targetNode->next = head;
        return head;
    }

    ListNode *curNode = head->next, *prevNode = head;
    while (true) {
        if ((prevNode->val <= target && target <= curNode->val)
            || (prevNode->val > curNode->val && (prevNode->val < target || target < curNode->val))
            || curNode == head) {
            prevNode->next = targetNode;
            targetNode->next = curNode;
            return head;
        }

        prevNode = curNode;
        curNode = curNode->next;
    }

    assert(0);
    return NULL;
}

bool validate(ListNode *head) {
    if (head == NULL || head->next == head)
        return true;

    ListNode *curNode = head->next, *prevNode = head;
    int crossCount = 0;
    while (curNode != head) {
        if (prevNode->val > curNode->val)
            ++crossCount;
        prevNode = curNode;
        curNode = curNode->next;
    }
    if (prevNode->val > curNode->val)
        ++crossCount;
    return crossCount <= 1;
}

void free(ListNode *head) {
    if (head == NULL) return;
    ListNode *curNode = head->next, *nextNode = NULL;
    head->next = NULL;
    while (curNode) {
        nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
}

int main() {
    ListNode       *head = NULL;
    const       int     MAX_TRY = 1000;
    const       int     MAX_TRY_EACH = 500;
    const       int     MAX_VAL = 2000;
    int             curTry = 0, curInnerTry = 0, curNum = 0;

    while (curTry++ < MAX_TRY) {
        cout << "Current outter try: " << curTry << endl << endl;
        if (curTry == 27)
            cout << endl;
        head = NULL;
        curInnerTry = 0;

        while (curInnerTry++ < MAX_TRY_EACH) {
            cout << "Current inner try: " << curInnerTry << endl << endl;
            if (curInnerTry == 3)
                cout << endl;
            curNum = 1 + rand() % MAX_VAL;
            head = insertNode(head, curNum);
            assert(validate(head));
        }

        free(head);
    }

    return 0;
}