/*
Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element
appears only once and return the new length.

Note that even though we want you to return the new length, make sure to
change the original array as well in place

Do not allocate extra space for another array, you must do this in place with
constant memory.

    Example:
    Given input array A = [1,1,2],
    Your function should return length = 2, and A is now [1,2]. 

*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
#include <iomanip>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std;

class Solution {
public:
    int my_removeDuplicates(vector<int> &nums) ;

    int removeDuplicates(vector<int> &A) {
        int count = 0, n = A.size();
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && A[i] == A[i+1]) continue;
            else {
                A[count] = A[i];
                count++;
            }
        }
        return count;
    }
};

int Solution::my_removeDuplicates(vector<int> &nums) {
    int slow=0, fast=0, nsize = nums.size();

    for ( ; fast < nsize; ++fast) {
        if (!fast  || nums[fast] != nums[slow-1])
            nums[slow++] = nums[fast];
    }
    return slow;
}

int main()
{
    Solution sol;
    vector<int> nums;
    int result;

    nums = {1,2};
    result = sol.removeDuplicates(nums);
    cout << "Result: " << result << endl;
    copy(nums.begin(), nums.begin()+result, ostream_iterator<int>(cout, ", "));

    return 0;
}
