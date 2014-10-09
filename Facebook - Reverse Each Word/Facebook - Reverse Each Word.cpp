//Code a function that receives a string composed by words separated by spaces and returns a string where 
//words appear in the same order but than the original string, but every word is inverted.
//Example, for this input string
//
//@"the boy ran"
//the output would be
//
//@"eht yob nar"
//
//Tell the complexity of the solution.

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

static inline void reverseWord(char *start, char* end){
    while (start < end) swap(*(start++), *(end--));
}

static inline char * getNextWordStart(char *str){
    while (*str && *str == ' ') ++str;
    return str;
}

static inline char * getNextWordEnd(char *str){
    while (*str && *str != ' ') ++str;
    return str;
}

static void reverseWords(char *str){
    char* wordStart = getNextWordStart(str), *wordEnd = NULL;

    while (*wordStart){
        wordEnd = getNextWordEnd(wordStart);
        reverseWord(wordStart, wordEnd - 1);
        wordStart = getNextWordStart(wordEnd);
    }
}

int main() {
    char str[100]; str[0] = '\0';
    cin.getline(str, 100);
    while (str[0] != '\0'){
        cout << "------------------------------" << endl;
        cout << str << endl;
        reverseWords(str);
        cout << str << endl;
        reverseWords(str);
        cout << str << endl;
        cin.getline(str, 100);
    }
    return 0;
}