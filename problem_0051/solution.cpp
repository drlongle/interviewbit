/*
Equal

Given an array A of integers, find the index of values that satisfy A + B = C + D, where A,B,C & D are integers values in the array

Note:

1) Return the indices `A1 B1 C1 D1`, so that 
  A[A1] + A[B1] = A[C1] + A[D1]
  A1 < B1, C1 < D1
  A1 < C1, B1 != D1, B1 != C1 

2) If there are more than one solutions, 
   then return the tuple of values which are lexicographical smallest. 

Assume we have two solutions
S1 : A1 B1 C1 D1 ( these are values of indices int the array )  
S2 : A2 B2 C2 D2

S1 is lexicographically smaller than S2 iff
  A1 < A2 OR
  A1 = A2 AND B1 < B2 OR
  A1 = A2 AND B1 = B2 AND C1 < C2 OR 
  A1 = A2 AND B1 = B2 AND C1 = C2 AND D1 < D2

Example:

Input: [3, 4, 7, 1, 2, 9, 8]
Output: [0, 2, 3, 5] (O index)

If no solution is possible, return an empty list.

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

    vector<int> my_equal(vector<int> &nums) ;

    vector<int> equal(vector<int> &vec)
    {
        int N = vec.size();
        // With every sum, we store the lexicographically first occuring pair
        // of integers. 
        map<int, pair<int, int> > Hash;
        vector<int> Ans;
        
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                
                int Sum = vec[i] + vec[j];
                if (Hash.find(Sum) == Hash.end()) {
                    Hash[Sum] = make_pair(i, j);
                    continue;
                }
                
                pair<int, int> p1 = Hash[Sum];
                if (p1.first != i && p1.first != j &&
                    p1.second != i && p1.second != j) {
                    vector<int> ans;
                    ans.push_back(p1.first);
                    ans.push_back(p1.second);
                    ans.push_back(i);
                    ans.push_back(j);
                    
                    if (Ans.size() == 0) Ans = ans;
                    else {
                        // compare and assign Ans
                        bool shouldReplace = false;
                        for (int i1 = 0; i1 < Ans.size(); i1++) {
                            if (Ans[i1] < ans[i1]) break;
                            if (Ans[i1] > ans[i1]) {
                                shouldReplace = true;
                                break;
                            }
                        }
                        if (shouldReplace) Ans = ans;
                    }
                }
            }
        }

        return Ans;
    }
};

bool check_valid_pairs(pair<int,int>& p1, pair<int,int>& p2)
{
    return (p1.first < p2.first && p1.second != p2.first &&
        p1.second != p2.second);
}

void create_equal_entries(const vector<pair<int,int> >& pairs,
    vector<tuple<int,int,int,int> >& result)
{
    int nsize = pairs.size();
    for (int i = 0; i < nsize ; ++i)
        for (int j = i+1; j < nsize ; ++j)
        {
            if (pairs[i].first != pairs[j].first &&
                pairs[i].second != pairs[j].first &&
                pairs[i].second != pairs[j].second)
                result.emplace_back(make_tuple(pairs[i].first,
                    pairs[i].second, pairs[j].first, pairs[j].second));
        }
}

vector<int> Solution::my_equal(vector<int> &nums)
{
    vector<tuple<int,int,int,int>> result;
    vector<int> res;
    int nsize = nums.size();
    for (int i = 0; i < nsize; ++i)
    {
        map<ll, pair<int,int> > table;
        for (int j = i+1; j < nsize; ++j)
        {
            ll sum = nums[i]+nums[j];
            if (table.find(sum) == table.end())
                table[sum] = (make_pair(i,j));

            for (int k = i+1; k < nsize; ++k)
                for (int l = k+1; l < nsize; ++l)
                {
                    ll sum = nums[k]+nums[l];
                    if (table.find(sum) == table.end()) continue;
                    pair<int,int> p1 = table[sum];
                    if (p1.second != k && p1.second != l)
                    {
                        res.emplace_back(p1.first);
                        res.emplace_back(p1.second);
                        res.emplace_back(k);
                        res.emplace_back(l);
                        return res;
                    }
                }
        }
    }
    return vector<int>();
}

int main()
{
    Solution sol;
    vector<int> nums, result;

    // Expected: 0, 2, 3, 5
    nums = {3, 4, 7, 1, 2, 9, 8};

    result = sol.equal(nums);
    for (int i = 0; i < static_cast<int>(result.size()); ++i)
        cout << result[i] << ((i % 4 != 3) ? ", " : "\n");

    return 0;
}

