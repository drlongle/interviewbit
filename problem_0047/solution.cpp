/*
Kth Permutation Sequence

The set [1,2,3,..,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3 ) :

1. "123"
2. "132"
3. "213"
4. "231"
5. "312"
6. "321"

Given n and k, return the kth permutation sequence.

For example, given n = 3, k = 4, ans = "231"

Good questions to ask the interviewer :

    What if n is greater than 10. How should multiple digit numbers be represented in string?
    > In this case, just concatenate the number to the answer.
    > so if n = 11, k = 1, ans = "1234567891011"

    Whats the maximum value of n and k?
    > In this case, k will be a positive integer thats less than INT_MAX.
    > n is reasonable enough to make sure the answer does not bloat up a lot.

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

pair<int,int> div_factorial(int n, int k)
{
    int quotient = k, remainder = k, product = 1;
    for (int i = 2; i <= n && quotient > 0; i++)
    {
        quotient /= i;
        product *= i;
    }

    if (quotient)
        remainder = k - product*quotient;
    return make_pair(quotient, remainder);
}

string get_permutation(vector<int>& nums, int k)
{
    int nsize = nums.size();
    if (!nsize)
        return "";
    pair<int,int> p = div_factorial(nsize-1, k);

    int digit = nums[p.first];
    nums.erase(nums.begin()+p.first);

    stringstream ss;
    ss << digit;
    ss << get_permutation(nums, p.second);
    return ss.str();
}

class Solution {
public:
    string my_getPermutation(int n, int k);

    int factorial(int n) {
        if (n > 12) {
            // this overflows in int. So, its definitely greater than k
            // which is all we care about. So, we return INT_MAX which
            // is also greater than k.
            return INT_MAX;
        }
        // Can also store these values. But this is just < 12 iteration, so meh!
        int fact = 1;
        for (int i = 2; i <= n; i++) fact *= i;
        return fact;
    }

    string getPermutation(int k, vector<int> &candidateSet) {
        int n = candidateSet.size();
        if (n == 0) {
            return "";
        }
        if (k > factorial(n)) return ""; // invalid. Should never reach here.

        int f = factorial(n - 1);
        int pos = k / f;
        k %= f;
        string ch = to_string(candidateSet[pos]);
        // now remove the character ch from candidateSet. 
        candidateSet.erase(candidateSet.begin() + pos);
        return ch + getPermutation(k, candidateSet);
    }
    
    string getPermutation(int n, int k) {
        vector<int> candidateSet; 
        for (int i = 1; i <= n; i++) candidateSet.push_back(i);
        return getPermutation(k - 1, candidateSet);
    }
};

string Solution::my_getPermutation(int n, int k)
{
    vector<int> nums = vector<int>(n);
    iota(nums.begin(), nums.end(), 1);

    return get_permutation(nums, k-1);
}

int main()
{
    Solution sol;
    int n, k;
  
    n = 3, k = 4;
    n = 11, k = 1;

    cout << "Result: " << sol.getPermutation(n, k) << endl;

    return 0;
}

