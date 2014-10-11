// Given a matrix consisting of 0's and 1's, find the largest connected component consisting of 1's.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int DIRECT_SIZE = 8;
const int directX[DIRECT_SIZE] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int directY[DIRECT_SIZE] = { -1, 0, 1, -1, 1, -1, 0, 1 };

class Solution
{
public:
    int largestComponent(vector<vector<char>> &matrix)
    {
        int m = matrix.size(); if (m == 0) return 0;
        int n = matrix[0].size(); if (n == 0) return 0;

        int maxArea = 0, curArea = 0;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] != '1') continue;
                curArea = calculateComponentSize(matrix, i, j);
                if (curArea > maxArea) maxArea = curArea;
            }
        }

        ResumeMatrix(matrix);
        return maxArea;
    }

private:
    int calculateComponentSize(vector<vector<char>> &matrix, int startX, int startY){
        int m = matrix.size(), n = matrix[0].size();
        queue<int> qX, qY;
        qX.push(startX); qY.push(startY); markVisited(matrix[startX][startY]);
        int count = 0, curX = 0, curY = 0;
        while (!qX.empty()){
            startX = qX.front(); startY = qY.front(); qX.pop(); qY.pop();
            ++count;
            for (int i = 0; i < DIRECT_SIZE; ++i){
                curX = startX + directX[i]; curY = startY + directY[i];
                if (curX < 0 || curX >= m || curY < 0 || curY >= n || matrix[curX][curY] != '1')
                    continue;
                markVisited(matrix[curX][curY]);
                qX.push(curX); qY.push(curY);
            }
        }
        return count;
    }

    void markVisited(char &c){
        c = 'v';
    }

    void ResumeMatrix(vector<vector<char>> &matrix){
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] == 'v') matrix[i][j] = '1';
            }
        }
    }
};

int main() {
    char matrixArr[4][5] = {
        { '0', '0', '0', '1', '0' },
        { '0', '1', '0', '1', '1' },
        { '1', '1', '0', '1', '0' },
        { '1', '0', '0', '1', '0' }
    };
    vector<char> row0(&matrixArr[0][0], (&matrixArr[0][0]) + 5);
    vector<char> row1(&matrixArr[1][0], (&matrixArr[1][0]) + 5);
    vector<char> row2(&matrixArr[2][0], (&matrixArr[2][0]) + 5);
    vector<char> row3(&matrixArr[3][0], (&matrixArr[3][0]) + 5);
    vector<vector<char>> matrix;
    matrix.push_back(row0); matrix.push_back(row1);
    matrix.push_back(row2); matrix.push_back(row3);

    Solution so;
    cout << so.largestComponent(matrix) << endl;
    return 0;
}