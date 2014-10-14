//  Given an unordered array of positive integers, create an algorithm to arrange the array so that makes sure when the array is sub - grouped by 
//  K elements, no group contains duplicate number
//  
//  Input: 2, 1, 1, 1, 3, 4, 4, 4, 5  K = 2
//  Output : 2, 1, 1, 3, 1, 4, 4, 5, 4

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>

using namespace std;

typedef struct __Elem
{
    int        val;
    int        count;
    __Elem(int val = 0, int count = 0) : val(val), count(count) {}
}Elem;

class Solution
{
public:
    void RearrangeArray(int * arr, int n, int K)
    {
        if (K < 2 || n <= 2 || K >= n) return;

        unordered_map<int, int> countMap;
        for (int i = 0; i < n; ++i)
            countMap[arr[i]]++;

        int distinceNumCount = countMap.size();
        Elem *elemArr = new Elem[distinceNumCount];
        GenerateElemArrAndSort(countMap, elemArr, n);

        int groupCount = (n + K - 1) / K;
        if (elemArr[0].count > groupCount) { delete[] elemArr; return; }

        int *groupPosArr = new int[groupCount], *groupRemainCount = new int[groupCount];
        int curPos = 0;
        for (int i = 0; i < groupCount; ++i) {
            groupPosArr[i] = curPos; groupRemainCount[i] = min(K, n - curPos);
            curPos += K;
        }

        curPos = 0;
        for (int i = 0; i < distinceNumCount; ++i) {
            while (curPos < groupCount && groupRemainCount[curPos] == 0) ++curPos;
            for (int j = 0; j < elemArr[i].count; ++j){
                arr[groupPosArr[curPos + j]++] = elemArr[i].val;
                groupRemainCount[curPos + j]--;
            }
        }

        delete[] elemArr; delete[] groupPosArr; delete[] groupRemainCount;
        return;
    }

private:
    static bool compare(const Elem &e1, const Elem &e2) {
        return e1.count > e2.count;
    }

    void GenerateElemArrAndSort(unordered_map<int, int> &countMap, Elem *elemArr, int n) {
        int cur = 0;
        for (unordered_map<int, int>::iterator iter = countMap.begin(); iter != countMap.end(); iter++) {
            elemArr[cur].val = iter->first;  elemArr[cur++].count = iter->second;
        }
        sort(elemArr, elemArr + cur, compare);
    }
};

void OutputArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int arr[] = { 2, 7, 9, 11, 12, 3, 3, 4, 4, 4, 5, 5, 5, 5 };
    int K = 4;
    int n = sizeof(arr) / sizeof(int);
    Solution so;

    so.RearrangeArray(arr, n, K);
    OutputArray(arr, n);

    return 0;
}