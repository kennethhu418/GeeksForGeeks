#include <iostream>
using namespace std;

/***************************************************************************
 * Microsoft Excel numbers cells are shown as A, B, C, D, .... Z, AA, AB, AC, AD, .... AZ, .....
 * They are actually corresponding to numbers 1, 2, 3, 4, .... 26, 27, 28, 29, 30, .... 52, ....
 * Given an excel representation, output the corresponding number and vise versa.
 ***************************************************************************/

/***************************************************************************
 * The idea is that we should realize it is actually a 26-ary number system, where each digit
 * is between [1, 26] (there is no digit 0!). A corresponds to 1, B corresponds to 2 ...........
 * Z corresponds to 26. So when transforming excel representation to decimal number, we
 * can just use the normal number calculation (by *26).
 * When transforming decimal number to excel representation, we still use the normal
 * number calculation (by / and % 26). However, there is no 0 in the excel 26-ary 
 * number system, and 0 is actually treated as 26. So when we get residule r = 0, we convert
 * it to 26 thus getting character Z. Please note that after treating r = 0 as r = 26, we should
 * get n/26 as (n - r)/26
 ***************************************************************************/
class Solution
{
public:
    long long excelToNumber(const string &str)
    {
        int n = str.size(); if (n == 0) return 0;
        long long result = 0, curNum = 0;
        for (int i = 0; i < n; ++i){
            curNum = str[i] - 'A' + 1;
            result = 26 * result + curNum;
        }
        return result;
    }

    string numberToExcel(long long num)
    {
        if (num == 0) return "";
        string result;
        long long r = 0;
        while (num){
            r = num % 26; if (r == 0) r = 26;
            num = (num - r) / 26;
            result += ('A' + r - 1);
        }
        int start = 0, end = result.size() - 1;
        while (start < end) swap(result[start++], result[end--]);
        return result;
    }
};

int main() {
    int tryCount = 1000;
    string *strArr = new string[tryCount];
    Solution so;

    cout << "The first " << tryCount << " excel strings are " << endl;
    for (int i = 0; i < tryCount; ++i){
        strArr[i] = so.numberToExcel(i + 1);
        cout << strArr[i].c_str() << endl;
    }

    cout << "The first " << tryCount << " numbers are " << endl;
    for (int i = 0; i < tryCount; ++i){
        cout << so.excelToNumber(strArr[i]) << endl;
    }

    delete[] strArr;
    return 0;
}