//  Given a set of n integers, divide the set in two subsets of n / 2 sizes each such that the difference of the sum of two subsets is as minimum as 
//  possible.If n is even, then sizes of two subsets must be strictly n / 2 and if n is odd, then size of one subset must be(n - 1) / 2 and size of other 
//  subset must be(n + 1) / 2.
//  
//  For example, let given set be{ 3, 4, 5, -3, 100, 1, 89, 54, 23, 20 }, the size of set is 10. Output for this set should be{ 4, 100, 1, 23, 20 } and
//  { 3, 5, -3, 89, 54 }.Both output subsets are of size 5 and sum of elements in both subsets is same(148 and 148).
//  Let us consider another example where n is odd.Let given set be{ 23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4 }.The output subsets should be
//  { 45, -34, 12, 98, -1 } and{ 23, 0, -99, 4, 189, 4 }.The sums of elements in two subsets are 120 and 121 respectively.

#include <iostream>
#include <cstring>
#include <cstdio>
#include <assert.h>
using namespace std;


/************************************************************
* Here is my DP Solution
***********************************************************/

#define MAX_N 12
#define MAX_S  60


int calculateSum(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += arr[i];
    return sum;
}

void getMaxSum(int *arr, int n, int* resultArr1, int *resultArr2, int targetSum, int targetCount) {
    int sumArr[MAX_N + 1][MAX_N + 1][MAX_S + 1];
    bool selectArr[MAX_N + 1][MAX_N + 1][MAX_S + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= targetCount; ++j) {
            for (int s = 0; s <= targetSum; ++s) {
                sumArr[i][j][s] = -1;
                selectArr[i][j][s] = false;
            }
        }
    }

    sumArr[n][0][0] = 0;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= targetCount && j <= n - i; ++j) {
            for (int s = 0; s <= targetSum; ++s) {
                sumArr[i][j][s] = sumArr[i + 1][j][s];
                if (s >= arr[i] && sumArr[i + 1][j - 1][s - arr[i]] >= 0 && arr[i] + sumArr[i + 1][j - 1][s - arr[i]] > sumArr[i][j][s]) {
                    selectArr[i][j][s] = true;
                    sumArr[i][j][s] = arr[i] + sumArr[i + 1][j - 1][s - arr[i]];
                }
            }
        }
    }

    int pos1 = 0, pos2 = 0;
    for (int i = 0; i < n; ++i) {
        if (selectArr[i][targetCount][targetSum]) {
            resultArr1[pos1++] = arr[i];
            --targetCount;
            targetSum -= arr[i];
        }
        else
            resultArr2[pos2++] = arr[i];
    }
    assert(targetSum == 0);
    assert(targetCount == 0);
}

void TugOfWar(int *arr, int n, int* resultArr1, int *resultArr2) {
    if (n < 2) return;
    int totalSum = calculateSum(arr, n);
    int targetSum = (totalSum >> 1);
    int targetN = (n >> 1);

    getMaxSum(arr, n, resultArr1, resultArr2, targetSum, targetN);
    if (!(n & 1))
        return;

    int *resultArr1Buffer = new int[targetN];
    int *resultArr2Buffer = new int[targetN + 1];
    getMaxSum(arr, n, resultArr2Buffer, resultArr1Buffer, targetSum, targetN + 1);

    int diff1 = abs(calculateSum(resultArr1, targetN) - calculateSum(resultArr2, targetN + 1));
    int diff2 = abs(calculateSum(resultArr1Buffer, targetN) - calculateSum(resultArr2Buffer, targetN + 1));
    if (diff2 < diff1) {
        memmove(resultArr1, resultArr1Buffer, targetN * sizeof(int));
        memmove(resultArr2, resultArr2Buffer, (targetN + 1) * sizeof(int));
    }

    delete[] resultArr1Buffer;
    delete[] resultArr2Buffer;
}



/************************************************************
* Here is one brute force / backtracing solution
***********************************************************/

// function that tries every possible solution by calling itself recursively
void TOWUtil(int* arr, int n, bool* curr_elements, int no_of_selected_elements,
    bool* soln, int* min_diff, int sum, int curr_sum, int curr_position)
{
    // checks whether the it is going out of bound
    if (curr_position == n)
        return;

    // checks that the numbers of elements left are not less than the
    // number of elements required to form the solution
    if ((n / 2 - no_of_selected_elements) > (n - curr_position))
        return;

    // consider the cases when current element is not included in the solution
    TOWUtil(arr, n, curr_elements, no_of_selected_elements,
        soln, min_diff, sum, curr_sum, curr_position + 1);

    // add the current element to the solution
    no_of_selected_elements++;
    curr_sum = curr_sum + arr[curr_position];
    curr_elements[curr_position] = true;

    // checks if a solution is formed
    if (no_of_selected_elements == n / 2)
    {
        // checks if the solution formed is better than the best solution so far
        if (abs(sum / 2 - curr_sum) < *min_diff)
        {
            *min_diff = abs(sum / 2 - curr_sum);
            for (int i = 0; i<n; i++)
                soln[i] = curr_elements[i];
        }
    }
    else
    {
        // consider the cases where current element is included in the solution
        TOWUtil(arr, n, curr_elements, no_of_selected_elements, soln,
            min_diff, sum, curr_sum, curr_position + 1);
    }

    // removes current element before returning to the caller of this function
    curr_elements[curr_position] = false;
}

// main function that generate an arr
void tugOfWar(int *arr, int n)
{
    // the boolen array that contains the inclusion and exclusion of an element
    // in current set. The number excluded automatically form the other set
    bool* curr_elements = new bool[n];

    // The inclusion/exclusion array for final solution
    bool* soln = new bool[n];

    int min_diff = INT_MAX;

    int sum = 0;
    for (int i = 0; i<n; i++)
    {
        sum += arr[i];
        curr_elements[i] = soln[i] = false;
    }

    // Find the solution using recursive function TOWUtil()
    TOWUtil(arr, n, curr_elements, 0, soln, &min_diff, sum, 0, 0);

    // Print the solution
    int s1 = 0, s2 = 0;
    cout << "The first subset is: ";
    for (int i = 0; i<n; i++)
    {
        if (soln[i] == true) {
            cout << arr[i] << " ";
            s1 += arr[i];
        }
    }
    cout << "\nThe second subset is: ";
    for (int i = 0; i<n; i++)
    {
        if (soln[i] == false) {
            cout << arr[i] << " ";
            s2 += arr[i];
        }
    }
    cout << "\nThe diff is " << abs(s1 - s2) << endl;
}



/************************************************************
* Here is the test
***********************************************************/
int main()
{
    int arr[] = { 3, 6, 1, 9, 12, 11, 2, 20, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int n1 = (n >> 1);
    int n2 = n - n1;
    int *res1Arr = new int[n1];
    int *res2Arr = new int[n2];

    cout << "Brute Force Result is : " << endl;
    tugOfWar(arr, n);
    cout << endl << endl;

    cout << "My Result is:" << endl;
    TugOfWar(arr, n, res1Arr, res2Arr);
    int s1 = 0, s2 = 0;
    // Print the solution
    cout << "The first subset is: ";
    for (int i = 0; i < n1; i++)
        cout << res1Arr[i] << " ";
    cout << "\nThe second subset is: ";
    for (int i = 0; i<n2; i++)
        cout << res2Arr[i] << " ";
    cout << endl;
    s1 = calculateSum(res1Arr, n1); s2 = calculateSum(res2Arr, n2);
    cout << "The diff is " << abs(s1 - s2) << endl;
    delete[] res1Arr; delete[] res2Arr;
    return 0;
}