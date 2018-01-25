/*
Smallest sequence with given Primes

Given three prime number(p1, p2, p3) and an integer k. Find the first(smallest) k integers which have only p1, p2, p3 or a combination of them as their prime factors.

Example:

Input :
Prime numbers : [2,3,5]
k : 5

If primes are given as p1=2, p2=3 and p3=5 and k is given as 5, then the sequence of first 5 integers will be:

Output:
{2,3,4,5,6}

Explanation :
4 = p1 * p1 ( 2 * 2 )
6 = p1 * p2 ( 2 * 3 )

Note: The sequence should be sorted in ascending order

Hint:
Naive solution : We are interested in only those numbers whose prime factorization contains no other prime number other than p1, p2 and p3. So we can simply iterate all numbers and can check their prime factorization.

Better solution : Can we incrementally construct new numbers starting from the lowest prime p1 ? Would this become similar to Breadth first search / Dijkstra ?


Solution approach:
The naive solution will be to check prime factorization of every natural number incrementally till k numbers are found. However, that will be too slow.

As mentioned in the previous hint, this problem can be addressed as a modified BFS / Dijkstra. We push p1, p2 and p3 to a min heap.
Every time, we repeat the following process till we find k numbers :

- M = Pop out the min element in the min heap. 
 - Add M to the final answer. 
 - Push M * p1, M * p2, M * p3 to the min heap if they are not already present in the heap ( We can use a hash map to track this ) 

However, this is O( k * log k ).
Can we do better than this ?

It turns out we can.
We use the fact that there are only 3 possibilities of getting to a new number : Multiply by p1 or p2 or p3.

For each of p1, p2 and p3, we maintain the minimum number in our set which has not been multiplied with the corresponding prime number yet.
So, at a time we will have 3 numbers to compare.
The corresponding approach would look something like the following :


Algorithm:
initialSet = [p1, p2, p3] 
indexInFinalSet = [0, 0, 0]

for i = 1 to k 
  M = get min from initialSet. 
  add M to the finalAnswer if last element in finalAnswer != M
  if M corresponds to p1 ( or in other words M = initialSet[0] )
    initialSet[0] = finalAnswer[indexInFinalSet[0]] * p1
    indexInFinalSet[0] += 1
  else if M corresponds to p2 ( or in other words M = initialSet[1] )
    initialSet[1] = finalAnswer[indexInFinalSet[1]] * p1
    indexInFinalSet[1] += 1
  else 
    # Similar steps for p3. 
end

*/

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
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

#define pb push_back

using namespace std;

class Solution {
public:
    vector<int> solve(int a, int b, int c, int k);
    vector<int> my_solve(int a, int b, int c, int k);
};

vector<int> Solution::solve(int A, int B, int C, int D) 
{
    vector<int> dp;
    dp.pb(1);
    int i1 = 0,i2 = 0, i3 = 0;
    for(int i = 1; i <= D; i++)
    {
        dp.pb(min(dp[i1]*A,min(dp[i2]*B,dp[i3]*C)));
        
        if(dp[i] == dp[i1]*A)
            i1++;
    
        if(dp[i] == dp[i2]*B)
            i2++;
            
        if(dp[i] == dp[i3]*C)
            i3++;
    }
    vector<int>ans;
    for(int i = 1; i < dp.size(); i++)
        ans.pb(dp[i]);
        
    return ans;
}

vector<int> Solution::my_solve(int a, int b, int c, int k) {
    vector<int> nums;
    set<int> candidates;
    candidates.insert(a);
    candidates.insert(b);
    candidates.insert(c);
    while (nums.size() < k) {
        auto it = candidates.begin();
        int n = *it;
        candidates.erase(it);
        nums.push_back(n);
        candidates.insert(n*a);
        candidates.insert(n*b);
        candidates.insert(n*c);
    }

    return nums;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> res;
    int a, b, c, k;

    a = 2;
    b = 3;
    c = 5;
    k = 5;

    res = sol.solve(a, b, c, k);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}

