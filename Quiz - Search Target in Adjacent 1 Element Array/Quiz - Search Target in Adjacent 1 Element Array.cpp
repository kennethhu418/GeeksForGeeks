// Search a target in an array, where the difference of adjacent elements is 1 at most.
// For example, the array would be {8, 8, 9, 10, 9, 8, 7, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 1}
#include <iostream>
#include <cmath>
using namespace std;

int searchTarget(int * arr, int n, int target) {
    if (n == 0) return -1;
    if (n == 1) return arr[0] == target ? 0 : -1;

    int curPos = 0;
    while (curPos < n) {
        if (arr[curPos] == target) return curPos;
        curPos += abs(target - arr[curPos]);
    }
    return -1;
}
int main()
{
    int arr[] = {124, 124, 124, 125, 124, 123, 123, 124, 123, 121, 121, 120, 120, 120, 119, 118, 117, 117, 116, 117, 118, 119, 120};
    
    int target = 0, index = 0;

    while (cin >> target) {
        index = searchTarget(arr, sizeof(arr) / sizeof(int), target);
        if (index >= 0)
            cout << "Target is found: " << arr[index] << endl;
        else
            cout << "Target not found." << endl;
        cout << "====================================================" << endl;
    }
	return 0;
}

