// 找小偷问题，有n个房间，其中一个房间有小偷。
// 早上我们可以打开一个房间的门看小偷在不在里面，晚上小偷会向左边或者右边的
// 房间走。现在给你一个开门的sequence，你输出这个sequence能不能保证找到小偷。
// 比如：如果只有三个房间那么如果打开房间的sequence是{ 1, 1 }那么一定会找到小偷。
// 因为如果小偷在中间那么第一天就会被找到，如果小偷在两边那么第二天一定回来
// 到中间也会被找到.

#include <iostream>
#include <vector>
using namespace std;

bool canFindThief(const int *sequenceArr, int sequenceSize, int doorCount) {
    if (sequenceSize == 0)
        return false;
    if (doorCount < 2)
        return true;

    vector<bool>    v1(doorCount, true), v2(doorCount, true);
    vector<bool>    *prevResult = &v1, *curResult = &v2;
    for (int i = 0; i < doorCount; ++i)
        prevResult->at(i) = false;

    for (int i = sequenceSize - 1; i >= 0; --i) {
        for (int j = 0; j < doorCount; ++j) {
            if (j == sequenceArr[i]) {
                curResult->at(j) = true;
                continue;
            }
            if (j < doorCount - 1 && prevResult->at(j + 1) == false) {
                curResult->at(j) = false;
                continue;
            }        
            if (j > 0 && prevResult->at(j - 1) == false) {
                curResult->at(j) = false;
                continue;
            }
            curResult->at(j) = true;
        }
        swap(curResult, prevResult);
    }

    for (int i = 0; i < doorCount; ++i) {
        if (prevResult->at(i) == false)
            return false;
    }
    return true;
}

int main() {
    int     n = 3;
    int     seqArr[] = {1, 1};
    cout << canFindThief(seqArr, sizeof(seqArr) / sizeof(seqArr[0]), n) << endl;
    return 0;
}