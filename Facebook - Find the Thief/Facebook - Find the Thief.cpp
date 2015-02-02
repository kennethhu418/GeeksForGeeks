// ��С͵���⣬��n�����䣬����һ��������С͵��
// �������ǿ��Դ�һ��������ſ�С͵�ڲ������棬����С͵������߻����ұߵ�
// �����ߡ����ڸ���һ�����ŵ�sequence����������sequence�ܲ��ܱ�֤�ҵ�С͵��
// ���磺���ֻ������������ô����򿪷����sequence��{ 1, 1 }��ôһ�����ҵ�С͵��
// ��Ϊ���С͵���м���ô��һ��ͻᱻ�ҵ������С͵��������ô�ڶ���һ������
// ���м�Ҳ�ᱻ�ҵ�.

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