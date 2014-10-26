//  Given an integer, find the next biggest integer whose digits are in increasing order.
//  
//  Example:
//  Input : 118
//  Output : 123
//  
//  Input : 127
//  Output : 234
//  
//  Input : 987
//  Output : 1234

#include <iostream>
#include <assert.h>
using namespace std;

class Solution
{
public:
    int getNextLargerIncreasingNumber(int n) {
        if (n < 9) return n + 1;

        long long base = 1; int d = 0;
        while (base <= n) {
            base *= 10; ++d;
        }
        base /= 10; --d;

        int curD = d, prevDigit = -1, curDigit = -1;
        while (curD >= 0) {
            curDigit = (n / base) % 10;
            if (curDigit == prevDigit) break;
            if (curDigit < prevDigit) {
                n = ((n / (10 * base)) * 10 + prevDigit)*base + n%base;
                break;
            }
            base /= 10; --curD; prevDigit = curDigit;
        }
        if (curD < 0) { base = 1; curD = 0; }

        while (curD <= d) {
            curDigit = (n / base) % 10 + 1;
            if (curD <= 9 - curDigit) return constructNumber(n / base + 1, curD);
            ++curD; base *= 10;
        }
        return constructNumber(1, d + 1);
    }

private:
    int constructNumber(int num, int d) {
        int digit = num % 10 + 1;
        while (d-- > 0)
            num = 10 * num + digit++;
        return num;
    }
};

class Solution2
{
private:
    bool isIncreasingNumber(int n) {
        if (n < 10) return true;
        int curNumber = 0, prevNumber = 10;
        while (n) {
            curNumber = n % 10; n /= 10;
            if (curNumber >= prevNumber) return false;
            prevNumber = curNumber;
        }
        return true;
    }

public:
    int getNextLargerIncreasingNumber(int n) {
        ++n;
        while (!isIncreasingNumber(n)) ++n;
        return n;
    }
};

int main()
{
    Solution so; Solution2 so2;
    int targetNum = 0;
    for (int n = 9; n <= 12000; ++n) {
        targetNum = so.getNextLargerIncreasingNumber(n);
        cout << "Next number of " << n << " is " << targetNum << endl;
        assert(targetNum == so2.getNextLargerIncreasingNumber(n));
    }
    return 0;
}