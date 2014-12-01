//Given an array of non - negative integers.Find the largest multiple of 3 that can be formed from array elements.
//
//For example, if the input array is{ 8, 1, 9 }, the output should be ¡°9 8 1¡å, and if the input array is{ 8, 1, 7, 6, 0 }, output should be ¡°8 7 6 0¡å.

//Here is my idea :

//[Background Knowledge]
//1) A number is multiple of 3 if and only if the sum of digits of number is multiple of 3. For example, let us consider 8760, it is a multiple of 3 because sum of digits is 8 + 7 + 6 + 0 = 21, which is a multiple of 3.
//
//2) If a number is multiple of 3, then all permutations of it are also multiple of 3. This is the extension of 1).For example, since 6078 is a multiple of 3, the numbers 8760, 7608, 7068, ¡­..are also multiples of 3.
//
//3) We get the same remainder when we divide the number and sum of digits of the number.For example, if divide number 151 and sum of it digits 7, by 3, we get the same remainder 1.
//
//Let us consider a 3 digit number n to prove this fact.Let the first, second and third digits of n be ¡®a¡¯, ¡®b¡¯ and ¡®c¡¯ respectively.n can be written as
//n = 100 * a + 10 * b + c
//= (99 + 1)*a + (9 + 1)*b + c
//= 99 * a + 9 * b + a + b + c
//
//Since 99 * a + 9 * b can be dividided by 3, the remainder of n is the same with that of(a + b + c)
//
//[Algorithm]
//1. Split the original array ARR into three sub arrays ARR0, ARR1 and ARR2.ARR0 stores the numbers that can be divided by 3, ARR1 stores the numbers with remainder 1 when dividing by 3 and ARR2 stores the numbers with remainder 2 when dividing by 3
//
//2. Sum all the digits of all the numbers in the original array.Assume the sum is S.
//
//3. Three cases arise :
//¡­¡­3.1 S is divisible by 3. Based on Knowledge 3), this means the combination of all numbers in the original array can be divisible by 3. So directly go to step 4.
//
//¡­¡­3.2 The sum of digits produces remainder 1 when divided by 3.
//This means we should remove a remainder 1 from the original array numbers.This can be achieved by removing the smallest number ARR1[0] from ARR1 or the two smallest numbers ARR2[0] and ARR2[1] from ARR2.If the digits count of ARR1[0] is larger than that of the concatenate of ARR2[0] and ARR2[1], we remove ARR2[0] and ARR2[1]; If the digits count of the concatenate of ARR2[0] and ARR2[1] is larger than that of ARR1[0], we remove ARR1[0].If their digits count are the same, we remove the smaller one of(ARR1[0]) and(max of concatenate of ARR2[0] and ARR2[1]).
//
//¡­¡­3.3 The sum of digits produces remainder 2 when divided by 3.
//This means we should remove a remainder 2 from the original array numbers.This can be achieved by removing the smallest number ARR2[0] from ARR2 or the two smallest numbers ARR1[0] and ARR1[1] from ARR1.If the digits count of ARR2[0] is larger than that of the concatenate of ARR1[0] and ARR1[1], we remove ARR1[0] and ARR1[1]; If the digits count of the concatenate of ARR1[0] and ARR1[1] is larger than that of ARR2[0], we remove ARR2[0].If their digits count are the same, we remove the smaller one of(ARR2[0]) and(max of concatenate of ARR1[0] and ARR1[1]).
//
//4. Finally sort all the remaining numbers in the array by their MSDs(most significant digits) decreasingly and concatenate them together by order.If two numbers' MSDs are the same, sort them by the larger result of concatenating them.
//
//For example, assume there is three remaining numbers 5411, 876 and 87. 876 and 87 should be "larger" in sorting because 8 is greater than 5. And 87 should be "larger" than 876 because they have the same MSBs(i.e, 87), and when concating them together, 87876 is greater than 87687.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>
#include <ctime>
using namespace std;

