//String evaluation : eg.Given 3 + 2x + 5y - (3 + 5x) = 8 - 7y + 2x and X value
//, return Y value

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
private:
    double			mCoeff;
    double			mConstb;
    bool			mVerticalLine;

    typedef struct __Elem {
        int		coeffx;
        int		coeffy;
        int		constv;
        bool	isMinus;
    }Elem;

    void removeLeadingBlanks(const string &expStr, int &pos) {
        while (pos < expStr.size() && expStr[pos] == ' ')
            ++pos;
    }

    char probeNextChar(const string &expStr, int &pos) {
        removeLeadingBlanks(expStr, pos);
        if (pos >= expStr.size()) return '\0';
        return expStr[pos];
    }

    char getNextChar(const string &expStr, int &pos) {
        removeLeadingBlanks(expStr, pos);
        if (pos >= expStr.size()) return '\0';
        return expStr[pos++];
    }

    int getNumber(const string &expStr, int &pos) {
        removeLeadingBlanks(expStr, pos);
        if (pos >= expStr.size()) return 0;
        int result = 0;
        while (pos < expStr.size() && expStr[pos] >= '0' && expStr[pos] <= '9')
            result = 10 * result + expStr[pos++] - '0';
        return result;
    }

public:
    void Initialize(const string &expStr) {
        int n = expStr.size(), curPos = 0, curNum = 0;
        char probeChar = '\0';
        Elem curElem = { 0, 0, 0, false }, prevElem;
        stack<Elem>		stackA;
        while (curPos < n) {
            probeChar = probeNextChar(expStr, curPos);
            if (probeChar == '\0')
                break;
            else if (probeChar == '(') {
                probeChar = getNextChar(expStr, curPos);
                stackA.push(curElem);
                curElem.coeffx = curElem.coeffy = curElem.constv = 0;
                curElem.isMinus = false;
            }
            else if (probeChar == ')') {
                probeChar = getNextChar(expStr, curPos);
                prevElem = stackA.top(); stackA.pop();
                if (prevElem.isMinus) {
                    prevElem.coeffx -= curElem.coeffx;
                    prevElem.coeffy -= curElem.coeffy;
                    prevElem.constv -= curElem.constv;
                }
                else {
                    prevElem.coeffx += curElem.coeffx;
                    prevElem.coeffy += curElem.coeffy;
                    prevElem.constv += curElem.constv;
                }
                curElem = prevElem;
            }
            else if (probeChar == '+') {
                probeChar = getNextChar(expStr, curPos);
                curElem.isMinus = false;
            }
            else if (probeChar == '-') {
                probeChar = getNextChar(expStr, curPos);
                curElem.isMinus = true;
            }
            else if (probeChar == '=') {
                probeChar = getNextChar(expStr, curPos);
                curElem.isMinus = true;
                stackA.push(curElem);
                curElem.coeffx = curElem.coeffy = curElem.constv = 0;
                curElem.isMinus = false;
            }
            else if (probeChar == 'x') {
                probeChar = getNextChar(expStr, curPos);
                curElem.coeffx = curElem.isMinus ? curElem.coeffx - 1 : curElem.coeffx + 1;
            }
            else if (probeChar == 'y') {
                probeChar = getNextChar(expStr, curPos);
                curElem.coeffy = curElem.isMinus ? curElem.coeffy - 1 : curElem.coeffy + 1;
            }
            else {
                curNum = getNumber(expStr, curPos);
                probeChar = probeNextChar(expStr, curPos);
                if (probeChar == 'x') {
                    curElem.coeffx = curElem.isMinus ? curElem.coeffx - curNum : curElem.coeffx + curNum;
                    probeChar = getNextChar(expStr, curPos);
                }
                else if (probeChar == 'y') {
                    curElem.coeffy = curElem.isMinus ? curElem.coeffy - curNum : curElem.coeffy + curNum;
                    probeChar = getNextChar(expStr, curPos);
                }
                else
                    curElem.constv = curElem.isMinus ? curElem.constv - curNum : curElem.constv + curNum;
            }
        }

        prevElem = stackA.top(); stackA.pop();
        prevElem.coeffx -= curElem.coeffx;
        prevElem.coeffy -= curElem.coeffy;
        prevElem.constv -= curElem.constv;
        curElem = prevElem;

        if (curElem.coeffy == 0)
            mVerticalLine = true;
        else {
            mVerticalLine = false;
            mCoeff = -curElem.coeffx / (double)curElem.coeffy;
            mConstb = -curElem.constv / (double)curElem.coeffy;
        }
    }

    double getVal(double x) {
        if (mVerticalLine)
            return rand();
        return mCoeff * x + mConstb;
    }
};


// (2 x - (4y + (-6) ) - (3x-y+1)) + 4x - 6 = 5y
int main() {
    string expStr;
    int x, y;
    Solution so;

    cout << "New Expression String : " << endl;
    getline(cin, expStr);

    so.Initialize(expStr);
    cout << "x = ";
    while (cin >> x) {
        if (x == 0) break;
        cout << "y = " << so.getVal(x) << endl << endl;
        cout << "x = ";
    }

    return 0;
}