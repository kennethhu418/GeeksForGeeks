//  Given an integer array, find a subarray with sum closest to zero.Return the indexes 
//  of the first number and last number.
//  Example:
//  Given[-3, 1, 1, -3, 5], return[0, 2], [1, 3], [1, 1], [2, 2] or[0, 4]

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    typedef struct __Node {
        int     sum;
        int     index;
        __Node(int sum = 0, int index = 0) : sum(sum), index(index) {}
    }Node;

    static bool compareNode(const Node &node1, const Node &node2) {
        if (node1.sum == node2.sum) return node1.index < node2.index;
        return node1.sum < node2.sum;
    }

public:
    /**
    * @param nums: A list of integers
    * @return: A list of integers includes the index of the first number
    *          and the index of the last number
    */
    vector<int> subarraySumClosest(const vector<int> &nums){
        int n = nums.size();
        if (n == 0) return vector<int>();

        Node node;
        int curSum = 0;
        vector<Node>	sumArr;
        for (int i = 0; i < n; ++i) {
            node.sum = curSum;
            node.index = i;
            sumArr.push_back(node);
            curSum += nums[i];
        }
        sumArr.push_back(Node(curSum, n));

        sort(sumArr.begin(), sumArr.end(), compareNode);

        int curDiff = 0, minDiff = INT_MAX, minDiffStart = 0, curPos = 0;
        while (curPos < n - 1) {
            curDiff = abs(sumArr[curPos].sum - sumArr[curPos + 1].sum);
            if (curDiff < minDiff) {
                minDiff = curDiff;
                minDiffStart = curPos;
            }
            ++curPos;
        }

        vector<int>	result(2, -1);
        if (sumArr[minDiffStart].index > sumArr[minDiffStart + 1].index) {
            result[0] = sumArr[minDiffStart + 1].index;
            result[1] = sumArr[minDiffStart].index - 1;
        }
        else {
            result[0] = sumArr[minDiffStart].index;
            result[1] = sumArr[minDiffStart + 1].index - 1;
        }
        return result;
    }
};

int main() {
    int arr[] = { -3, 1, 1, -3, 5 };
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    Solution so;

    vector<int> result = so.subarraySumClosest(nums);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}
