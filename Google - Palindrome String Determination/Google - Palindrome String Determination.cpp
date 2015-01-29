// 1. 给定一个string，判断能否用这个string来组成一个palindrome。e.g. 'uber' -->
// False, 'aab' --> True, 'carecra' --> True
// 
// 2. Follow up : 给出所有能够组成的palindrome

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Output all palindromes
class Solution {
public:
    void outputPalindromes(const string &str) {
        int n = str.size();
        if (n < 2) {
            cout << str << endl;
            return;
        }

        for (int i = 0; i < n; ++i)
            mMap[str[i]]++;

        char oddChar = '\0';
        for (unordered_map<char, unsigned int>::iterator iter = mMap.begin();
            iter != mMap.end(); ++iter) {
            if (iter->second & 1) {
                if (oddChar != '\0')	return;
                oddChar = iter->first;
            }
        }

        string innerStr;
        if (oddChar != '\0') {
            innerStr = oddChar;
            mMap[oddChar]--;
            if (mMap[oddChar] == 0)
                mMap.erase(oddChar);
        }

        outputPalindromesInternal(innerStr);
        mMap.clear();
    }

private:
    unordered_map<char, unsigned int>	mMap;

    void outputPalindromesInternal(const string &innerStr) {
        bool foundRemainingChars = false;
        string nextInnerStr;
        for (unordered_map<char, unsigned int>::iterator iter = mMap.begin();
            iter != mMap.end(); ++iter) {
            if (iter->second == 0) continue;
            if (!foundRemainingChars)
                foundRemainingChars = true;

            nextInnerStr = iter->first;
            nextInnerStr += innerStr;
            nextInnerStr += iter->first;
            iter->second -= 2;

            outputPalindromesInternal(nextInnerStr);

            iter->second += 2;
        }

        if (!foundRemainingChars)
            cout << innerStr << endl;
    }
};

int main() {
    string  str = "carecra";
    Solution so;
    so.outputPalindromes(str);
    return 0;
}