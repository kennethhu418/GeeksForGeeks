// Given a number n(which is represented by digit array) and a number k, find the next larger number than n 
// by swapping adjacent digits of n k times at most.
// For example:
// n = 7935877331 and k = 5
// Then the next larger number of n by swapping adjacent digits at most 5 times is 7937358731
// step1 : 7935877331 -> 7935787331
// step2 : 7935787331 -> 7937587331
// step3 : 7937587331 -> 7937583731
// step4:  7937583731 -> 7937538731
// step5:  7937538731 -> 7937358731

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
    // a number represented by digit array, and swapping at most K times
    void getNextLargerNumber(vector<int> & digitArr, int K) {
        int n = digitArr.size();
        if (n < 2 || K == 0) return;

        //Search the first digit (T_D) which begins to decrease from the end of the array
        int curPos = n - 1;
        while (curPos > 0) {
            if (digitArr[curPos - 1] < digitArr[curPos]) break;
            --curPos;
        }
        if (curPos == 0) return;

        // Starting from the next digit of the above found decreasing digit T_D, find the first smallest digit which is larger 
        // than T_D and the distance between T_D and the first smallest digit is smaller than K
        int curStartPos = curPos - 1, targetPos = -1, k = K;
        for (int i = curPos; i < n && i - curStartPos <= k; ++i) {
            if (digitArr[i] <= digitArr[curStartPos]) break;
            if (targetPos < 0 || digitArr[i] < digitArr[targetPos]) targetPos = i;
        }

        // We move the target number found in the above procedure to the T_D position by swapping adjacent digits 
        int target = digitArr[targetPos];
        k -= (targetPos - curStartPos);
        memmove(&digitArr[curStartPos + 1], &digitArr[curStartPos], (targetPos - curStartPos) * sizeof(int));
        digitArr[curStartPos] = target;

        // ++curStartPos. Now starting from curStartPos , repeatedly find the smallest digit to replace the number at curStartPos
        ++curStartPos;
        while (curStartPos < n - 1 && k > 0) {
            targetPos = -1; curPos = curStartPos + 1;
            while (curPos < n && curPos - curStartPos <= k) {
                if (digitArr[curPos] < digitArr[curStartPos]) {
                    if (targetPos < 0 || digitArr[targetPos] > digitArr[curPos]) targetPos = curPos;
                }
                ++curPos;
            }

            if (targetPos >= 0) {
                target = digitArr[targetPos];
                k -= (targetPos - curStartPos);
                memmove(&digitArr[curStartPos + 1], &digitArr[curStartPos], (targetPos - curStartPos) * sizeof(int));
                digitArr[curStartPos] = target;
            }

            ++curStartPos;
        }

        return;
    }
};

/*****************Below codes are for tests**********************/
void printNumber(const vector<int> & arr) {
    for (vector<int>::const_iterator iter = arr.begin(); iter != arr.end(); ++iter)
        cout << *iter;
}

int main()
{
    Solution so;

    /**************** Unit Test 1********************/
    int arr1[] = { 7, 9, 3, 5, 8, 7, 7, 3, 3, 1 };
    vector<int> digitArr1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    int K1 = 5;    
    
    cout << "The next larger number of ";
    printNumber(digitArr1);
    cout << " is ";
    so.getNextLargerNumber(digitArr1, K1);
    printNumber(digitArr1);
    cout << endl;
    /********************************************/

    /**************** Unit Test 2********************/
    int arr2[] = { 4, 3, 5, 9, 2, 1, 6, 9 };
    vector<int> digitArr2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int K2 = 5;
 
    cout << "The next larger number of ";
    printNumber(digitArr2);
    cout << " is ";
    so.getNextLargerNumber(digitArr2, K2);
    printNumber(digitArr2);
    cout << endl;
    /********************************************/
	return 0;
}