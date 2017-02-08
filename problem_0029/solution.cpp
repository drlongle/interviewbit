/*
3 Sum

Given an array S of n integers, find three integers in S such that the sum
is closest to a given number, target. Return the sum of the three integers.
You may assume that each input would have exactly one solution.

Example:
given array S = {-1 2 1 -4},
and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2) 
 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    int my_threeSumClosest(vector<int> &A, int B);
    int threeSumClosest(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        int bestSum = 1000000000, sum = 0;
        // Fix the smallest number in the three integers
        for (int i = 0; i < num.size() - 2; i++) {
            // Now num[i] is the smallest number in the three integers
            // in the solution
            int ptr1 = i + 1, ptr2 = num.size() - 1;
            while (ptr1 < ptr2) {
                sum = num[i] + num[ptr1] + num[ptr2];
                if (abs(target - sum) < abs(target - bestSum)) {
                    bestSum = sum;
                }
                if (sum > target) {
                    ptr2--;
                } else {
                    ptr1++;
                }
            }
        }
        return bestSum;
    }
};

int findClosestSum(vector<int>& nums, int low, int high, int target)
{
    int result = nums[low]+nums[high];
    while (low < high) {
        int temp = nums[low]+nums[high];
        if (temp == target)
            return target;
        if (abs(result-target) > abs(temp-target))
            result = temp;
        if (temp < target)
            ++low;
        else
            --high;
    }
    return result;
}


int Solution::my_threeSumClosest(vector<int> &A, int B) {
    sort(A.begin(), A.end());
    int nsize = A.size();
    int result = A[0]+A[1]+A[2];
    for (int i = 0; i < nsize-2; ++i) {
        int temp = findClosestSum(A, i+1, nsize-1, B-A[i]) + A[i];
        if (temp == B)
            return B;
        if (abs(B-temp) < abs(B-result))
            result = temp;        
    }

    return result;
}

int main()
{
    Solution sol;
    vector<int> nums;
    int target;

    // Expected: 33 (8+12+13)
    nums = {12, 1, 8, 2, 4, 5, 9, -1, -7, 17, 22, 49, 13};
    target = 33;

    cout << "Result: " << sol.threeSumClosest(nums, target) << endl;

    return 0;
}

