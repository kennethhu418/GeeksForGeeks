//  You have given a mathematical expression in string format.
//  Example: "3+ -12  *(-3 - 4 )/ 7"
//  You need to write function which will return final result of the given expression.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

#define INVALID_NUMBER INT_MIN

class Calculator {
private:
    enum Priority {
        PRIORITY_INVALID = 0,
        PRIORITY_LOW = 1,
        PRIORITY_MID = 2,
        PRIORITY_HIGH = 3
    };

    Priority PRI(char c) {
        switch (c) {
        case '(':
        case ')':
            return PRIORITY_HIGH;
        case '+':
        case '-':
            return PRIORITY_MID;
        case '*':
        case '/':
            return PRIORITY_LOW;
        default:
            break;
        }
        return PRIORITY_INVALID;
    }

public:
    int    calculate(const string &str) {
        if (str.size() == 0) return 0;
        int n = str.size(), curPos = 0;
        char probeChar = '\0';
        bool started = false;
        stack<int>    dataArr;
        stack<char>   operatorArr;

        while (curPos < n) {
            probeChar = probeNextChar(str, curPos);
            if (probeChar == '\0') break;
            if (probeChar == '(') {
                probeChar = getNextChar(str, curPos);
                operatorArr.push(probeChar);
                probeChar = probeNextChar(str, curPos);
                if (probeChar == '-')
                    dataArr.push(getNumber(str, curPos));
            }
            else if (probeChar == ')') {
                probeChar = getNextChar(str, curPos);
                while (true) {
                    if (operatorArr.empty()) return INVALID_NUMBER;
                    char opt = operatorArr.top(); operatorArr.pop();
                    if (opt == '(') break;
                    if (dataArr.empty()) return INVALID_NUMBER;
                    int data1 = dataArr.top(); dataArr.pop();
                    if (dataArr.empty()) return INVALID_NUMBER;
                    int data2 = dataArr.top(); dataArr.pop();
                    int data = calculate(data2, data1, opt);
                    dataArr.push(data);
                }
            }
            else if (probeChar == '+' || probeChar == '-' || probeChar == '*' || probeChar == '/') {
                if (probeChar == '-' && !started) {
                    dataArr.push(getNumber(str, curPos));
                }
                else {
                    probeChar = getNextChar(str, curPos);
                    Priority curPri, targetPri = PRI(probeChar);
                    while (!operatorArr.empty() && targetPri > (curPri = PRI(operatorArr.top()))) {
                        int data1 = dataArr.top(); dataArr.pop();
                        if (dataArr.empty()) return INVALID_NUMBER;
                        int data2 = dataArr.top(); dataArr.pop();
                        int data = calculate(data2, data1, operatorArr.top());
                        operatorArr.pop();
                        dataArr.push(data);
                    }
                    operatorArr.push(probeChar);
                }
            }
            else if (probeChar >= '0' && probeChar <= '9')
                dataArr.push(getNumber(str, curPos));
            else
                return INVALID_NUMBER;

            if (!started) started = true;
        }

        while (!operatorArr.empty()) {
            int data1 = dataArr.top(); dataArr.pop();
            if (dataArr.empty()) return INVALID_NUMBER;
            int data2 = dataArr.top(); dataArr.pop();
            int data = calculate(data2, data1, operatorArr.top());
            operatorArr.pop();
            dataArr.push(data);
        }

        return dataArr.size() == 1 ? dataArr.top() : INVALID_NUMBER;
    }

private:
    void removeSpaces(const string &str, int &pos) {
        while (pos < str.size() && str[pos] == ' ')
            ++pos;
    }

    char probeNextChar(const string &str, int &pos) {
        removeSpaces(str, pos);
        if (pos >= str.size()) return '\0';
        return str[pos];
    }

    char getNextChar(const string &str, int &pos) {
        char target = probeNextChar(str, pos);
        ++pos;
        return target;
    }

    int getNumber(const string &str, int &pos) {
        char c = probeNextChar(str, pos);
        if (pos == str.size()) return INVALID_NUMBER;

        bool negative = false;
        if (c == '-') {
            negative = true;
            ++pos;
        }

        int result = 0;
        while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9')
            result = 10 * result + str[pos++] - '0';
        return negative ? -result : result;
    }

    int calculate(int num1, int num2, char opt) {
        switch (opt) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        default:
            break;
        }
        return 0;
    }
};

int main() {
    double result = 0;
    char buffer[200];
    string expStr;
    Calculator cal;

    while (true) {
        cout << "Please Enter your expression:" << endl;
        if (!cin.getline(buffer, 200)) break;
        expStr = buffer;

        result = cal.calculate(expStr);
        if (result == INVALID_NUMBER)
            cout << "Invalid Input Expression!" << endl << endl;
        else
            cout << "= " << result << endl << endl;
    }
    return 0;
}