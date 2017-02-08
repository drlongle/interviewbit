/*
Distinct Numbers in Window

You are given an array of N integers, A1, A2 ,..., AN and an integer K. Return
the of count of distinct numbers in all windows of size K.

Formally, return an array of size N-K+1 where i'th element in this array
contains number of distinct elements in sequence Ai, Ai+1 ,..., Ai+k-1.

Note:
- If K > N, return empty array.

For example,

A=[1, 2, 1, 3, 4, 3] and K = 3

All windows of size K are

[1, 2, 1]
[2, 1, 3]
[1, 3, 4]
[3, 4, 3]

So, we return an array [2, 3, 3, 2].

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
    vector<int> dNums(vector<int> &A, int B) ;
    vector<int> my_dNums(vector<int> &A, int B) ;
};

vector<int> Solution::my_dNums(vector<int> &nums, int K) {
    unordered_map<int, int> lookup;
    vector<int> res;
    int nsize = nums.size();

    if (K > nsize) return res;

    for (int i = 0; i < K-1; ++i)
        ++lookup[nums[i]];

    for (int i = K-1; i < nsize; ++i)
    {
        ++lookup[nums[i]];
        res.emplace_back(lookup.size());
        int n = nums[i-K+1];
        if (--lookup[n] == 0)
            lookup.erase(n);
    }

    return res;
}

vector<int> Solution::dNums(vector<int> &A, int B) {
    assert(B<=A.size());
    int n=A.size();
    vector<int> ret;
    unordered_map <int, int> m;
    for(int i=0; i<n; i++){
        //increase key
        m[A[i]]++;
        if(i-B+1>=0){

            //decrease key
            ret.push_back(m.size());
            m[A[i-B+1]]--;

            //remove if count becomes 0
            if(m[A[i-B+1]]==0)m.erase(A[i-B+1]);
        }
    }
    return ret;
}

int main()
{
    Solution sol;
    vector<int> nums, res;
    int K;

    nums = {1, 2, 1, 3, 4, 3};
    K = 3;
    res = sol.dNums(nums, K);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;

    return 0;
}

