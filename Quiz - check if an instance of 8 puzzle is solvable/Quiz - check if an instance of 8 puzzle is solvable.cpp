//What is 8 puzzle ?
//Given a 3¡Á3 board with 8 tiles(every tile has one number from 1 to 8) and one empty space.
//The objective is to place the numbers on tiles in order using the empty space.We can slide four adjacent(left, right, above and below) 
//tiles into the empty space.
//http ://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/


// Solution:
// Using BFS to find whether there is a path from the given initial state to the objective state

#include <iostream>
#include <unordered_set>
#include <queue>
using namespace std;

static const int neighborArr[9][4] = {
    { 1, 3, -1, -1 },   //0
    { 0, 2, 4, -1 },   //1
    { 1, 5, -1, -1 },   //2
    { 0, 4, 6, -1 },    //3
    { 1, 3, 5, 7 },     //4
    { 8, 4, 2, -1 },    //5
    { 3, 7, -1, -1 },   //6
    { 4, 6, 8, -1 },    //7
    { 5, 7, -1, -1 }    //8
};

static const long long TARGETBITMASK = 0x87654321;

long long MASK(int val, int pos) {
    return (((long long)val) << (4 * pos));
}

int VALUE(long long mask, int pos) {
    return (mask >> (4 * pos)) & 0xF;
}

bool solveUtil(long long bitmask, int blankPos, unordered_set<long long> &visitedState) {
    if (bitmask == TARGETBITMASK) return true;
    queue<long long> visitQ;
    queue<int> blankPosQ;
    visitQ.push(bitmask);
    visitedState.insert(bitmask);
    blankPosQ.push(blankPos);

    long long newBitmask = 0;
    int neighbor = -1;
    while (!visitQ.empty()) {
        bitmask = visitQ.front(); visitQ.pop();
        blankPos = blankPosQ.front(); blankPosQ.pop();

        for (int i = 0; i < 4; ++i) {
            neighbor = neighborArr[blankPos][i];
            if (neighbor < 0) break;

            newBitmask = bitmask;
            newBitmask |= MASK(VALUE(newBitmask, neighbor), blankPos);
            newBitmask &= ~MASK(0xF, neighbor);

            if (newBitmask == TARGETBITMASK) return true;
            if (visitedState.find(newBitmask) != visitedState.end()) continue;

            visitedState.insert(newBitmask);
            visitQ.push(newBitmask);
            blankPosQ.push(neighbor);
        }
    }
    return false;
}

bool puzzleSolvable(const int board[9]) {
    long long bitmask = 0;
    int blankPos = -1;
    for (int i = 0; i < 9; ++i) {
        if (board[i] > 0)
            bitmask |= MASK(board[i], i);
        else
            blankPos = i;
    }
    unordered_set<long long> visitedState;
    return solveUtil(bitmask, blankPos, visitedState);
}


void printBoard(const int board[9]) {
    int pos = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            cout << board[pos++] << " ";
        cout << endl;
    }
}

int main() {
    const int board1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    const int board2[9] = { 1, 8, 2, 0, 4, 3, 7, 6, 5 };
    const int board3[9] = { 8, 1, 2, 0, 4, 3, 7, 6, 5 };
    const int board4[9] = { 1, 2, 3, 4, 5, 0, 7, 8, 6 };

    cout << "******** Board 1 ********" << endl;
    printBoard(board1);
    if (puzzleSolvable(board1))
        cout << endl << "Solvable." << endl;
    else
        cout << endl << "Unsolvable." << endl;
    cout << endl;

    cout << "******** Board 2 ********" << endl;
    printBoard(board2);
    if (puzzleSolvable(board2))
        cout << endl << "Solvable." << endl;
    else
        cout << endl << "Unsolvable." << endl;
    cout << endl;


    cout << "******** Board 3 ********" << endl;
    printBoard(board3);
    if (puzzleSolvable(board3))
        cout << endl << "Solvable." << endl;
    else
        cout << endl << "Unsolvable." << endl;
    cout << endl;

    cout << "******** Board 4 ********" << endl;
    printBoard(board4);
    if (puzzleSolvable(board4))
        cout << endl << "Solvable." << endl;
    else
        cout << endl << "Unsolvable." << endl;
    cout << endl;

    system("PAUSE");
    return 0;
}