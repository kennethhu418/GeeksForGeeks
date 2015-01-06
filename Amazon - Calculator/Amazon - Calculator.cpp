//  You have given a mathematical expression in string format.
//  Example: "3+ -12  *(-3 - 4 )/ 7"
//  You need to write function which will return final result of the given expression.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

#define INVALID_NUMBER  -9876543210

class Calculator{
public:
    double     calculate(const string &expStr) {
        double num = 0, data1 = 0, data2 = 0;
        OPT opt = INVALID_OPT, nextOpt = INVALID_OPT;
        int cursor = 0;
        stack<double>   dataStack;
        stack<OPT>  optStack;
        bool prevIsNumberOrRightEmbrace = false;
        while (cursor < expStr.size()) {
            nextOpt = getOperator(expStr, cursor, true);
            if (nextOpt == ERROR_OPT) break;

            if (nextOpt == INVALID_OPT || (nextOpt == MINUS && !prevIsNumberOrRightEmbrace)) {
                num = getNumber(expStr, cursor);
                if (num == INVALID_NUMBER) break;
                dataStack.push(num);
                prevIsNumberOrRightEmbrace = true;
                continue;
            }

            opt = getOperator(expStr, cursor);
            if (opt == INVALID_OPT) break;

            prevIsNumberOrRightEmbrace = false;

            if (optStack.empty() || opt == LEFT_EMBRACE)
                optStack.push(opt);
            else if (opt == RIGHT_EMBRACE) {
                while (optStack.size() && optStack.top() != LEFT_EMBRACE) {
                    nextOpt = optStack.top();  optStack.pop();
                    if (dataStack.empty()) return INVALID_NUMBER;
                    data1 = dataStack.top();  dataStack.pop();
                    if (dataStack.empty()) return INVALID_NUMBER;
                    data2 = dataStack.top();  dataStack.pop();
                    dataStack.push(calculate(data2, data1, nextOpt));
                }
                if (optStack.empty()) return INVALID_NUMBER;
                optStack.pop();
                prevIsNumberOrRightEmbrace = true;
            }
            else {
                while (optStack.size() && !isGreater(opt, optStack.top())) {
                    nextOpt = optStack.top();  optStack.pop();
                    if (dataStack.empty()) return INVALID_NUMBER;
                    data1 = dataStack.top();  dataStack.pop();
                    if (dataStack.empty()) return INVALID_NUMBER;
                    data2 = dataStack.top();  dataStack.pop();
                    dataStack.push(calculate(data2, data1, nextOpt));
                }
                optStack.push(opt);
            }
        }

        if (cursor < expStr.size()) return INVALID_NUMBER;

        while (optStack.size()) {
            nextOpt = optStack.top();  optStack.pop();
            if (dataStack.empty()) return INVALID_NUMBER;
            data1 = dataStack.top();  dataStack.pop();
            if (dataStack.empty()) return INVALID_NUMBER;
            data2 = dataStack.top();  dataStack.pop();
            dataStack.push(calculate(data2, data1, nextOpt));
        }

        if (dataStack.size() != 1) return INVALID_NUMBER;
        return dataStack.top();
    }

private:

    typedef enum __OPT{
        LEFT_EMBRACE = 0,
        RIGHT_EMBRACE = 1,
        PLUS = 2,
        MINUS = 3,
        MULTIPLY = 4,
        DIVIDE = 5,
        ERROR_OPT = 6,
        INVALID_OPT = 7
    }OPT;

    bool isGreater(OPT op1, OPT op2) {
        return (op1 >> 1) > (op2 >> 1);
    }

    int  removeSpaces(const string &str, int cursor) {
        while (cursor < str.size() && str[cursor] == ' ')
            ++cursor;
        return cursor;
    }

    double getNumber(const string &str, int &cursor) {
        cursor = removeSpaces(str, cursor);
        if (cursor >= str.size()) return INVALID_NUMBER;

        bool isNegative = false;
        if (str[cursor] == '-') {
            isNegative = true;
            ++cursor;
        }

        double result = 0;
        while (cursor < str.size() && (str[cursor] >= '0' && str[cursor] <= '9')) {
            result = 10 * result + str[cursor++] - '0';
        }
        if (cursor == str.size()) return isNegative ? -result : result;

        double pointPart = 0, base = 10;
        if (str[cursor] == '.') {
            ++cursor;
            while (cursor < str.size() && (str[cursor] >= '0' && str[cursor] <= '9')) {
                result += (str[cursor++] - '0') / base;
                base *= 10;
            }
        }
        return isNegative ? (0 - result) : result;
    }

    OPT getOperator(const string &str, int &cursor, bool isProbe = false) {
        cursor = removeSpaces(str, cursor);
        if (cursor >= str.size()) return INVALID_OPT;

        char optChar = str[cursor];
        if (!isProbe) ++cursor;
        else {
            if (optChar != '+' && optChar != '-' && optChar != '*' && optChar != '/' && optChar != '(' && optChar != ')'
                && (optChar < '0' || optChar > '9'))
                return ERROR_OPT;
        }

        switch (optChar) {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        case '(':
            return LEFT_EMBRACE;
        case ')':
            return RIGHT_EMBRACE;
        default:
            return INVALID_OPT;
        }
        return INVALID_OPT;
    }

    double calculate(double n1, double n2, OPT opt) {
        switch (opt) {
        case PLUS:
            return n1 + n2;
        case MINUS:
            return n1 - n2;
        case MULTIPLY:
            return n1 * n2;
        case DIVIDE:
            return n1 / n2;
        default:
            return INVALID_OPT;
        }
        return INVALID_NUMBER;
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