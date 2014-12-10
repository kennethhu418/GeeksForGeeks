// Let us assume a represents 0, b represents 1, ..... z represents 25, aa represents 26, ab represents 27 ...... aaa represents 702, etc. 
// Now given an alpha representation, output the decimal number it represents.
// Besides, given a decimal number, please output its alpha representation.

//Solution:
//This is exactly the same question to "Facebook - Excel to Number" problem. The only difference is that in Excel to number problem, the starting index is 1 
//while our problem is starting from 0. We just need to translate our number to 1-starting-index based number by adding 1 to it, and then use the exact same procedure.

#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

string translateDecimalToAlphaNumber(long long n) {
    ++n; //translate 0-starting-index based number to 1-starting-index based number
    string result;
    int r = 0;
    while (n) {
        r = n % 26;
        if (r == 0) r = 26;
        n = (n - r) / 26;
        result += ('a' + r - 1);
    }

    int s = 0, e = result.size() - 1;
    while (s < e) swap(result[s++], result[e--]);
    return result;
}

long long translateAlphaNumberToDecimal(const string &str) {
    long long n = 0;
    for (int i = 0; i < str.size(); ++i)
        n = n * 26 + (str[i] - 'a' + 1);

    --n; //translate 1-starting-index based number to 0-starting-index based number
    return n;
}


/******************************************************************************
 ********************** Following are test codes ***********************************
 *****************************************************************************/
string generateNext(string numStr)
{
    string result;
    int n = numStr.size();
    bool carry_over = true;
    char c = '\0';
    for (int i = n - 1; i >= 0; --i) {
        c = numStr[i];
        if (carry_over) {
            carry_over = false;
            if (c >= 'a' && c <= 'y')  ++c;
            else { // c == 'z'
                c = 'a'; carry_over = true;
            }
        }
        result += c;
    }

    if (carry_over) result += 'a';

    int s = 0, e = result.size() - 1;
    while (s < e) swap(result[s++], result[e--]);
    return result;
}

int main()
{
    const long long MAX_TRY = 100000;

    //First verify translateDecimalToAlphaNumber logic
    string result, resultStandard = "a";
    for (long long i = 1; i <= MAX_TRY; ++i) {
        result = translateDecimalToAlphaNumber(i);
        resultStandard = generateNext(resultStandard);
        assert(result == resultStandard);
    }

    //Now verify translateAlphaNumberToDecimal logic
    long long curNumber = 0, standardNumber = 0;
    resultStandard = "a";
    while (curNumber < MAX_TRY) {
        curNumber = translateAlphaNumberToDecimal(resultStandard);
        assert(curNumber == standardNumber);

        ++standardNumber;
        resultStandard = generateNext(resultStandard);
    }

    return 0;
}