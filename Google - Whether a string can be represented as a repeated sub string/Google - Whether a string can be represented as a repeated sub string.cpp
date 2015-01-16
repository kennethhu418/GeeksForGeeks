//  Given a string ¡®str¡¯, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
//  
//  Examples:
//  
//  Input : str = "abcabcabc"
//  Output : true
//  The given string is 3 times repetition of "abc"
//  
//  Input : str = "abadabad"
//  Output : true
//  The given string is 2 times repetition of "abad"
//  
//  Input : str = "aabaabaabaab"
//  Output : true
//  The given string is 4 times repetition of "aab"
//  
//  Input : str = "abcdabc"
//  Output : false
//


//  There can be many solutions to this problem.The challenging part is to solve the problem in O(n) time.Below is a O(n) algorithm.
//  
//  Let the given string be ¡®str¡¯ and length of given string be ¡®n¡¯.
//  
//  1) Find length of the longest proper prefix of ¡®str¡¯ which is also a suffix.Let the length of the longest proper prefix suffix be ¡®len¡¯.
//       This can be computed in O(n) time using pre - processing step of KMP string matching algorithm.
//  
//  2) If value of ¡®n ¨C len¡¯ divides n(or ¡®n % (n - len)¡¯ is 0), then return true, else return false.
//  
//  In case of ¡®true¡¯, the substring ¡®str[0..n - len - 1]¡¯ is the substring that repeats n % (n - len) times.
//  
//  How does this work ?
//  length of longest proper prefix - suffix(or len) is always between 0 to n - 1. If len is n - 1, then all characters in string are same.
//  For example len is 3 for ¡°AAAA¡±.If len is n - 2 and n is even, then two characters in string repeat n / 2 times.For example ¡°ABABABAB¡±, 
//  length of lps is 6. The reason is if the first n - 2 characters are same as last n - 2 character, the starting from the first pair, every pair of characters 
//  is identical to the next pair.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <assert.h>
using namespace std;

class Solution {
private:
    void generateNextArr(const char *str, int n, vector<int> &nextArr) {
        int i = 0, j = -1;
        nextArr[i] = j;
        while (i < n - 1) {
            if (j == -1 || str[i] == str[j])
                nextArr[++i] = ++j;
            else
                j = nextArr[j];
        }
    }

    int strlen(const char *str) {
        int	n = 0;
        while (*str) {
            ++n; ++str;
        }
        return n;
    }

public:
    // returns the length of the repeated sub string
    // If there is no such sub string, return -1
    int isRepeatedString(const char *str) {
        int len = strlen(str);
        if (len < 2) return false;
        vector<int>	nextArr(len + 1, -1);
        generateNextArr(str, len + 1, nextArr);
        if (nextArr[len] < 1 || len % (len - nextArr[len]) != 0)
            return -1;
        return len - nextArr[len];
    }
};

/*************** TEST CODES BELOW **************************/
string generateString(int len) {
    string str;
    str.resize(len);
    for (int i = 0; i < len; ++i)
        str[i] = 'a' + rand() % 26;
    return str;
}

string generateRepeatString(const string &str, int repeatCount) {
    string result;
    while (repeatCount-- > 0)
        result += str;
    return result;
}

bool validate(const string &str, int unitSize) {
    string unitStr = str.substr(0, unitSize);
    int curPos = unitSize;
    while (curPos < str.size()) {
        if (unitStr != str.substr(curPos, unitSize))
            return false;
        curPos += unitSize;
    }
    return curPos == str.size();
}

// Driver method.
int main()
{
    const int MAX_UNIT_LEN = 20;
    const int MAX_REPEAT_CNT = 50;
    const int MAX_STRING_SIZE = 1000;
    char test_str[MAX_STRING_SIZE + 1];
    Solution so;
    int tryTimes = 60000;

    srand(time(NULL));

    while (tryTimes-- > 0) {
        if (rand() & 1) { //generate repeated string
            string unitStr = generateString(1 + rand() % MAX_UNIT_LEN);
            string str = generateRepeatString(unitStr, 2 + rand() % (MAX_REPEAT_CNT - 1));
            strcpy(test_str, str.c_str());
            assert(so.isRepeatedString(test_str) > 0);
        }
        else {
            string str = generateString(1 + rand() % MAX_STRING_SIZE);
            strcpy(test_str, str.c_str());
            int unitSize = so.isRepeatedString(test_str);
            if (unitSize > 0)
                assert(validate(str, unitSize));
        }
    }
    return 0;
}