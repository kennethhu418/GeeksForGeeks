// Given an array of strings, find if the given strings can be chained to form a circle. A string X can be put 
// before another string Y in circle if the last character of X is same as first character of Y.
// 
// Examples:
// 
// Input: arr[] = {"geek", "king"}
// Output: Yes, the given strings can be chained.
// Note that the last character of first string is same
// as first character of second string and vice versa is
// also true.
// 
// Input: arr[] = {"for", "geek", "rig", "kaf"}
// Output: Yes, the given strings can be chained.
// The strings can be chained as "for", "rig", "geek" 
// and "kaf"
// 
// Input: arr[] = {"aab", "bac", "aaa", "cda"}
// Output: Yes, the given strings can be chained.
// The strings can be chained as "aaa", "aab", "bac" 
// and "cda"
// 
// Input: arr[] = {"aaa", "bbb", "baa", "aab"};
// Output: Yes, the given strings can be chained.
// The strings can be chained as "aaa", "aab", "bbb" 
// and "baa"
// 
// Input: arr[] = {"aaa"};
// Output: Yes
// 
// Input: arr[] = {"aaa", "bbb"};
// Output: No



//  The idea is to create a directed graph of all characters and then find if their is an eulerian circuit in the graph or not. 
//  If there is an eulerian circuit, then chain can be formed, otherwise not.
//  Note that a directed graph has eulerian circuit only if in degree and out degree of every vertex is same, and all non-zero
//  degree vertices form a single strongly connected component.
//  
//  Following are detailed steps of the algorithm.
//  
//  1) Create a directed graph g with number of vertices equal to the size of alphabet. We have created a graph with 26 vertices
//     in the below program.
//  
//  2) Do following for every string in the given array of strings.
//  бн..a) Add an edge from first character to last character of the given graph.
//  
//  3) If the created graph has eulerian circuit, then return true, else return false.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 26

typedef struct __CompoundEdge
{
    int     count;
    vector<int>     stringsRepresented;
    vector<bool>  edgeVisited;
    __CompoundEdge(int count = 0) : count(count) {}
}CompoundEdge;

class Solution
{
public:
    bool canStringsConcatenate(const string *strArr, int n, vector<int> &concatenatePath) {
        if (n == 0) return false;
        if (n == 1) {
            concatenatePath.push_back(0);
            return true;
        }

        InitializeEdgeArr(strArr, n);

        if (!isEulerianCyclePreliminarily()) return false;

        concatenatePath.clear();
        //we can walk from any node. Here we start from the first string's node.
        walkEulerianCycle(strArr[0][0] - 'a', concatenatePath);

        if (mTraversedEdgeCount != mEdgeCount){
            concatenatePath.clear();
            return false;
        }

        int start = 0, end = concatenatePath.size() - 1;
        while (start < end) swap(concatenatePath[start++], concatenatePath[end--]);
        return true;
    }

private:
    CompoundEdge mEdgeMatrix[ALPHABET_SIZE][ALPHABET_SIZE];    
    int mInDegree[ALPHABET_SIZE];
    int mOutDegree[ALPHABET_SIZE];
    int  mEdgeCount;
    int mTraversedEdgeCount;

    void InitializeEdgeArr(const string *strArr, int n) {
        for (int i = 0; i < ALPHABET_SIZE; ++i){
            for (int j = 0; j < ALPHABET_SIZE; ++j) {
                mEdgeMatrix[i][j].count = 0;
                mEdgeMatrix[i][j].stringsRepresented.clear();
                mEdgeMatrix[i][j].edgeVisited.clear();
            }
            mInDegree[i] = 0;
            mOutDegree[i] = 0;
        }

        mEdgeCount = 0;
        mTraversedEdgeCount = 0;

        char startC = 0, endC = 0;
        for (int i = 0; i < n; ++i) {
            startC = strArr[i][0] - 'a'; endC = strArr[i][strArr[i].size() - 1] - 'a';
            mEdgeMatrix[startC][endC].count++;
            mEdgeMatrix[startC][endC].stringsRepresented.push_back(i);
            mEdgeMatrix[startC][endC].edgeVisited.push_back(false);
            mInDegree[endC]++;  mOutDegree[startC]++;
            ++mEdgeCount;
        }       
    }

    bool isEulerianCyclePreliminarily() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (mInDegree[i] != mOutDegree[i]) return false;
        }
        return true;
    }

    void walkEulerianCycle(int curPos, vector<int> &concatenatePath) {
        int edgeCount = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            edgeCount = mEdgeMatrix[curPos][i].count;
            for (int j = 0; j < edgeCount; ++j) {
                if (mEdgeMatrix[curPos][i].edgeVisited[j]) continue;
                mEdgeMatrix[curPos][i].edgeVisited[j] = true;
                walkEulerianCycle(i, concatenatePath);
                concatenatePath.push_back(mEdgeMatrix[curPos][i].stringsRepresented[j]);
                ++mTraversedEdgeCount;
            }        
        }
    }
};


int main()
{
    Solution so;

    /*********test 1************/
    const string strArr1[] = { "adam", "meek", "koor", "rea", "klea", "make", "am", "room", "eye", "mask", "eager"};
    vector<int> result;
    bool canMakeCycle = so.canStringsConcatenate(strArr1, sizeof(strArr1) / sizeof(string), result);
    if (canMakeCycle) {
        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
            cout << strArr1[*iter] << "  ";
    }
    else
        cout << "Cannot make cycle !";
    cout << endl << endl;

    /*********test 2************/
    const string strArr2[] = { "for", "geek", "rig", "kaf" };
    canMakeCycle = so.canStringsConcatenate(strArr2, sizeof(strArr2) / sizeof(string), result);
    if (canMakeCycle) {
        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
            cout << strArr2[*iter] << "  ";
    }
    else
        cout << "Cannot make cycle !";
    cout << endl << endl;

    /*********test 3************/
    const string strArr3[] = { "am", "erk", "mook", "make" };
    canMakeCycle = so.canStringsConcatenate(strArr3, sizeof(strArr3) / sizeof(string), result);
    if (canMakeCycle) {
        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
            cout << strArr3[*iter] << "  ";
    }
    else
        cout << "Cannot make cycle !";
    cout << endl << endl;

    /*********test 4************/
    const string strArr4[] = { "rob", "laugh", "bear", "ear", "fill", "room", "make" };
    canMakeCycle = so.canStringsConcatenate(strArr4, sizeof(strArr4) / sizeof(string), result);
    if (canMakeCycle) {
        for (vector<int>::iterator iter = result.begin(); iter != result.end(); iter++)
            cout << strArr4[*iter] << "  ";
    }
    else
        cout << "Cannot make cycle !";
    cout << endl << endl;

    return 0;
    

}