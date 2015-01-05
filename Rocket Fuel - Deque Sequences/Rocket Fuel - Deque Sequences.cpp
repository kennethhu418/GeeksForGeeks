// There is one deque, which only supports three operations:
// 1) pushBack()
// 2) pushFront()
// 3) popBack()
// Notice there is NO popFront() operation.
// Given a sequence[1, 2, 3, 4, ..... N], you will push the element in the sequence in increasing order. That is, you will push 1 first, 
// then push 2, then push 3. The push can be either pushFront() or pushBack().And you can do the popBack() operation at any
// time.
// Given another sequence where the element are 1 ... N, determine whether it is a valid sequence by doing the operations
// denoted above.
// For example, sequence[2 3 1 4 5] is a valid sequence because we can do the following operations to get this result sequence:
// pushBack£¬pushBack£¬popBack£¬pushBack£¬popBack£¬popBack£¬pushBack£¬popBack£¬pushBack£¬popBack
// However, sequence [3 2 4 5 1] is not a valid sequence.

// Solution:
// Just simulate the push and pop sequence according to the final result sequence' order

#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;

typedef enum __OPT{
    INVALID_OPT = 0,
    PUSH_FRONT = 1,
    PUSH_BACK = 2,
    POP_BACK = 3
}OPT;

typedef struct __TraceRecord {
    OPT opt;
    int value;
    __TraceRecord(int value = 0, OPT opt = INVALID_OPT) : opt(opt), value(value) {}
}TraceRecord;

// Input Elements are from 1 to n
// traceArr is used to record the operation sequence to generate the resultSequence
// traceArr is only valid when the return value is true
bool validDequeOrder(int *resultSequence, int n, TraceRecord *traceArr) {
    if (n < 3) return true;

    //orderArr[i] records the index of i in the resultSequence
    int *orderArr = new int[n + 1];
    for (int i = 0; i < n; ++i)
        orderArr[resultSequence[i]] = i;

    // Use a list to simulate the deque
    list<int> dequeSim;
    // Indicate the next popped number's index in resultSequence
    int nextPoppedNumIndex = 0;
    
    int nextTraceIndex = 0;

    // Enque each number from 1 to n
    for (int curEnqueNum = 1; curEnqueNum <= n; ++curEnqueNum) {
        if (dequeSim.empty()) {
            dequeSim.push_back(curEnqueNum);
            traceArr[nextTraceIndex++] = TraceRecord(curEnqueNum, PUSH_BACK);
        }
        else {
            // The current num can only be pushed to the front or end of the deque,
            // so in the resultSequence, current num should be at the left or right of all the current deque elements
            bool targetRelativePositionLeft = true;
            if (orderArr[dequeSim.front()] < orderArr[curEnqueNum])
                targetRelativePositionLeft = false;
            for (list<int>::const_iterator iter = dequeSim.begin(); iter != dequeSim.end(); ++iter) {
                if ((orderArr[*iter] > orderArr[curEnqueNum]) != targetRelativePositionLeft) {
                    delete[] orderArr;
                    return false;
                }
            }

            // check passed, so push the current num into the deque
            if (targetRelativePositionLeft) {
                dequeSim.push_back(curEnqueNum);
                traceArr[nextTraceIndex++] = TraceRecord(curEnqueNum, PUSH_BACK);
            }
            else {
                dequeSim.push_front(curEnqueNum);
                traceArr[nextTraceIndex++] = TraceRecord(curEnqueNum, PUSH_FRONT);
            }
        }

        // After pushing the current number into the deque, check whether the back
        // of the deque is the next popped number. If it is, pop it out from the deque
        if (dequeSim.back() == resultSequence[nextPoppedNumIndex]) {
            dequeSim.pop_back();            
            traceArr[nextTraceIndex++] = TraceRecord(resultSequence[nextPoppedNumIndex], POP_BACK);
            ++nextPoppedNumIndex;
        }
    }

    delete[] orderArr;

    // Let's see whether the remaining elements in the deque satisefies the remaining result sequence
    while (!dequeSim.empty()) {
        if (dequeSim.back() != resultSequence[nextPoppedNumIndex])
            return false;
        dequeSim.pop_back();
        ++nextPoppedNumIndex;
    }
    return true;
}


/******************* TEST CODES BELOW *******************************/

void shuffleArray(int *arr, int n) {
    if (n < 2) return;
    int selIndex = 0;
    while (n > 1) {
        selIndex = rand() % n;
        swap(arr[selIndex], arr[n - 1]);
        --n;
    }
}

int main() {
    const int MAX_NUM = 10;
    TraceRecord traceArr[MAX_NUM << 1];
    int     resultSequence[MAX_NUM];
    bool  succeed = false;
    int     tryCount = 5;

    srand(time(NULL));

    for (int i = 4; i < MAX_NUM; ++i) {
        cout << "****************************************" << endl;
        cout << "Now test number = " << i << endl << endl;

        //Initialize result sequence
        for (int j = 0; j < i; ++j)
            resultSequence[j] = j + 1;

        for (int j = 0; j < tryCount; ++j) {
            shuffleArray(resultSequence, i);
            succeed = validDequeOrder(resultSequence, i, traceArr);
            cout << "The result sequence is: " << endl;
            for (int k = 0; k < i; ++k)
                cout << resultSequence[k] << " ";
            cout << endl;
            if (succeed) {
                cout << "Valid sequence and the sequence is :" << endl;
                for (int k = 0; k < 2 * i; ++k) {
                    if (traceArr[k].opt == PUSH_FRONT)
                        cout << "PUSH_FRONT  ";
                    else if (traceArr[k].opt == PUSH_BACK)
                        cout << "PUSH_BACK  ";
                    else
                        cout << "POP  ";
                }
                cout << endl << endl;
            }
            else
                cout << "Invalid Sequence!" << endl << endl;
        }    
    }

    return 0;
}