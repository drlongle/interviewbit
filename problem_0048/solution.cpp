/*
Permutations

Given a collection of numbers, return all possible permutations.

Example:

[1,2,3] will have the following permutations:

[1,2,3]
[1,3,2]
[2,1,3] 
[2,3,1] 
[3,1,2] 
[3,2,1]

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
  vector<vector<int> > my_permute(vector<int> &A);

  void permute(vector<int> &num, int start, vector<vector<int> > &result) {
        if (start == num.size() - 1) {
            result.push_back(num);
            return;
        } 
        for (int i = start; i < num.size(); i++) {
            swap(num[start], num[i]);
            permute(num, start + 1, result);
            swap(num[start], num[i]);
        }
    }

    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > result;
        if (num.size() == 0)
            return result;
        sort(num.begin(), num.end());
        permute(num, 0, result);
        return result;
    }
};

void do_permutation(const vector<int>& nums, int index,
    vector<vector<int>>& result)
{
    int nsize = nums.size();
    if (index == nsize)
        return;
    vector<int> numbers = nums;
    sort(numbers.begin()+index, numbers.end());
    for (int i = index; i < nsize; ++i)
    {
        swap(numbers[i], numbers[index]);
        if (index+1 == nsize)
            result.emplace_back(numbers);
        else
            do_permutation(numbers, index+1, result);
        swap(numbers[i], numbers[index]);
    }
}

vector<vector<int> > Solution::my_permute(vector<int> &numbers)
{
    vector<vector<int>> result;
    do_permutation(numbers, 0, result);
    return result;
}

int main()
{
    Solution sol;
    vector<vector<int>> result;
    vector<int> nums;

    nums = {1,2,3,4,5};
    result = sol.permute(nums);
    for (int i = 0; i < static_cast<int>(result.size()); ++i)
    {
        copy(result[i].begin(), result[i].end(),
            ostream_iterator<int>(cout, ","));
      cout << endl;
    }

    return 0;
}

