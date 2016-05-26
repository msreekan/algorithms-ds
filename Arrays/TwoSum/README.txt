******************************************************************************
Problem Statement: Two Sum
******************************************************************************
Given an array of integers, return indices of the two numbers such that they 
add up to a specific target. You may assume that each input would have exactly
one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].

******************************************************************************
URL : https://leetcode.com/problems/two-sum/
******************************************************************************

******************************************************************************
Notes: 
******************************************************************************
Time Complexity : O(nLog(n))
Space Complexity : O(n)

Algorithm sorts the array. Scans it from both the ends and narrows down on the
pair of integers which adds up to the target.

Allows compile time options for heap and quick sort. Also provides an alternate
O(n Log(n)) algorithm employing binary search.

******************************************************************************