class Solution
{
public:
    vector<int> constructLargestNumberOf3(const vector<int> &arr) {
        int n = arr.size();
        vector<int> result;
        if (n == 0) return result;

        int digitSum = getDigitSum(arr);
        if (digitSum % 3 == 0) {
            result = arr;
            sort(result.begin(), result.end(), customizedCmp);
            return result;
        }

        if (digitSum % 3 == 1) {
            int num1_1 = -1, num1_2 = -1;
            searchSmallestWithRemainder(arr, num1_1, num1_2, 1);
            int num2_1 = -1, num2_2 = -1;
            searchSmallestWithRemainder(arr, num2_1, num2_2, 2);
            if (num1_1 >= 0 && num2_2 < 0) {
                copyDataWithException(result, arr, num1_1, -1);
            }
            else if (num1_1 < 0 && num2_2 >= 0) {
                copyDataWithException(result, arr, num2_1, num2_2);
            }
            else if (num1_1 >= 0 && num2_2 >= 0) {
                string res1 = constructNumber(0, num1_1);
                string res2 = constructNumber(num2_1, num2_2);
                string res3 = constructNumber(num2_2, num2_1);
                if (res1.size() > res2.size() && res1.size() > res3.size())
                    copyDataWithException(result, arr, num2_1, num2_2);
                else if (res2.size() > res1.size() || res3.size() > res1.size())
                    copyDataWithException(result, arr, num1_1, -1);
                else if (res1 >= res2 && res1 >= res3)
                    copyDataWithException(result, arr, num2_1, num2_2);
                else
                    copyDataWithException(result, arr, num1_1, -1);
            }
        }
        else {
            int num1_1 = -1, num1_2 = -1;
            searchSmallestWithRemainder(arr, num1_1, num1_2, 1);
            int num2_1 = -1, num2_2 = -1;
            searchSmallestWithRemainder(arr, num2_1, num2_2, 2);
            if (num2_1 >= 0 && num1_2 < 0) {
                copyDataWithException(result, arr, num2_1, -1);
            }
            else if (num2_1 < 0 && num1_2 >= 0) {
                copyDataWithException(result, arr, num1_1, num1_2);
            }
            else if (num2_1 >= 0 && num1_2 >= 0) {
                string res1 = constructNumber(0, num2_1);
                string res2 = constructNumber(num1_1, num1_2);
                string res3 = constructNumber(num1_2, num1_1);
                if (res1.size() > res2.size() && res1.size() > res3.size())
                    copyDataWithException(result, arr, num1_1, num1_2);
                else if (res2.size() > res1.size() || res3.size() > res1.size())
                    copyDataWithException(result, arr, num2_1, -1);
                else if (res1 >= res2 && res1 >= res3)
                    copyDataWithException(result, arr, num1_1, num1_2);
                else
                    copyDataWithException(result, arr, num2_1, -1);
            }
        }

        sort(result.begin(), result.end(), customizedCmp);
        return result;
    }

private:
    int getDigitSum(int n) {
        int sum = 0;
        int r = 0;
        while (n) {
            r = n % 10;
            n /= 10;
            sum += r;
        }
        return sum;
    }

    void searchSmallestWithRemainder(const vector<int> &arr, int &res1, int &res2, int target_r) {
        int n = arr.size();
        res1 = res2 = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (arr[i] % 3 != target_r) continue;

            if (arr[i] < res1) {
                res2 = res1;
                res1 = arr[i];
            }
            else if (arr[i] < res2)
                res2 = arr[i];
        }

        if (res1 == INT_MAX) res1 = -1;
        if (res2 == INT_MAX) res2 = -1;    
    }

    void copyDataWithException(vector<int> &dest, const vector<int> &src, int t1, int t2) {
        for (int i = 0; i < src.size(); ++i) {
            if (src[i] == t1)
                t1 = -1;
            else if (src[i] == t2)
                t2 = -1;
            else
                dest.push_back(src[i]);
        }    
    }

    static string constructNumber(int n1, int n2) {
        if (n1 == 0 && n2 == 0) return "0";
        int r = 0;
        string result;
        while (n1) {
            r = n1 % 10;
            n1 /= 10;
            result += '0' + r;
        }

        int start = 0, end = result.size() - 1;
        while (start < end)
            swap(result[start++], result[end--]);

        start = result.size();
        while (n2) {
            r = n2 % 10;
            n2 /= 10;
            result += '0' + r;
        }

        end = result.size() - 1;
        while (start < end)
            swap(result[start++], result[end--]);
        return result;    
    }

    static bool customizedCmp(const int &n1, const int &n2) {
        string res1 = constructNumber(n1, n2);
        string res2 = constructNumber(n2, n1);
        if (res1.size() > res2.size()) return true;
        if (res2.size() > res1.size()) return false;
        return res1 > res2;
    }

public:
    int getDigitSum(const vector<int> &arr) {
        int sum = 0;
        for (int i = 0; i < arr.size(); ++i)
            sum += getDigitSum(arr[i]);
        return sum;
    }
};

void Output(const vector<int> &arr) {
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void GenerateArray(vector<int> &arr, int n, int MAX_VAL) {
    for (int i = 0; i < n; ++i)
        arr.push_back(rand() % MAX_VAL + 1);
}

int main()
{
    const int MAX_NUM = 600;
    const int MAX_TRY = 100;
    const int MAX_ARR_SIZE = 30;
    vector<int> srcArr;
    Solution so;
    vector<int> result;
    int tryTimes = MAX_TRY;

    srand(time(NULL));

    while (tryTimes-- > 0) {
        srcArr.clear();
        GenerateArray(srcArr, rand() % MAX_ARR_SIZE + 1, MAX_NUM);
        result = so.constructLargestNumberOf3(srcArr);
        assert(so.getDigitSum(result) % 3 == 0);

        cout << "Original Array is:" << endl;
        Output(srcArr);
        cout << "Constructed Maximum Number that is multiple of 3 is:" << endl;
        Output(result);
        cout << "-------------------------------------------" << endl;    
    }

	return 0;
}

