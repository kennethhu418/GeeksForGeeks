//Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence
//1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, бн
//shows the first 11 ugly numbers.By convention, 1 is included.
//
//Write a funtion to return the nth ugly number.
#include <queue>
#include <iostream>
#include <assert.h>
using namespace std;

int popMin(deque<int> &q1, deque<int> &q2, deque<int> &q3, int &srcQ) {
    int num1 = q1.front(), num2 = q2.front(), num3 = q3.front();
    if (num1 < num2 && num1 < num3) {
        srcQ = 0; q1.pop_front(); return num1;
    }

    if (num2 < num1 && num2 < num3) {
        srcQ = 1; q2.pop_front(); return num2;
    }

    srcQ = 2; q3.pop_front();
    return num3;
}

int getUglyNumber(int n) {
    if (n < 7) return n;
    --n; //assume 2 is the first ugly number, rather than 1.

    deque<int> q2, q3, q5;
    q2.push_back(2);
    q3.push_back(3);
    q5.push_back(5);
    int curVisitedCnt = 3, curNum = 0, srcQ = 0;
    while (true) {
        curNum = popMin(q2, q3, q5, srcQ);
        curVisitedCnt++;
        if (curVisitedCnt == n)
            return curNum;

        switch (srcQ)
        {
        case 0:
            q2.push_back(2 * curNum);
        case 1:
            q3.push_back(3 * curNum);
        case 2:
            q5.push_back(5 * curNum);
            break;
        default:
            assert(0);
        }    
    }

    return -1;
}

int main()
{
    for (int i = 1; i <= 100; ++i) {
        cout << "The " << i << "th ugly number is " << getUglyNumber(i) << endl;
    }
    return 0;
}