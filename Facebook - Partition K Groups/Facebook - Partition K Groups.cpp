//  There are N objects kept in a row.The ith object is at position x_i.You want to partition them into K groups.You want to move all objects 
//  belonging to the same group to the same position.Objects in two different groups may be placed at the same position.What is the 
//  minimum total amount by which you need to move the objects to accomplish this ?
//  
//  Input :
//  The first line contains the number of test cases T.T test cases follow.The first line contains N and K.The next line contains N space 
//  seperated integers, denoting the original positions x_i of the objects.
//  
//  Output :
//  Output T lines, containing the total minimum amount by which the objects should be moved.
//  
//  Constraints :
//              1 <= T <= 1000
//              1 <= K <= N <= 200
//              0 <= x_i <= 1000
//  
//  Sample Input :
//  3
//  3 3
//  1 1 3
//  3 2
//  1 2 4
//  4 2
//  1 2 5 7
//  
//  Sample Output :
//  0
//  1
//  3
//  
//  Explanation :
//  For the first case, there is no need to move any object.
//  For the second case, group objects 1 and 2 together by moving the first object to position 2.
//  For the third case, group objects 1 and 2 together by moving the first object to position 2 and 
//  group objects 3 and 4 together by moving object 3 to position 7. Thus the answer is 1 + 2 = 3.
//
//http://www.careercup.com/question?id=4804004722769920

#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;

#define MAX_COUNT 100
#define MAX_GROUP 100

class Solution
{
public:
    int calculateMinMovements(int arr[], int n, int K){
        if (n < 2 || n == K) return 0;
        sort(arr, arr + n);

        //Initialize 
        for (int i = 0; i < n; ++i){
            for (int j = i; j < n; ++j)
                singleGroupArr[i][j - i + 1] = getSingleGroupMovements(arr, i, j);
        }

        for (int i = 0; i < n; ++i) resultArr[i][1] = singleGroupArr[i][n - i];

        if (K == 1) return singleGroupArr[0][n];

        //Run DP
        int minMove = INT_MAX, curMove = 0;
        for (int p = 2; p <= K; ++p) {
            for (int i = n - p; i >= 0; --i){
                minMove = INT_MAX;
                for (int len = 1; len < n - i && len <= n - i + 1 - p; ++len) {
                    curMove = singleGroupArr[i][len] + resultArr[i + len][p - 1];
                    if (curMove < minMove) minMove = curMove;
                }
                resultArr[i][p] = minMove;
            }
        }
        return resultArr[0][K];
    }

private:
    int    resultArr[MAX_COUNT][MAX_GROUP];
    int    singleGroupArr[MAX_COUNT][MAX_COUNT];

    int getSingleGroupMovements(const int arr[], int start, int end) {
        int minPos = arr[start], maxPos = arr[end];
        int minMoves = INT_MAX, curMoves = 0;
        for (int pos = minPos; pos <= maxPos; ++pos) {
            curMoves = 0;
            for (int i = start; i <= end; ++i)
                curMoves += abs(pos - arr[i]);
            if (curMoves < minMoves) minMoves = curMoves;
        }
        return minMoves;
    }
};

int main()
{
    int arr1[] = { 1, 1, 3 };
    int n = sizeof(arr1) / sizeof(int);
    int K = 3;
    Solution so;

    cout << so.calculateMinMovements(arr1, n, K) << endl;

    int arr2[] = { 1, 2, 4 };
    n = sizeof(arr2) / sizeof(int);
    K = 2;
    cout << so.calculateMinMovements(arr2, n, K) << endl;

    int arr3[] = { 1, 2, 5, 7 };
    n = sizeof(arr3) / sizeof(int);
    K = 2;
    cout << so.calculateMinMovements(arr3, n, K) << endl;

    return 0;
}