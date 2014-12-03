// Given an array of numbers, arrange them in a way that yields the largest value.
// For example, if the given numbers are{ 54, 546, 548, 60 }, the arrangement 6054854654 gives the largest value.
// And if the given numbers are{ 1, 34, 3, 98, 9, 76, 45, 4 }, then the arrangement 998764543431 gives the largest value.


//Solution:
// A simple solution that comes to our mind is to sort all numbers in descending order, but simply sorting doesn¡¯t work. 
// For example, 548 is greater than 60, but in output 60 comes before 548. As a second example, 98 is greater than 9, but 9 comes before 98 in output.
     
// So how do we go about it ? The idea is to use any comparison based sorting algorithm.In the used sorting algorithm, instead of using the default comparison, 
// write a comparison function myCompare() and use it to sort numbers. Given two numbers X and Y, how should myCompare() decide which number to put 
// first ¨C we compare two numbers XY(Y appended at the end of X) and YX(X appended at the end of Y).If XY is larger, then X should come before Y in output, 
// else Y should come before.For example, let X and Y be 542 and 60. To compare X and Y, we compare 54260 and 60542. 
// Since 60542 is greater than 54260, we put Y first.

// Now let us prove the proposed method is valid.
// We use proof by contradiction here.
// Since we take comparison based method to sort the array, the only thing that we need to prove is that the proposed relationship has transitive properties.That is, 
// if a1a2 > a2a1 and a2a3 > a3a2, then a1a3 > a3a1.
// 
// Now let us assume that the transitive property does not hold.That is a1a3 < a3a1, let us see what will happen.
// 
// One thing that we should recognize is that if ab < ba, then acb < bca.This is because by inserting number c between a and b, the length relationship and the 
// digit small / larger relationship between the two sides of the inequality do not change.For example, (583)(59) < (59)(583), then(583)(742)(59) < (59) (742) (583).
// 
// Now let¡¯s continue to see what happens if a1a3 < a3a1.
// a1a3 < a3a1 = >  a1a2a3 < a3a2a1 = >  a1a3a2 < a1a2a3 < a3a2a1 = >  a1a3a2 < a1a2a3 < a3a2a1 < a2a3a1
// Thus, we get a1a3a2 < a2a3a1.Removing the common part in middle, we get a1a2 < a2a1, this contradicts with the fact that a1a2 > a2a1.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// A comparison function which is used by sort() in printLargest()
int myCompare(string X, string Y)
{
    string XY = X.append(Y);

    string YX = Y.append(X);

    // Now see which of the two formed numbers is greater
    return XY.compare(YX) > 0 ? 1 : 0;
}

void printLargest(vector<string> arr)
{
    sort(arr.begin(), arr.end(), myCompare);

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i];
}

int main()
{
    vector<string> arr;

    //output should be 6054854654
    arr.push_back("54");
    arr.push_back("546");
    arr.push_back("548");
    arr.push_back("60");
    printLargest(arr);
    return 0;
}