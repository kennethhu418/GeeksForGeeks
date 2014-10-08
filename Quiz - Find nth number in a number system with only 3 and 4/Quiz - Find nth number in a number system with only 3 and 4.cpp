//Find n¡¯th number in a number system with only 3 and 4
//
//Given a number system with only 3 and 4. Find the nth number in the number system.
//First few numbers in the number system are : 3, 4, 33, 34, 43, 44, 333, 334, 343, 344, 
//433, 434, 443, 444, 3333, 3334, 3343, 3344, 3433, 3434, 3443, 3444, ¡­

#include <iostream>
#include <string>
using namespace std;

string Find(int n)
{
    if (n == 0) return "";
    if (n == 1) return "3";
    if (n == 2) return "4";

    string result;
    while (n){
        result += (n & 1) ? '3' : '4';
        n = ((n - 1) >> 1);
    }

    int start = 0, end = result.size() - 1;
    while (start < end)
        swap(result[start++], result[end--]);

    return result;
}

int main() {
    int n;
    while (cin >> n){
        cout << n << "th number is " << Find(n) << endl;
    }
    return 0;
}