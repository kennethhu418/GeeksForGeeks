//  polite number的意思是一个正整数可以表示为几个连续的正整数的和。
//  3 = 1 + 2
//  5 =     2 + 3
//  6 = 1 + 2 + 3
//  .
//  .
//  .. From 1point 3acres bbs
//  15 = 1 + 2 + 3 + 4 + 5
//                   4 + 5 + 6
//                              7 + 8
//  
//  给你一个正整数，让你求出一共有多少种表示的可能性，比如3就返回1，15就返回3.

// Solution 1:
// Use two pointers p1 and p2. Initialize p1 with 1 and p2 with 2 and curSum = 3.
// If curSum == n, then increase the totalCount that will be returned.
// If curSum > n, then remove the number at p1 and move on p1 and adjust curSum accordingly
// If curSum < n, then move on p2 and adjust curSum accordingly.

// Solution 2:
// Let us assume n = a + (a + 1) + ...... + (a + len - 1)
// That is, 2n = len*(2a + len - 1)
// From the above equation, we can see that the two parts have different odd/even property.
// When len is odd number, (2a + len - 1) is even number; when len is even number, 
// (2a + len - 1) is odd number. In other words, one of the two parts must be odd number (the other is
// natuarally even number of course)
// So the problems becomes how many odd numbers can be extracted from 2n.
// Assume 2n = 2^x * 3^y * 5^z ......
// Then the odd number count is odd_count = (y + 1) * (z + 1) * ......
// At last, the returned totalCount = odd_count - 1 because odd number 1 should not be any part.

// Solution 3:
// Let us assume n = a + (a + 1) + ...... + (a + len - 1)
// That is, 2n = len*(2a + len - 1)
// The limitations of the above equation is that len > 1 and a >= 1. Apply a >= 1 into the above
// equation, we can see that (2a + len - 1) > len. Thus, we can get len should be less than
// sqrt(2n).
// So now we get the first criteria: 1 < len < sqrt(2n)       -----------------------------  (1)
// From the above equation, we can also see that the two parts have different odd/even property.
// When len is odd number, (2a + len - 1) is even number; when len is even number, 
// This is the second criteria --------------------------------------------- (2)
// Combining (1) and (2), we can just try each number between 1 and sqrt(2n). If the current
// number current_num satisfies:
// 2n % current_num == 0 && 2n / current_num has different odd/even property with current_num,
// then the returned totalCount is increased by 1

#include <iostream>
using namespace std;

// Two pointer traversal
// Complexity: O(n)
int getCount1(int n) {
    if (n < 3) return 0;
    int start = 1, end = 2, curSum = 3, count = 0;
    while (end < n) {
        if (curSum == n) {
            ++count; ++end;
            curSum = curSum + end - start;
            ++start;
        }
        else if (curSum < n) {
            ++end; curSum += end;
        }
        else {
            curSum -= start; ++start;
            if (start == end) break;
        }
    }
    return count;
}

// Count how many combinations there are with the odd prime factors of the given number n.
// Complexity:  < O(log n)
int getCount2(int n) {
    if (n < 3) return 0;
    n <<= 1;
    // remove factor 2
    while ((n & 1) == 0) n >>= 1;

    int curFactor = 3, curFactorCount = 0, totalCount = 1;
    while (n > 1) {
        curFactorCount = 0;
        while (n % curFactor == 0) {
            ++curFactorCount; n /= curFactor;
        }
        if (curFactorCount > 0) totalCount *= (curFactorCount + 1);
        ++curFactor;
    }

    return totalCount - 1;
}

// Solve the equation
// Complexity: O(sqrt(n))
int getCount3(int n) {
    if (n < 3) return 0;

    n <<= 1;
    int endVal = sqrt((double)n);
    if (endVal * endVal == n) --endVal;

    int len = 2, count = 0, otherPart = 0;
    while (len <= endVal) {
        if (n % len == 0) {
            otherPart = n / len;
            if (((len & 1) && !(otherPart & 1)) || (!(len & 1) && (otherPart & 1)))
                ++count;
        }
        ++len;
    }

    return count;
}

int main() {
    int count1 = 0, count2 = 0, count3 = 0;
    for (int i = 1; i <= 100000; ++i) {
        count1 = getCount1(i);
        count2 = getCount2(i);
        count3 = getCount3(i);
        if (count1 != count2 || count1 != count3) {
            cout << count1 << "  " << count2 << "  " << count3 << endl;
            int a = 0;
            a = 1 / a;
        }
    }
    return 0;
}