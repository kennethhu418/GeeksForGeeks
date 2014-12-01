// Given a string which contains no duplicate characters, find its rank among all its 
// permutations sorted lexicographically.
// For example, rank of ¡°abc¡± is 1, rank of ¡°acb¡± is 2, and rank of ¡°cba¡± is 6.

#include <iostream>
#include <cstring>
#include <string>
#include <assert.h>
using namespace std;

class Solution
{
public:
    int getLexicographicalRank(const string &str) {
        int n = str.size();
        if (n < 2) return n;

        Initialize(str);

        int permCnt = 1;
        for (int i = 2; i < n; ++i) permCnt *= i;

        int curCharRank = 0, totalRank = 0;
        for (int curPos = 0; curPos < n - 1; ++curPos) {
            curCharRank = getCharRank(str[curPos]);
            RemoveChar(str[curPos]);
            totalRank += curCharRank * permCnt;
            permCnt /= (n - 1 - curPos);
        }
        return totalRank + 1;
    }

private:
    int mOccupyCntArr[26];

    void Initialize(const string &str) {
        memset(mOccupyCntArr, 0, sizeof(mOccupyCntArr));
        for (int i = 0; i < str.size(); ++i)
            ++mOccupyCntArr[str[i] - 'a'];
    }

    int getCharRank(char c) {
        int rank = 0;
        for (int i = 0; i < c - 'a'; ++i)
            rank += mOccupyCntArr[i];
        return rank;
    }

    void RemoveChar(char c) {
        assert(mOccupyCntArr[c - 'a']);
        --mOccupyCntArr[c - 'a'];
    }
};

int main() {
    const string str = "bcad";
    Solution so;

    cout << so.getLexicographicalRank(str) << endl;
    return 0;
}