// How would you break people into two groups such that no group contains 
// a pair of people who hate each other ?

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <assert.h>
using namespace std;

//If cannot be splitted into to groups, return empty vector
vector<vector<int>> groupPeople(bool ** hateMatrix, int n) {
    vector<vector<int>> resultArr;
    if (n == 0) return resultArr;

    int *labelArr = new int[n];
    //0: not visited 1: labeled as group1 2: labeled as group2 -1: visited but has not been decided which group
    memset(labelArr, 0, sizeof(int) * n);
    queue<int> visitQ;

    int curP = 0, neighborGroup = 0;
    for (int i = 0; i < n; ++i) {
        if (labelArr[i] != 0) {
            assert(labelArr[i] == 1 || labelArr[i] == 2);
            continue;
        }

        visitQ.push(i); labelArr[i] = -1;
        while (!visitQ.empty()) {
            curP = visitQ.front(); visitQ.pop();
            assert(labelArr[curP] == -1);

            neighborGroup = 0;
            for (int j = 0; j < n; ++j) {
                if (hateMatrix[curP][j] == false) continue;

                if (labelArr[j] == 0) {
                    labelArr[j] = -1; visitQ.push(j);
                }
                else if (labelArr[j] > 0) {
                    if (neighborGroup == 0)
                        neighborGroup = labelArr[j];
                    else if (neighborGroup != labelArr[j]){
                        delete[] labelArr;
                        return resultArr;
                    }
                }
            }

            if (neighborGroup < 2) labelArr[curP] = 2;
            else labelArr[curP] = 1;        
        }    
    }

    resultArr.resize(2);
    for (int i = 0; i < n; ++i){
        if (labelArr[i] == 1) resultArr[0].push_back(i);
        else resultArr[1].push_back(i);
    }
    delete[] labelArr;
    return resultArr;
}

int main()
{
    bool b0[] = { 0, 0, 0, 0, 0, 0, 1, 0 };
    bool b1[] = { 0, 0, 0, 0, 0, 0, 0, 1 };
    bool b2[] = { 0, 0, 0, 0, 0, 1, 0, 0 };
    bool b3[] = { 0, 0, 0, 0, 0, 1, 0, 0 };
    bool b4[] = { 0, 0, 0, 0, 0, 0, 1, 1 };
    bool b5[] = { 0, 0, 1, 1, 0, 0, 0, 0 };
    bool b6[] = { 1, 0, 0, 0, 1, 0, 0, 0 };
    bool b7[] = { 0, 1, 0, 0, 1, 0, 0, 0 };
    bool *hateMatrix[] = {b0, b1, b2, b3, b4, b5, b6, b7};

    vector<vector<int>> resultArr = groupPeople(hateMatrix, 8);
    assert(resultArr.size() == 2);
    cout << "Group 1:  ";
    for (int i = 0; i < resultArr[0].size(); ++i) cout << resultArr[0][i] << " ";
    cout << endl;
    cout << "Group 2:  ";
    for (int i = 0; i < resultArr[1].size(); ++i) cout << resultArr[1][i] << " ";
    cout << endl;
	return 0;
}

