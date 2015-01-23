// Program an iterator for a List which may include nodes or List  i.e.  *
// {0, { 1, 2 }, 3, { 4, { 5, 6 } }} Iterator returns 0 - 1 - 2 - 3 - 4 - 5 - 6

#include <iostream>
#include <stack>
using namespace std;

typedef struct __NestedList {
    int						val;	// only meaningful when nestedList is NULL
    __NestedList	*next;
    __NestedList	*nestedList;
    __NestedList(int val) : val(val), next(NULL), nestedList(NULL) {}
}NestedList;

class Iterator {
private:
    stack<NestedList*>	mStack;

public:
    Iterator(NestedList *head) {
        if (head == NULL)	return;
        mStack.push(head);
        while (head->nestedList) {
            mStack.push(head->nestedList);
            head = head->nestedList;
        }
    }

    bool hasNext() {
        return !mStack.empty();
    }

    int		next() {
        if (mStack.empty()) return -1;
        int target = mStack.top()->val;

        while (!mStack.empty() && !mStack.top()->next)
            mStack.pop();

        if (!mStack.empty()) {
            mStack.top() = mStack.top()->next;
            while (mStack.top()->nestedList)
                mStack.push(mStack.top()->nestedList);
        }
        return target;
    }
};

int main() {
    // {0, {1,2}, 3 ,{4,{5, 6}}}
    NestedList	list0(0), list1(1), list2(2), list3(3), list4(4), list5(5), list6(6);
    list1.next = &list2;
    list5.next = &list6;
    NestedList  list12(0);
    list12.nestedList = &list1;
    NestedList  list56(0);
    list56.nestedList = &list5;
    NestedList  list456(0);
    list456.nestedList = &list4;
    list4.next = &list56;
    list0.next = &list12;
    list12.next = &list3;
    list3.next = &list456;

    Iterator iter(&list0);
    while (iter.hasNext())
        cout << iter.next() << "  ";
    cout << endl;
    return 0;
}