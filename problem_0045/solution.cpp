/*
Subsets
Total Accepted: 96662 Total Submissions: 305340 Difficulty: Medium

Given a set of distinct integers, nums, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
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

void get_subset(vector<int>& nums, vector<bool>& used, size_t index,
    vector<int>& one_subset, vector<vector<int> >& result)
{
    result.emplace_back(one_subset);
    for (size_t i = index; i < nums.size(); ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            one_subset.emplace_back(nums[i]);
            get_subset(nums, used, i, one_subset, result);
            used[i] = false;
            one_subset.pop_back();
        }
    }
}

class Solution {
public:
    vector<vector<int>> my_subsets(vector<int>& nums);
    
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > result; 
        vector<int> current;
        sort(S.begin(), S.end());
        generateSubsets(S, 0, current, result);
        sort(result.begin(), result.end());
        return result;
    }

    void generateSubsets(vector<int> &S, int index,
        vector<int> &current, vector<vector<int> > &result) {
        if (index >= S.size()) {
            result.push_back(current);
            return;
        }
        // Ignore the current index.
        generateSubsets(S, index + 1, current, result);

        // Include the current index. 
        current.push_back(S[index]);
        generateSubsets(S, index + 1, current, result);
        current.pop_back();
    }
};

vector<vector<int>> Solution::my_subsets(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int> > result;
    vector<int> one_subset;
    vector<bool> used(nums.size(), false);
    
    get_subset(nums, used, 0, one_subset, result);
    
    return result;
}

int main()
{
    Solution sol;
    vector<int> nums;
    vector<vector<int> > result;
  
    nums = {1,2,3};
    result = sol.subsets(nums);
    for (size_t i = 0; i < result.size(); ++i)
    {
        copy(result[i].begin(), result[i].end(),
            ostream_iterator<int>(cout, ", "));
        cout << endl;
    }
    return 0;
}

