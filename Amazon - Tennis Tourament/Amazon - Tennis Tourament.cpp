// In a tennis tournament of N players every player plays with every other player.
// The following condition always hold -
// If player P1 has won the match with P2 and player P2 has won from P3, then Player P1 
// has also defeated P3.
// Find winner of tournament in O(N) time and O(1) space.Find rank of players in O(NlogN) time.

#include <iostream>
using namespace std;

#define PLAYER_COUNT 7

class Solution
{
public:
    int getWinner(bool winMatrix[][PLAYER_COUNT]) {
        if (PLAYER_COUNT == 0) return -1;
        if (PLAYER_COUNT == 1) return 0;
        int winner = 0;
        for (int i = 1; i < PLAYER_COUNT; ++i) {
            if (winMatrix[i][winner])
                winner = i;
        }
        return winner;
    }

    void rank(bool winMatrix[][PLAYER_COUNT], int rankArr[PLAYER_COUNT]) {
        if (PLAYER_COUNT == 1) rankArr[0] = 0;
        if (PLAYER_COUNT < 2) return;

        for (int i = 0; i < PLAYER_COUNT; ++i)
            rankArr[i] = i;
        
        int *buffer = new int[PLAYER_COUNT];
        rank(winMatrix, 0, PLAYER_COUNT - 1, rankArr, buffer);
        delete[] buffer;   
    }

private:
    void rank(bool winMatrix[][PLAYER_COUNT], int start, int end, int *rankArr, int *bufferArr) {
        if (start >= end) return;
        int mid = ((start + end) >> 1);
        rank(winMatrix, start, mid, rankArr, bufferArr);
        rank(winMatrix, mid + 1, end, rankArr, bufferArr);
        
        int lstart = start, lend = mid, rstart = mid + 1, rend = end, pos = 0;
        int lw = 0, rw = 0;
        while (lstart <= lend && rstart <= rend) {
            lw = rankArr[lstart]; rw = rankArr[rstart];
            if (winMatrix[lw][rw]) {
                bufferArr[pos++] = lw; ++lstart;
            }
            else {
                bufferArr[pos++] = rw; ++rstart;
            }
        }

        while (lstart <= lend) bufferArr[pos++] = rankArr[lstart++];
        while (rstart <= rend) bufferArr[pos++] = rankArr[rstart++];
        for (int i = 0; i < pos; ++i)
            rankArr[start + i] = bufferArr[i];    
    }
};





int main()
{
    // The rank is 1 5 0 6 2 3 4
    bool winMatrix[][PLAYER_COUNT] = {
       //0  1  2  3  4  5  6
        {0, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 0}
    };

    Solution so;
    int rankArr[PLAYER_COUNT];
    
    cout << "The winner is " << so.getWinner(winMatrix) << endl;
    cout << "The rank is :";
    so.rank(winMatrix, rankArr);
    for (int i = 0; i < PLAYER_COUNT; ++i)
        cout << rankArr[i] << " ";
    cout << endl;

    return 0;
}