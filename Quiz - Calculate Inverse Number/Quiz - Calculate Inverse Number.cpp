#include <iostream>
#include <ctime>
#include <cmath>
#include <cstring>
#include <assert.h>
using namespace std;

#define MAX_COUNT 3000

class Solution
{
private:
    int bufferArr[MAX_COUNT];

    int merge(int * arr, int start, int k1, int k2) {
        if (k1 == 0 || k2 == 0) return 0;
        int start1 = start, start2 = start + k1, end1 = start2 - 1, end2 = start2 + k2 - 1, inv = 0, smaller = 0, pos = 0;
        while (start1 <= end1 && start2 <= end2) {
            while (start1 <= end1 && arr[start1] <= arr[start2]){
                inv += smaller;
                bufferArr[pos++] = arr[start1++];                
            }                
            if (start1 > end1) break;

            while (start2 <= end2 && arr[start1] > arr[start2]) {
                ++smaller; bufferArr[pos++] = arr[start2++];
            }
        }

        while (start1 <= end1) { inv += smaller; bufferArr[pos++] = arr[start1++]; }
        while (start2 <= end2) bufferArr[pos++] = arr[start2++];
        memmove(&arr[start], bufferArr, sizeof(int)*(k1 + k2));
        return inv;
    }

public:
    int calculateInv(int * arr, int n) {
        if (n < 2) return 0;
        int k1 = (n >> 1), k2 = n - k1;
        int inv1 = calculateInv(arr, k1);
        int inv2 = calculateInv(arr + k1, k2);
        int inv3 = merge(arr, 0, k1, k2);
        return inv1 + inv2 + inv3;
    }
};


int test_calculate_invs(const int *arr, int n) {
    int inv = 0;
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            if (arr[j] < arr[i]) ++inv;
        }
    }    
    return inv;
}

void generateArray(int * arr, int n, int max_val = 100) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % max_val;
}

int main()
{
    const int MAX_VAL = 1000;
    int arr[MAX_COUNT];
    int n = 0;
    Solution so;
    int inv1 = 0, inv2 = 0, tryTimes = 2000;

    srand(time(NULL));

    while (tryTimes-- > 0) {
        n = rand() % MAX_COUNT + 1;
        generateArray(arr, n, MAX_VAL);

        inv1 = test_calculate_invs(arr, n);
        inv2 = so.calculateInv(arr, n);
        assert(inv1 == inv2);
    }
    return 0;
}