/*
Nearest Smaller Element

Given an array, find the nearest smaller element G[i] for every element A[i] in
the array such that the element has an index smaller than i.

More formally,

G[i] for an element A[i] = an element A[j] such that 
    j is maximum possible AND 
    j < i AND
    A[j] < A[i]

Elements for which no smaller element exist, consider next smaller element as -1.

Example:

Input : A : [4, 5, 2, 10]
Return : [-1, 4, -1, 2]

Example 2:

Input : A : [3, 2, 1]
Return : [-1, -1, -1]

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
    vector<int> prevSmaller(vector<int> &numbers);
};

vector<int> Solution::prevSmaller(vector<int> &numbers) {
    stack<int> prevs;
    vector<int> result;
    for (const auto& n: numbers) {
        while (prevs.size() && prevs.top() >= n)
            prevs.pop();
        if (prevs.empty())
            result.emplace_back(-1);
        else
            result.emplace_back(prevs.top());
        prevs.emplace(n);
    }
    return result;
}

int main()
{
    Solution sol;
    vector<int> numbers, result;
  
    numbers = {4, 5, 2, 10};
    numbers = {5, 2, 1};
  
    // Expected: -1 -1 -1 -1 4 24 24 -1 
    numbers = {39, 27, 11, 4, 24, 32, 32, 1};
  
    result = sol.prevSmaller(numbers);
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, ", "));
  
    return 0;
}

