/*******************************************
*           KMP Algorithm
******************************************/

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <assert.h>
using namespace std;

class Solution
{
private:
    int        size;
    int        *nextArr;

    void Initialize(const char *ptr) {
        const char *p = ptr;
        size = 0;
        while (*p != '\0') { ++p; ++size; }

        int i = 0, j = -1;
        nextArr = new int[size];
        nextArr[i] = j;
        while (i < size - 1) {
            if (j == -1 || ptr[i] == ptr[j])
                nextArr[++i] = ++j;
            else
                j = nextArr[j];
        }
    }

    void Free() { delete[] nextArr; }

public:
    vector<int> search(const char *str, const char *ptr) {
        vector<int> result;
        if (*str == '\0' && *ptr == '\0') { result.push_back(0); return result; }
        if (*str == '\0' || *ptr == '\0') return result;

        Initialize(ptr);

        int i = 0, j = 0;
        while (str[i] != '\0') {
            if (str[i] == ptr[j]) { ++i; ++j; continue; }

            if (ptr[j] == '\0') { result.push_back(i - size); --j; --i; }

            if (nextArr[j] == -1) { ++i; j = 0; continue; }
            j = nextArr[j];
        }
        if (ptr[j] == '\0') result.push_back(i - size);
        Free();
        return result;
    }
};

void generateString(char * str, int n) {
    for (int i = 0; i < n; ++i)
        str[i] = 'a' + rand() % 26;
    str[n] = '\0';
}

void generatePattern(char *pattern, char *str, int n, int patternN) {
    int start = rand() % (n - patternN + 1);
    while (n-- > 0) {
        *pattern = *(str + start);
        ++pattern; ++start;
    }
    *pattern = '\0';
}

bool verify(char *str, char *ptr, int start, int n) {
    while (n-- > 0) {
        if (str[start] != *ptr) return false;
        ++start; ++ptr;
    }
    return true;
}

int main()
{
    const int MAX_LEN = 1200;
    char str[MAX_LEN + 1];
    char ptr[MAX_LEN + 1];
    int tryLens = MAX_LEN, eachTryTimes = 20;
    int strLen = 0, ptrLen = 0;
    Solution so;
    vector<int> result;

    srand(time(NULL));

    for (strLen = 2; strLen <= tryLens; ++strLen) {
        generateString(str, strLen);
        //cout << "***************************************************" << endl;
        //cout << "Search String: " << str << endl;

        for (ptrLen = 1; ptrLen <= strLen; ++ptrLen) {
            for (int i = 0; i < eachTryTimes; ++i) {
                if (i & 1){
                    generatePattern(ptr, str, strLen, ptrLen);
                    //cout << "  Extracted Pattern: " << ptr << endl;
                    result = so.search(str, ptr);
                    assert(result.size() > 0);
                    for (int j = 0; j < result.size(); ++j)
                        assert(verify(str, ptr, result[j], ptrLen));
                }
                else {
                    generateString(ptr, ptrLen);
                    //cout << "  Constructed Pattern: " << ptr << endl;
                    result = so.search(str, ptr);
                    for (int j = 0; j < result.size(); ++j)
                        assert(verify(str, ptr, result[j], ptrLen));                
                }
            }
        }
    }

    return 0;
}