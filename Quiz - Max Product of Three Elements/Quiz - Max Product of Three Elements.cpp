// Given an integer array, find and print three element in the array whose product is maximum.

#include <iostream>
#include <algorithm>
using namespace std;

int searchMaxProduct(int *arr, int n) {
    if (n < 3) return 0;
    if (n == 3) return arr[0] * arr[1] * arr[2];
    sort(arr, arr + n);

    bool hasZero = false;
    for (int i = 0; i < n; ++i){
        if (arr[i] == 0){
            hasZero = true; break;
        }
    }

    //max result can be product of three positive numbers
    int maxVal = arr[n - 1] * arr[n - 2] * arr[n - 3];
    //max result can also be product of one positive number and two negative numbers
    if (arr[0] * arr[1] * arr[n - 1] > maxVal) maxVal = arr[0] * arr[1] * arr[n - 1];
    //max result can also be product of three negative numbers
    if (arr[0] * arr[1] * arr[2] > maxVal) maxVal = arr[0] * arr[1] * arr[2];
    //if there is zero and no positive numbers, the max product should be zero
    if (hasZero && maxVal < 0) maxVal = 0;
    return maxVal;
}


int main()
{
    int arr1[] = {1, 9, 7, 8, 12, 0};
    int arr2[] = { 1, 9, -7, 8, -12, 0 };
    int arr3[] = { -1, -9, -7, 8, -12, 0, 7};
    int arr4[] = { -1, -9, -7, -10, -11};
    int arr5[] = { -1, -9, -7, 0, -10, -11 };

    cout << searchMaxProduct(arr1, sizeof(arr1) / sizeof(int)) << endl;
    cout << searchMaxProduct(arr2, sizeof(arr2) / sizeof(int)) << endl;
    cout << searchMaxProduct(arr3, sizeof(arr3) / sizeof(int)) << endl;
    cout << searchMaxProduct(arr4, sizeof(arr4) / sizeof(int)) << endl;
    cout << searchMaxProduct(arr5, sizeof(arr5) / sizeof(int)) << endl;

	return 0;
}

