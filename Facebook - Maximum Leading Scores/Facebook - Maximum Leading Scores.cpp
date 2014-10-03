//  Given an array of positive integers that represents possible points a team could score in an individual play.Now there are two teams play against each other.Their final scores are S and S'. How would you compute the maximum number of times the team that leads could have changed?
//  For example, if S = 10 and S'=6. The lead could have changed 4 times:
//  Team 1 scores 2, then Team 2 scores 3 (lead change);
//  Team 1 scores 2 (lead change), Team 2 score 0 (no lead change);
//  Team 1 scores 0, Team 2 scores 3 (lead change);
//  Team 1 scores 3, Team 2 scores 0 (lead change);
//  Team 1 scores 3, Team 2 scores 0 (no lead change).
//  http://www.careercup.com/question?id=5659765149532160

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int leadChanges(int *scoreArr, int n, int S1, int S2)
{
    if ((S1 == 0 && S2 == 0) || n == 0) return 0;
    if (S1 == 0 || S2 == 0) return 1;

    sort(scoreArr, scoreArr + n);

    char* buffer = new char[sizeof(int)*(S1 + 1)*(S2 + 1) + sizeof(int*)*(S1 + 1)];
    //must zero this array because scoreArr main contain 0 score. In this case, the code line in label "ATTENTION" must have zero result.
    memset(buffer, 0, sizeof(int)*(S1 + 1)*(S2 + 1) + sizeof(int*)*(S1 + 1)); 
    int **resultArr = (int**)(buffer + sizeof(int)*(S1 + 1)*(S2 + 1));
    for (int i = 0; i <= S1; ++i)
        resultArr[i] = (int*)(buffer + i*sizeof(int)*(S2 + 1));

    int prevScore1 = 0, prevScore2 = 0, curTransform = 0, maxTransform = 0;
    for (int i = 0; i <= S1; ++i){
        for (int j = 0; j <= S2; ++j){
            maxTransform = 0;

            for (int k1 = 0; k1 < n; ++k1){
                if (i < scoreArr[k1]) break;
                prevScore1 = i - scoreArr[k1];

                for (int k2 = 0; k2 < n; ++k2){
                    if (j < scoreArr[k2]) break;
                    prevScore2 = j - scoreArr[k2];

                    curTransform = resultArr[prevScore1][prevScore2]; //ATTENTION
                    if ((i > j && prevScore1 <= prevScore2)
                        || (i < j && prevScore1 >= prevScore2))
                        ++curTransform;

                    if (curTransform > maxTransform) maxTransform = curTransform;
                }
            }

            resultArr[i][j] = maxTransform;
        }
    }

    int result = resultArr[S1][S2];
    delete[] buffer;
    return result;
}

int main() {
    int score[] = { 0, 2, 3 };
    int S1 = 10, S2 = 6;

    cout << leadChanges(score, sizeof(score) / sizeof(int), S1, S2) << endl;
    return 0;
}