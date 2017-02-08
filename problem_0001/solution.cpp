/*
Max Non Negative SubArray

Find out the maximum sub-array of non negative numbers from an array. The
subarray should be continuous. That is, a sub-array created by choosing the
second and fourth element and skipping the third element is invalid.

Maximum subarray is defined in terms of the sum of the elements in the
subarray. Subarray A is greater than sub-array B if sum(A) > sum(B).

Example:

A : [1, 2, 5, -7, 2, 3]
The two sub-arrays are [1, 2, 5] [2, 3].
The answer is [1, 2, 5] as its sum is larger than [2, 3]

NOTE: If there is a tie, then compare with segment's length and return segment
which has maximum length

NOTE 2: If there is still a tie, then return the segment with minimum starting
index.
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <string.h>

using namespace std;

class Solution
{
public:
    vector<int> my_maxset(vector<int>& Vec) ;

    vector<int> maxset(vector<int> Vec)
    {
        int N = Vec.size();
        long long mx_sum = 0;
        long long cur_sum = 0;
        int mx_range_left = -1;
        int mx_range_right = -1;
        int cur_range_left = 0;
        int cur_range_right = 0;

        while(cur_range_right < N) {
            if(Vec[cur_range_right] < 0) {
                cur_range_left = cur_range_right + 1;
                cur_sum = 0;
            } else {
                cur_sum += (long long)Vec[cur_range_right];
                if(cur_sum > mx_sum) {
                    mx_sum = cur_sum;
                    mx_range_left = cur_range_left;
                    mx_range_right = cur_range_right + 1;
                } else if(cur_sum == mx_sum) {
                    if(cur_range_right + 1 - cur_range_left > mx_range_right -
                        mx_range_left) {
                        mx_range_left = cur_range_left;
                        mx_range_right = cur_range_right + 1;
                    }
                }
            }
            cur_range_right++;
        }
        vector<int> ans;
        if(mx_range_left == -1 || mx_range_right == -1)
            return ans;

        for(int i = mx_range_left; i < mx_range_right; ++i)
            ans.push_back(Vec[i]);
        return ans;
    }
};

vector<int> Solution::my_maxset(vector<int> &A) {
    int i = 0, j;
    int size = static_cast<int>(A.size());
    long long running_sum = 0, result_sum = 0;
    vector<int> result;

    while (i < size) {
        while (A[i] < 0 && i < size) ++i;
        running_sum = 0;
        for (j = i; A[j] >= 0 && j < size; ++j)
            running_sum += A[j];
        if (running_sum > result_sum || (running_sum == result_sum &&
            j-i+1 > static_cast<int>(result.size())))
        {
            result_sum = running_sum;
            result.clear();
            copy(A.begin()+i, A.begin()+j, back_inserter(result));
        }
        i = j;
    }

    return result;
};

int main()
{
    Solution sol;
    vector<int> input, result;
    input = {1, 2, 5, -7, 2, 3};
    input = {1, 2, 5, -7, 2, 3, 9};
    result = sol.maxset(input);
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, ", "));
    return 0;
}
