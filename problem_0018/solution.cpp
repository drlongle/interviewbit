/*
Sorted Insert Position

Given a sorted array and a target value, return the index if the target is
found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.

[1,3,5,6], 5 -> 2
[1,3,5,6], 2 -> 1
[1,3,5,6], 7 -> 4
[1,3,5,6], 0 -> 0

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


using namespace std;

class Solution {
public:
    int my_searchInsert(vector<int> &nums, int target);
    int searchInsert(vector<int> &A, int target) {
        int n = A.size();
        int start = 0, end = n - 1;
        int mid;
        while(start <= end){
            mid = (start + end) / 2;
            if(target == A[mid]){
                return mid;
            }
            else if(target < A[mid]){
                end = mid - 1;
            }
            else{
                start = mid + 1;
            }
        }
        return start;
    }
};


int Solution::searchInsert(vector<int> &nums, int target) {
    int s_size = static_cast<int>(nums.size());
    if (!s_size) return 0;
    int begin = 0, end = s_size-1;
    int mid, result = 0;
    while (begin <= end) {
        mid = begin +((end-begin)>>1);
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            result = mid+1;
            begin = mid+1;
        }
        else
            end = mid-1;
    }
    return result;
}

int main()
{
    Solution sol;
    vector<int> nums;
    int target;

    nums = { 1, 3, 5, 6 };
    target = 7;

    int result = sol.searchInsert(nums,target);
    cout << "Result: " << result << endl;

    return 0;
}
