//Given an array of integers.We have to find the max element of the array, which is at multiple places in the 
//array and return any one of the indices randomly.

#include <cstdlib>
#include <iostream>
#include <unordered_map>
using namespace std;

int getMaximumElementIndex(int arr[], int n)
{
    if (n < 2) return n - 1;

    int curMaxIndex = 0, curMaxVal = arr[0], curMaxCount = 1;
    for (int i = 1; i < n; ++i){
        if (arr[i] == curMaxVal){
            ++curMaxCount;
            if (rand() % curMaxCount == 0) curMaxIndex = i;
        }
        else if (arr[i] > curMaxVal){
            curMaxIndex = i; curMaxVal = arr[i]; curMaxCount = 1;
        }
    }

    return curMaxIndex;
}


int main()
{
    unsigned long long TRY_COUNT = 120000000;
    int arr[] = {5, 4, 5, 6, 5, 3, 3, 7, 7, 1, 1, 7, 7, 7, 7, 8, 7, 8, 8, 1, 2};
    int n = sizeof(arr) / sizeof(int);
    unordered_map<int, int> posArr;

    while (TRY_COUNT-- > 0)
        posArr[getMaximumElementIndex(arr, n)]++;

    for (unordered_map<int, int>::const_iterator iter = posArr.begin(); iter != posArr.end(); ++iter)
        cout << iter->first << " - " << iter->second << endl;

    system("PAUSE");
	return 0;
}

