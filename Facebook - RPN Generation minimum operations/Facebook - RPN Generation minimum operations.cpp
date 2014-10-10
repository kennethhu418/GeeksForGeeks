//  Imagine x is an operand and * is an operator. We say a string of x and * follows Reverse Polish notation if it is a postfix notation.
//  
//  For example strings xx*, x, and xx*xx** follow Reverse Polish notation.
//  
//  Given a string of x and *, what is the minimum operations ( insert, delete, and replace) needed to make the string follow the RPN?
//  
//  For example, xx* need 0 operation to follow RPN since it already follows RPN.
//  x*x needs two operations to become xx* which follows RPN.
//  *xx* needs one operation to become xx* which follows RPN.
//  
//  Your algorithm should work for a string of size up to 100.

#include <string>
#include <iostream>
using namespace std;

/*****************************************************************************************
*         Here is Zhipeng's DP solution, where time complexity is O(n^3) and space complexity is O(n^2)
*****************************************************************************************/
#define MAX_LEN 101
class Solution
{
private:
    int    resultArr[MAX_LEN][MAX_LEN];

public:
    int    getMinOperationsForRPN(const string &str){
        int n = str.size(); if (n == 0) return 0;
        if (str == "x") return 0; if (str == "*") return 1;
        if (isRPN(str)) return 0;

        //Initialize DP Array
        for (int i = 0; i < n; ++i){
            resultArr[i][0] = 0;
            if (str[i] == '*') resultArr[i][1] = 1;
            else resultArr[i][1] = 0;
        }

        //Run DP Array
        for (int len = 2; len <= n; ++len){
            for (int i = 0; i <= n - len; ++i){
                if (isRPN(str.substr(i, len))) {
                    resultArr[i][len] = 0; continue;
                }

                //A RPN is composed of (RPN1)(RPN2)*
                resultArr[i][len] = len; // case1: remove all chars in this range
                for (int k = 1; k < len; ++k){
                    //case2: RPN1 is empty and there is only RPN2, and there is no the last *
                    if (k + resultArr[i + k][len - k] < resultArr[i][len]) resultArr[i][len] = k + resultArr[i + k][len - k];
                    //case3: RPN2 is empty and there is only RPN1, and there is no the last *
                    if (len - k + resultArr[i][k] < resultArr[i][len]) resultArr[i][len] = len - k + resultArr[i][k];
                    //case4: Need to add one * at the end of this range
                    if (1 + resultArr[i][k] + resultArr[i + k][len - k] < resultArr[i][len]) resultArr[i][len] = 1 + resultArr[i][k] + resultArr[i + k][len - k];
                    //case5: The last char of this range is the *
                    if (str[i + len - 1] == '*' && len - k - 1 > 0 && resultArr[i][k] + resultArr[i + k][len - k - 1] < resultArr[i][len]) resultArr[i][len] = resultArr[i][k] + resultArr[i + k][len - k - 1];
                    //case5: The last char of this range is not * and we replace it to *
                    if (str[i + len - 1] != '*' && len - k - 1 > 0 && 1 + resultArr[i][k] + resultArr[i + k][len - k - 1] < resultArr[i][len]) resultArr[i][len] = 1 + resultArr[i][k] + resultArr[i + k][len - k - 1];
                }
            }
        }

        return resultArr[0][n];
    }

private:
    bool    isRPN(const string &str){
        if (str.size() == 0) return true;
        int n = str.size(), dataCount = 0;
        for (int i = 0; i < n; ++i){
            if (str[i] == 'x') ++dataCount;
            else if (dataCount < 2) return false;
            else --dataCount;
        }
        return dataCount == 1;
    }
};

/*****************************************************************************************
*                  Following is a full test with randomly generating string sequences
*****************************************************************************************/

string makeRandomString(int n){
    string str(n, '0');
    for (int i = 0; i < n; ++i)
        str[i] = ((rand() & 1) ? 'x' : '*');
    return str;
}

int main()
{
    const int MAX_LEN_TEST = 100;
    const int MAX_TRY_FOR_EACH_LEN = 30;

    string str;
    Solution so;

    for (int len = 2; len <= MAX_LEN_TEST; ++len){
        cout << "===========================================" << endl;
        cout << "\tNow test len " << len << endl;
        for (int j = 0; j < MAX_TRY_FOR_EACH_LEN; ++j){
            str = makeRandomString(len);
            cout << "The min operations for " << str.c_str() << " is " << so.getMinOperationsForRPN(str) << endl;
        }
        cout << endl;
    }
    return 0;
}