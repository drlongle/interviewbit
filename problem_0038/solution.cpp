/*
All Factors

Given a number N, find all factors of N.

Example:

N = 6 
factors = {1, 2, 3, 6}

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
    vector<int> my_allFactors(int A);
    vector<int> allFactors(int n) {
        vector<int> ans;
        if (n < 2) {
            ans.push_back(n);
            return ans;
        }
        ans.push_back(1);
        ans.push_back(n);
        int upperLimit = (int)(sqrt(n));
        for (int i = 2; i <= upperLimit; i++) {
            if (i < n && n % i == 0) {
                ans.push_back(i);
                if (n / i != i) ans.push_back(n / i);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

vector<int> Solution::my_allFactors(int A) {
    vector<int> factors, tail;
    factors.emplace_back(1);
    if ((A & 1) == 0) {
        factors.emplace_back(2);
        if (A != 4)
            tail.insert(tail.begin(), A >> 1);
    }
    int upperlimit = sqrt(A);
    for (int i = 3; i <= upperlimit; ++i) {
        if (A % i == 0) {
            int cofact = A/i;
            factors.emplace_back(i);
            if (cofact != i)
                tail.insert(tail.begin(), cofact);
        }
    }
    copy(tail.begin(), tail.end(), back_inserter(factors));
    if (A!=1)
        factors.emplace_back(A);
    
    return factors;
}

int main()
{
    Solution sol;
    int A;
    vector<int> result;

    // Expected: 1 7 29 203 421 2947 12209 85463
    A = 85463;
    result = sol.allFactors(A);
    copy(result.begin(),result.end(),ostream_iterator<int>(cout, ", "));

    return 0;
}
