//The following is a description of the instance of this famous puzzle involving n = 2 eggs and a 
//building with k = 36 floors.
//
//Suppose that we wish to know which stories in a 36 - story building are safe to drop eggs from, 
//and which will cause the eggs to break on landing.We make a few assumptions :
//
//бн..An egg that survives a fall can be used again.
//бн..A broken egg must be discarded.
//бн..The effect of a fall is the same for all eggs.
//бн..If an egg breaks when dropped, then it would break if dropped from a higher floor.
//бн..If an egg survives a fall then it would survive a shorter fall.
//бн..It is not ruled out that the first - floor windows break eggs, nor is it ruled out that the 36th - floor do not cause an egg to break.
//
//If only one egg is available and we wish to be sure of obtaining the right result, the experiment 
//can be carried out in only one way.Drop the egg from the first - floor window; if it survives, 
//drop it from the second floor window.Continue upward until it breaks.In the worst case, this 
//method may require 36 droppings.Suppose 2 eggs are available.What is the least number of egg - 
//droppings that is guaranteed to work in all cases ?
//The problem is not actually to find the critical floor, but merely to decide floors from which 
//eggs should be dropped so that total number of trials are minimized.
//
//In this post, we will discuss solution to a general problem with n eggs and k floors.

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_FLOORS 201
#define MAX_EGGS 21

static int resultArr[MAX_FLOORS][MAX_EGGS];
static int dropArr[MAX_FLOORS][MAX_EGGS];

int solveEggDropPuzzle(int n, int m) {
    if (m == 0 || n == 0) { resultArr[n][m] = 0;  return 0; }
    if (m == 1) { resultArr[n][m] = n; return n; }

    for (int i = 0; i <= m; ++i)
        resultArr[0][i] = 0;
    for (int i = 0; i <= n; ++i)
        resultArr[i][1] = i;

    int curDrops = 0, minDrop = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            resultArr[i][j] = n + 100;
            for (int k = 0; k < i; ++k) {
                curDrops = 1 + max(resultArr[k][j - 1], resultArr[i - k - 1][j]);
                if (curDrops < resultArr[i][j]) {
                    resultArr[i][j] = curDrops;
                    minDrop = k;
                }
            }
            dropArr[i][j] = minDrop;
        }
    }
    return resultArr[n][m];
}

void outputResult(int n, int m) {
    int startF = 1, endF = n, dropF = 0;
    cout << "Minimum Drops in worse case is : " << resultArr[n][m] << endl;
    while (n > 0 && m > 1) {
        dropF = dropArr[n][m];
        cout << " " << startF + dropF;
        if (resultArr[dropF][m - 1] >= resultArr[n - dropF - 1][m]) {
            endF = startF + dropF - 1;
            n = dropF; --m;
        }
        else {
            startF = startF + dropF + 1;
            n -= (dropF + 1);
        }
    }
    if (m == 1) {
        for (int i = startF; i <= endF; ++i) cout << " " << i;
    }
    cout << endl;
}

int main()
{
    for (int floors = 2; floors < MAX_FLOORS; floors++){
        for (int eggs = 1; eggs < MAX_EGGS; ++eggs) {
            solveEggDropPuzzle(floors, eggs);
            cout << "\n**************************************************" << endl;
            cout << "Result of " << floors << " floors and " << eggs << " eggs: " << endl;
            outputResult(floors, eggs);
        }
    }
    return 0;
}