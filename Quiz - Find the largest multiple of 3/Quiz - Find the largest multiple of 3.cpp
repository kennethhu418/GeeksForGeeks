// Quiz - Find the largest multiple of 3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//Given an array of non - negative integers.Find the largest multiple of 3 that can be formed from array elements.
//
//For example, if the input array is{ 8, 1, 9 }, the output should be “9 8 1″, and if the input array is{ 8, 1, 7, 6, 0 }, output should be “8 7 6 0″.

//Here is my idea :

//[Background Knowledge]
//1) A number is multiple of 3 if and only if the sum of digits of number is multiple of 3. For example, let us consider 8760, it is a multiple of 3 because sum of digits is 8 + 7 + 6 + 0 = 21, which is a multiple of 3.
//
//2) If a number is multiple of 3, then all permutations of it are also multiple of 3. This is the extension of 1).For example, since 6078 is a multiple of 3, the numbers 8760, 7608, 7068, …..are also multiples of 3.
//
//3) We get the same remainder when we divide the number and sum of digits of the number.For example, if divide number 151 and sum of it digits 7, by 3, we get the same remainder 1.
//
//Let us consider a 3 digit number n to prove this fact.Let the first, second and third digits of n be ‘a’, ‘b’ and ‘c’ respectively.n can be written as
//n = 100 * a + 10 * b + c
//= (99 + 1)*a + (9 + 1)*b + c
//= 99 * a + 9 * b + a + b + c
//
//Since 99 * a + 9 * b can be dividided by 3, the remainder of n is the same with that of(a + b + c)
//
//[Algorithm]
//1. Split the original array ARR into three sub arrays ARR0, ARR1 and ARR2.ARR0 stores the numbers that can be divided by 3, ARR1 stores the numbers with remainder 1 when dividing by 3 and ARR2 stores the numbers with remainder 2 when dividing by 3
//
//2. Sum all the digits of all the numbers in the original array.Assume the sum is S.
//
//3. Three cases arise :
//……3.1 S is divisible by 3. Based on Knowledge 3), this means the combination of all numbers in the original array can be divisible by 3. So directly go to step 4.
//
//……3.2 The sum of digits produces remainder 1 when divided by 3.
//This means we should remove a remainder 1 from the original array numbers.This can be achieved by removing the smallest number ARR1[0] from ARR1 or the two smallest numbers ARR2[0] and ARR2[1] from ARR2.If the digits count of ARR1[0] is larger than that of the concatenate of ARR2[0] and ARR2[1], we remove ARR2[0] and ARR2[1]; If the digits count of the concatenate of ARR2[0] and ARR2[1] is larger than that of ARR1[0], we remove ARR1[0].If their digits count are the same, we remove the smaller one of(ARR1[0]) and(max of concatenate of ARR2[0] and ARR2[1]).
//
//……3.3 The sum of digits produces remainder 2 when divided by 3.
//This means we should remove a remainder 2 from the original array numbers.This can be achieved by removing the smallest number ARR2[0] from ARR2 or the two smallest numbers ARR1[0] and ARR1[1] from ARR1.If the digits count of ARR2[0] is larger than that of the concatenate of ARR1[0] and ARR1[1], we remove ARR1[0] and ARR1[1]; If the digits count of the concatenate of ARR1[0] and ARR1[1] is larger than that of ARR2[0], we remove ARR2[0].If their digits count are the same, we remove the smaller one of(ARR2[0]) and(max of concatenate of ARR1[0] and ARR1[1]).
//
//4. Finally sort all the remaining numbers in the array by their MSDs(most significant digits) decreasingly and concatenate them together by order.If two numbers' MSDs are the same, sort them by the larger result of concatenating them.
//
//For example, assume there is three remaining numbers 5411, 876 and 87. 876 and 87 should be "larger" in sorting because 8 is greater than 5. And 87 should be "larger" than 876 because they have the same MSBs(i.e, 87), and when concating them together, 87876 is greater than 87687.

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

