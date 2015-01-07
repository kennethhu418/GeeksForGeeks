// find a intersection to build office so that the sum of all employees¡¯
// commute distances is minimum. £¨the map is represented as a m*n grid, you
// are given each employee¡¯s house's coordination, they can only move in up-down and
// left-right directions£©
// Notice that the building cannot be built on an employee's house, and when one employee
// go to work, he cannot pass through another employee's house.

#include <iostream>
#include <ctime>
#include <cmath>
#include <queue>
using namespace std;

#define M 7
#define N 7
#define DIRECTIONS 4

static const int directionX[DIRECTIONS] = { -1, 1, 0, 0 };
static const int directionY[DIRECTIONS] = { 0, 0, 1, -1 };

typedef struct __Point {
    int    x;
    int    y;
    int    dist;
    __Point(int x = 0, int y = 0, int dist = 0) : x(x), y(y), dist(dist){}
}Point;

class Solution
{
private:
    int distMatrix[M][N];
    int visitMatrix[M][N];

    void ResetArray(int matrix[M][N]) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j)
                matrix[i][j] = 0;
        }
    }

    void fillDistantMatrix(char matrix[M][N], int startX, int startY) {
        queue<Point> ptQ;
        ptQ.push(Point(startX, startY));
        visitMatrix[startX][startY] = 1;

        Point pt, nextPt;
        while (!ptQ.empty()) {
            pt = ptQ.front(); ptQ.pop();
            distMatrix[pt.x][pt.y] += pt.dist;

            for (int i = 0; i < DIRECTIONS; ++i) {
                nextPt.x = pt.x + directionX[i];
                nextPt.y = pt.y + directionY[i];
                nextPt.dist = pt.dist + 1;
                if (nextPt.x >= 0 && nextPt.y >= 0
                    && nextPt.x < M && nextPt.y < N
                    && matrix[nextPt.x][nextPt.y] == 'O'
                    && !visitMatrix[nextPt.x][nextPt.y]) {
                    visitMatrix[nextPt.x][nextPt.y] = 1;
                    ptQ.push(nextPt);
                }
            }
        }
    }


public:
    Point getBuildingLocation(char matrix[M][N]) {
        Point result(-1, -1, 0);

        ResetArray(distMatrix);

        int employeeCount = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == 'O') continue;
                ++employeeCount;
                ResetArray(visitMatrix);
                fillDistantMatrix(matrix, i, j);
            }
        }

        int minDist = INT_MAX;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == 'E') continue;
                if (minDist > distMatrix[i][j]) {
                    minDist = distMatrix[i][j];
                    result.x = i; result.y = j;
                    result.dist = minDist / (double)employeeCount + 0.5;
                }
            }
        }
        return result;
    }

};

void OutputMatrix(char matrix[M][N]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void generateMatrix(char matrix[M][N], int cnt = 0) {
    bool visitArr[M][N];
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            visitArr[i][j] = false;
            matrix[i][j] = 'O';
        }
    }

    int x = 0, y = 0;
    while (cnt) {
        x = rand() % M;
        y = rand() % N;
        if (visitArr[x][y]) continue;
        --cnt;
        matrix[x][y] = 'E';
    }
}

int main() {
    char matrix[M][N];
    int employeeCount;
    char buffer[100];
    Point result;
    Solution so;
    int MAX_EMPLOYEE = (M * N / 5);

    srand(time(NULL));

    cout << "Press Enter to procceed next test." << endl;
    while (cin.getline(buffer, 100)) {
        for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = 0;

        employeeCount = 1 + rand() % MAX_EMPLOYEE;
        generateMatrix(matrix, employeeCount);

        cout << "The distribution is :" << endl;
        OutputMatrix(matrix);
        cout << endl;

        cout << "The building is build in:" << endl;
        result = so.getBuildingLocation(matrix);
        if (result.x < 0)
            cout << "No building can be built." << endl;
        else {
            matrix[result.x][result.y] = 'X';
            OutputMatrix(matrix);
            cout << endl << "The minimum average distance is " << result.dist << endl;
        }
        cout << endl;
        cout << "Input Enter to procceed next test." << endl;
    }
    return 0;
}