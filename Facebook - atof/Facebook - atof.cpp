// Implement atof, which converts a string representation of a float(like "342.18E-10") to an actual float 
// without using any built - in parsing functions.

#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    double atof(const string &str){
        int n = str.size(); if (n == 0) return 0;
        int curPos = 0;
        while (curPos < n && str[curPos] == ' ') ++curPos;
        if (curPos == n) return 0;

        //determine the sign
        bool negative = false;
        if (str[curPos] == '+') ++curPos;
        else if (str[curPos] == '-') {
            negative = true; ++curPos;
        }

        double result = 0;
        while (curPos < n && isDigit(str[curPos]))
            result = result * 10 + (str[curPos++] - '0');

        double postBase = 10;
        if (curPos < n && str[curPos] == '.') {
            ++curPos;
            while (curPos < n && isDigit(str[curPos])) {
                result += (str[curPos++] - '0') / postBase;
                postBase *= 10;
            }
        }

        if (curPos < n && (str[curPos] == 'e' || str[curPos] == 'E')){
            ++curPos;
            bool negBase = false;
            if (str[curPos] == '+') ++curPos;
            else if (str[curPos] == '-') { ++curPos; negBase = true; }

            int base = 0;
            while (curPos < n && isDigit(str[curPos]))
                base = base * 10 + (str[curPos++] - '0');
            double factor = 1;
            for (int i = 0; i < base; ++i) factor *= 10;
            if (negBase) factor = 1 / factor;
            result *= factor;
        }

        return negative ? -result : result;
    }

private:
    bool isDigit(char c){
        if (c >= '0' && c <= '9') return true;
        return false;
    }
};

int main()
{
    char buffer[100];
    string str;

    Solution so;
    while (cin.getline(buffer, 100)){
        str = buffer;
        printf("%40.20f\n", so.atof(str));
    }

    return 0;
}