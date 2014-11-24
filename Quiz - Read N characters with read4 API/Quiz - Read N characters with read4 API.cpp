//  Read N Characters Given Read4 II - Call multiple times
//  
//  The API : int read4(char *buf) reads 4 characters at a time from a file.
//  
//  The return value is the actual number of characters read.For example, it
//  returns 3 if there is only 3 characters left in the file.
//  
//  By using the read4 API, implement the function int read(char *buf, int n)
//  that reads n characters from the file.
//  
//  Note:
//  The read function may be called multiple times.

#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

int read4(char * buffer);

class Solution
{
private:
    char        residuleBuffer[5];
    int            remainingResiduleCnt;
    int            residuleBufferSize;

public:
    Solution() : remainingResiduleCnt(0), residuleBufferSize(0) {}

    int read(char * buf, int n) {
        int totalReadCnt = 0, curReadCnt = 0;

        curReadCnt = min(n, remainingResiduleCnt);
        memmove(buf, &residuleBuffer[residuleBufferSize - remainingResiduleCnt], curReadCnt);
        remainingResiduleCnt -= curReadCnt; totalReadCnt = curReadCnt; buf += curReadCnt;

        if (totalReadCnt == n) return totalReadCnt;

        int readPass = (n - curReadCnt) / 4, curReadPass = 0;
        while (curReadPass < readPass) {
            curReadCnt = read4(buf);  totalReadCnt += curReadCnt;
            ++curReadPass;  buf += curReadCnt;
            if (curReadCnt < 4) return totalReadCnt;
        }

        if (totalReadCnt == n) return totalReadCnt;

        curReadCnt = read4(residuleBuffer);
        residuleBufferSize = remainingResiduleCnt = curReadCnt;

        curReadCnt = min(curReadCnt, n - totalReadCnt);
        memmove(buf, residuleBuffer, curReadCnt);
        totalReadCnt += curReadCnt; remainingResiduleCnt -= curReadCnt;
        return totalReadCnt;
    }
};


/******************** Tests ******************/
const static string CONST_TEST_FILE = "We have changed the behavior of solution buttons, since some of you mentioned it was difficult to differentiate between the solutions that are available vs. the unavailable ones.\
Now if the solution is not yet available, the button will be disabled.Do you want to see our problem's analysis? Solve it and get your solution accepted now!\
Still have problem while using OJ ? Welcome to email admin@leetcode.com.";
static string test_file;
static int curCursor;

int read4(char * buf) {
    int cnt = 4;
    if (test_file.size() - curCursor < cnt) cnt = test_file.size() - curCursor;

    for (int i = 0; i < cnt; ++i)
        buf[i] = test_file[curCursor + i];

    curCursor += cnt;
    return cnt;
}

int main()
{
    string composedString;
    const int MAX_READ_CNT = 20;
    char buf[MAX_READ_CNT + 1];

    for (int tryCount = 0; tryCount < 200; ++tryCount) {
        Solution so;
        test_file = CONST_TEST_FILE.substr(0, 1 + rand() % CONST_TEST_FILE.size());
        composedString.clear(); curCursor = 0;

        int curN = 0, actualN = 0;
        while (true) {
            curN = 1 + rand() % MAX_READ_CNT;
            actualN = so.read(buf, curN);
            buf[actualN] = '\0';
            composedString += buf;
            if (actualN < curN) break;        
        }

        assert(composedString == test_file.c_str());    
    }

	return 0;
}

