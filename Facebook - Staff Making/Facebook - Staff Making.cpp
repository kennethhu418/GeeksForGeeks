//  You want to create a staff to use in your martial arts training, and it has to meet some specific requirements.
//  
//  1. You want it to be composed of two smaller staves of equal length so that you can either use it as a single staff or as two smaller ones.
//  
//  2. You want the full sized staff's center of gravity to be exactly in the middle of the staff. 
//  
//  You have a very, very long branch from which you can cut the pieces for your staff.The mass of the branch varies significantly throughout it, 
//  so you use just any two pieces of the same length.Given a description of the mass throughout the branch, determine the longest staff you can 
//  make, then return three integers on a single line, the first two indicating the first index of each half - staff, and the third indicating the length 
//  of each half - staff.
//  
//  The input will be given on a single line as a string of digits[1 - 9], each digit representing the mass of a section of the branch.All sections are 
//  the same size and the maximum length of the string is 500. Here is an example :
//  
//  41111921111119
//  11119 11119
//  
//  If the indicated sections are cut from the branch they will satisfy your requirements.They are both the same length, and they can be put 
//  together as either 9111111119 or 1111991111, both of which have a center of gravity exactly in the center of the staff.
//  
//  
//  Center of gravity can be determined by taking a weighted average of the mass of each section of the staff.Given the following distances 
//  and masses :
//  Distance : 12345678
//  Mass : 22241211
//  
//  Sum of the mass of each section : 2 + 2 + 2 + 4 + 1 + 2 + 1 + 1 = 15
//  Weighted sum of the masses :
//  2 * 1 + 2 * 2 + 2 * 3 + 4 * 4 + 1 * 5 + 2 * 6 + 1 * 7 + 1 * 8 = 60
//  Weighted sum / regular sum = 60 / 15 = 4
//  
//  This means that the center of mass is in section 4 of the staff. However, if we wanted to use this staff the center of gravity would need to 
//  be(8 + 1) / 2 = 4.5.
//  
//  Here is another example :
//  
//  131251141231
//  ---- ----
//  
//  If we take the sections indicated we get 1312 and 1231. By reversing the first one and putting them together we get 21311231
//  
//  Sum of the mass of each section : 2 + 1 + 3 + 1 + 1 + 2 + 3 + 1 = 14
//  Weight sum of the masses :
//  2 * 1 + 1 * 2 + 3 * 3 + 1 * 4 + 1 * 5 + 2 * 6 + 3 * 7 + 1 * 8 = 63
//  Weighted sum / regular sum = 63 / 14 = 4.5
//  
//  This puts the center of mass exactly in the center of the staff, for a perfectly balanced staff.
//  There isn't a longer staff that can be made from this, so the answer to this problem is 
//  
//  0 8 4
//  
//  Because the half - staves begin at indices 0 and 8 (in that order) and each is of length 4.
//
//  http://www.careercup.com/question?id=5745799489126400

//  Here is my O(n^2) solution:
//  Basic idea is:
//  Create a matrix that stores the centre of gravity for all i<=j. cg(i,j) = weighted sum from i to j. Not that c(i,j) is a number between [0, (j-i)]. 
//  Now, start iterating over the matrix, while inserting c(i,j) in the set and check if the set already has c(i,j) or (j-i)-c(i,j) (inverted staff section) 
//  and update the max_length seen so far (=j-i). This is because you can contruct final staff with two sections [i,j] and [p,q] if j-i == q-p, c(i,j) == c(p,q) or p - q - c(p,q). 
//  Time complexity : O(n ^ 2) constructing and traversing cg matrix
//  Space complexity : O(n ^ 2) for matrix and Set

#include <iostream>
#include <unordered_map>
using namespace std;

const unsigned int MAX_SEGMENTS = 51;
static int weightedSumArr[MAX_SEGMENTS][MAX_SEGMENTS];
static int sumArr[MAX_SEGMENTS][MAX_SEGMENTS];

bool getMaxLengthStaff(int *arr, int n, int &start1, int &start2, int &maxlenRes)
{
    int maxLen = (n >> 1);

    //Initialize sum arr
    for (int i = 0; i < n; ++i) sumArr[i][1] = arr[i];
    for (int len = 2; len <= n; ++len){
        for (int i = 0; i <= n - len; ++i)
            sumArr[i][len] = arr[i] + sumArr[i + 1][len - 1];
    }

    //Initialize weightedSumArr and gravityMap
    unordered_map<double, int> *gravityMap = new unordered_map<double, int>[maxLen + 1];
    double gravity = 0;

    for (int i = 0; i < n; ++i) weightedSumArr[i][1] = arr[i];
    for (int len = 2; len <= maxLen; ++len){
        for (int i = 0; i <= n - len; ++i) {
            weightedSumArr[i][len] = arr[i] + weightedSumArr[i + 1][len - 1] + sumArr[i + 1][len - 1];
            gravity = weightedSumArr[i][len] / (double)sumArr[i][len];
            //We record the largest index with gravity of len into the map
            //By doing this, we can easily check whether there is non-overlapping
            //range with len having the same or equally mirrored gravity if we 
            //perform the check from low index to high index later.
            if (gravityMap[len].find(gravity) == gravityMap[len].end()
                || gravityMap[len][gravity] < i)
                gravityMap[len][gravity] = i;
        }
    }

    //Now check each len range from longest len to shortest len
    for (int len = maxLen; len > 0; --len){
        for (int i = 0; i <= n - len; ++i){
            gravity = weightedSumArr[i][len] / (double)sumArr[i][len];

            // There are three requirements for two segments can be concated to the satisfied staff:
            // (1) the two segments should be non-overlapped
            // (2) the two segments should have the same weight
            // (3) the gravity of the two segements should be the same or equally mirrored.

            // first check same gravity
            if (gravityMap[len].find(gravity) != gravityMap[len].end()
                && gravityMap[len][gravity] >= i + len  //the two segments should be non-overlapped
                && sumArr[i][len] == sumArr[gravityMap[len][gravity]][len]){  //the weight of the two segements should be the same
                start1 = i; start2 = gravityMap[len][gravity]; maxlenRes = len;
                delete[] gravityMap;
                return true;
            }

            // second check equally mirrored gravity
            if (gravityMap[len].find(len + 1 - gravity) != gravityMap[len].end()
                && gravityMap[len][len + 1 - gravity] >= i + len
                && sumArr[i][len] == sumArr[gravityMap[len][len + 1 - gravity]][len]){
                start1 = i; start2 = gravityMap[len][len + 1 - gravity]; maxlenRes = len;
                delete[] gravityMap;
                return true;
            }
        }
    }

    delete[] gravityMap;
    return false;
}

int main() {
    int arr1[] = { 1, 3, 1, 2, 5, 1, 1, 4, 1, 2, 3, 1 };
    int n = sizeof(arr1) / sizeof(int);
    int start1 = 0, start2 = 0, len = 0;
    if (!getMaxLengthStaff(arr1, n, start1, start2, len))
        cout << "No solution1!" << endl;
    else
        cout << "Solution1: " << start1 << " " << start2 << " " << len << endl;

    int arr2[] = { 4, 1, 1, 1, 1, 9, 2, 1, 1, 1, 1, 1, 1, 9 };
    n = sizeof(arr2) / sizeof(int);
    if (!getMaxLengthStaff(arr2, n, start1, start2, len))
        cout << "No solution2!" << endl;
    else
        cout << "Solution2: " << start1 << " " << start2 << " " << len << endl;
    return 0;
}