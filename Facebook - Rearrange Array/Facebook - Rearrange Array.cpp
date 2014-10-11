//  WAP to modify the array such that arr[I] = arr[arr[I]].
//  Do this in place i.e.with out using additional memory.
//  
//  example : if a = { 2, 3, 1, 0 }
//  o / p = a = { 1, 0, 3, 2 }
//  
//  Note: The array contains 0 to n - 1 integers.

#include <iostream>
using namespace std;

void rearrangeArray(int * arr, int n){
    if (n < 2) return;
    int curCheckPos = 0, curPos = 0, orgVal = 0, targetPos = 0;
    while (curCheckPos < n){
        if (arr[curCheckPos] >= n) { ++curCheckPos; continue; }
        orgVal = arr[curCheckPos]; targetPos = orgVal; curPos = curCheckPos;
        while (targetPos != curCheckPos){
            arr[curPos] = arr[targetPos] + n;
            curPos = targetPos; targetPos = arr[curPos];
        }
        arr[curPos] = orgVal + n;
        ++curCheckPos;
    }

    for (int i = 0; i < n; ++i) arr[i] -= n;
}

void OutputArray(int * arr, int n)
{
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr1[] = { 2, 3, 1, 0 };
    int n = sizeof(arr1) / sizeof(int);

    cout << "Original Array is:" << endl;
    OutputArray(arr1, n);
    cout << "Rearranged Array is:" << endl;
    rearrangeArray(arr1, n);
    OutputArray(arr1, n);

    cout << endl;
    int arr2[] = { 1, 4, 2, 0, 3 };
    n = sizeof(arr2) / sizeof(int);
    cout << "Original Array is:" << endl;
    OutputArray(arr2, n);
    cout << "Rearranged Array is:" << endl;
    rearrangeArray(arr2, n);
    OutputArray(arr2, n);
    return 0;
}