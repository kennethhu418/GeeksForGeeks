//Given an array of 0s and 1s, find the position of 0 to be replaced with 1 to get 
//longest continuous sequence of 1s.
//
//Eg: Array - 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1
//    Output - 9. That is, by replacing the 0 at the 9th position of the array, 
//             we can get longest continouse sequence of 1s. And the length is 7.
#include <iostream>
using namespace std;

int SearchLongest1Sequence(int arr[], int n, int &pos) {
    pos = -1;
    if (n == 0) return 0;
    if (n == 1) {
        if (arr[0] == 0) pos = 0;
        return 1;
    }

    int prev0 = arr[n - 1] == 1 ? 1 : 0, cur0 = 0;
    int prev1 = 1, cur1 = 0;
    int prevPos = arr[n - 1] == 1 ? -1 : (n - 1), curPos = 0;
    int longestLen = 0;
    for (int i = n - 2; i >= 0; --i) {
        cur0 = arr[i] == 0 ? 0 : 1 + prev0;
        if (arr[i] == 0) {
            cur1 = 1 + prev0;
            curPos = i;
        }
        else {
            cur1 = 1 + prev1;
            curPos = prevPos;
        }

        if (cur1 > longestLen) {
            longestLen = cur1;
            pos = curPos;
        }

        prev0 = cur0; prev1 = cur1; prevPos = curPos;
    }

    return longestLen;
}

int main() {
    int arr1[] = { 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1 };
    int n = sizeof(arr1) / sizeof(int);
    int longestLen = 0, longestPos = 0;

    longestLen = SearchLongest1Sequence(arr1, n, longestPos);
    cout << "Longest length is " << longestLen << " by replacing 0 at " << longestPos << endl;
    return 0;
}