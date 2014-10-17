#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAX_SIZE 3000

class Solution
{
private:
    bool	visitedMatrix[MAX_SIZE];

    int	getBoardJumpToNumber(int **board, int n, int num) {
        int r = num / n, c = num % n;
        if (r & 1) return board[r][n - 1 - c];
        return board[r][c];
    }

    //return whether we climbed to an unvisited cell
    int climbLadders(int **board, int n, int startNum) {
        int nextNum = getBoardJumpToNumber(board, n, startNum);
        if (nextNum < 0) return startNum;

        int EndNum = nextNum; startNum = nextNum;
        while (startNum >= 0) {
            if (visitedMatrix[startNum]) return startNum;
            EndNum = startNum;
            visitedMatrix[startNum] = true;
            startNum = getBoardJumpToNumber(board, n, startNum);
        }
        visitedMatrix[EndNum] = false;
        return EndNum;
    }

public:
    int	minStepsForSnakeAndLadder(int **board, int m, int n) {
        if (m == 0 || n == 0) return 0; if (m == 1 && n == 1) return 0;
        queue<int> q1, q2;
        queue<int> *curLevelQ = &q1, *nextLevelQ = &q2;

        memset(visitedMatrix, 0, MAX_SIZE*sizeof(bool));

        int curSteps = 0, curNum = 0, nextNum = 0, target = m * n - 1;
        curNum = climbLadders(board, n, 0);
        if (curNum == target) return 0;
        visitedMatrix[curNum] = true;
        curLevelQ->push(curNum);

        while (!curLevelQ->empty()) {
            while (!curLevelQ->empty()) {
                curNum = curLevelQ->front(); curLevelQ->pop();
                //throw indices
                for (int k = 1; k < 7; ++k) {
                    nextNum = curNum + k;
                    if (nextNum == target) return curSteps + 1;
                    if (visitedMatrix[nextNum]) continue;
                    nextNum = climbLadders(board, n, nextNum);
                    if (!visitedMatrix[nextNum]){
                        nextLevelQ->push(nextNum);
                        visitedMatrix[nextNum] = true;
                    }
                }
            }

            swap(nextLevelQ, curLevelQ);
            ++curSteps;
        }
        return -1;
    }
};

int main() {
    int	row1[6] = { -1, -1, 21, -1, 7, -1 };
    int	row2[6] = { -1, 25, -1, -1, -1, -1 };
    int	row3[6] = { -1, -1, -1, -1, 3, -1 };
    int	row4[6] = { -1, -1, -1, 8, 28, 6 };
    int	row5[6] = { -1, -1, 0, -1, -1, -1 };
    int **board = new int*[5];
    board[0] = row1; board[1] = row2; board[2] = row3; board[3] = row4; board[4] = row5;

    Solution so;
    cout << so.minStepsForSnakeAndLadder(board, 5, 6) << endl;
    return 0;
}