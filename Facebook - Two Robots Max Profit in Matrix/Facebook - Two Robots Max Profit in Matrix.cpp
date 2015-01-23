//һ��m*n��matrixÿ�������Ϸ�һ��������Ǯ���������߹�һ�����ӾͰ�Ǯ���ߣ�����
//�Ͻ��ߵ����½ǣ�ֻ�����������ߡ�����������������õ���Ǯ���ܺ����ֵ��

// Author: Kenneth Hu
// Version: created @ Jan 23 2015
//

/*****************************************************************************
�㷨˵�� - ��άDynamic Programming

���ȴ���άDP����
result[x1][y1][x2][y2] ��ʾ������1��(x1, y1), ������2��(x2, y2)��
�Ӵ����������½Ǹ���������Ǯ���ܺ����ֵ

��ô
(1) If x1 == x2 && y1 == y2(��������ͬһ�����)
result[x1][y1][x2][y2] = matrix[x1][y1] + max(result[x1 + 1][y1][x2 + 1][y2],
result[x1][y1 + 1][x2][y2 + 1], result[x1 + 1][y1][x2][y2 + 1],
result[x1][y1 + 1][x2 + 1][y2]);

(2) else
result[x1][y1][x2][y2] = matrix[x1][y1] + matrix[x2][y2] + max(result[x1 + 1][y1][x2 + 1][y2],
result[x1][y1 + 1][x2][y2 + 1], result[x1 + 1][y1][x2][y2 + 1],
result[x1][y1 + 1][x2 + 1][y2]);

���result[0][0][0][0]��Ϊ����

ʵ���п��Խ�����(x, y) encode Ϊ x*width + y, �Ӷ�ת��Ϊ�˶�άDP����
****************************************************************************/

#include <iostream>
#include <assert.h>
using namespace std;

#define MAX_MATRIX_WIDTH      6
#define MAX_MATRIX_HEIGHT     6

class Solution{
public:
    int calculateMaxProfit(const unsigned int **matrix, int width, int height) {
        assert(width <= MAX_MATRIX_WIDTH);
        assert(height <= MAX_MATRIX_HEIGHT);
        if (width == 0 || height == 0)
            return 0;

        mHeight = height;  mWidth = width;
        static unsigned int resultArr[MAX_MATRIX_HEIGHT*MAX_MATRIX_WIDTH][MAX_MATRIX_HEIGHT*MAX_MATRIX_WIDTH];
        unsigned int nextStepMaxProfit = 0;
        int nextRobot1Pos = 0, nextRobot2Pos = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;

        for (int robot1Pos = width * height - 1; robot1Pos >= 0; --robot1Pos) {
            for (int robot2Pos = width * height - 1; robot2Pos >= 0; --robot2Pos){
                translateToMatrixPos(robot1Pos, x1, y1);
                translateToMatrixPos(robot2Pos, x2, y2);
                if (robot1Pos == robot2Pos)
                    resultArr[robot1Pos][robot2Pos] = matrix[x1][y1];
                else
                    resultArr[robot1Pos][robot2Pos] = matrix[x1][y1] + matrix[x2][y2];

                nextStepMaxProfit = 0;
                for (int i = 0; i < 2; ++i) {
                    for (int j = 0; j < 2; ++j) {
                        nextRobot1Pos = getNext(robot1Pos, i);
                        nextRobot2Pos = getNext(robot2Pos, j);
                        if (nextRobot1Pos >= 0 && nextRobot2Pos >= 0 && resultArr[nextRobot1Pos][nextRobot2Pos] > nextStepMaxProfit)
                            nextStepMaxProfit = resultArr[nextRobot1Pos][nextRobot2Pos];
                    }
                }

                resultArr[robot1Pos][robot2Pos] += nextStepMaxProfit;
            }
        }

        return resultArr[0][0];
    }

private:
    int    mHeight;
    int    mWidth;
    int    getNext(int curPos, bool goDown = true) {
        int x = 0, y = 0, nextPos = 0;
        translateToMatrixPos(curPos, x, y);
        if (goDown) {
            if (x + 1 >= mHeight) return -1;
            return (x + 1) * mWidth + y;
        }
        if (y + 1 >= mWidth) return -1;
        return curPos + 1;
    }

    void translateToMatrixPos(int pos, int &x, int &y) {
        x = pos / mWidth;
        y = pos % mWidth;
    }
};


int main() {
    const unsigned int MATRIX_SIZE = 3;
    const unsigned int r1[MATRIX_SIZE] = { 0, 0, 2 };
    const unsigned int r2[MATRIX_SIZE] = { 0, 3, 2 };
    const unsigned int r3[MATRIX_SIZE] = { 0, 1, 0 };
    const unsigned int *matrix[MATRIX_SIZE] = { r1, r2, r3 };
    Solution so;

    cout << "Max Profit for two robots is " << so.calculateMaxProfit(matrix, MATRIX_SIZE, MATRIX_SIZE) << endl;
    return 0;
}
