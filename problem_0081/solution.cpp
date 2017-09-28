/*
Intersecting Chords in a Circle 

Given a number N, return number of ways you can draw N chords in a circle with 2*N points such that no 2 chords intersect.
Two ways are different if there exists a chord which is present in one way and not in other.

For example,

N=2
If points are numbered 1 to 4 in clockwise direction, then different ways to draw chords are:
{(1-2), (3-4)} and {(1-4), (2-3)}

So, we return 2.
Notes:

1 <= N <= 1000
Return answer modulo 10^9+7.

Think in terms of DP.
Can we relate answer for N with smaller answers.

If we draw a chord between any two points, can you observe current set of points getting broken into two smaller sets S_1 and S_2? Can a chord be drawn between two points where each point belong to different set?

If we draw a chord from a point in S_1 to a point in S_2, it will surely intersect the chord we’ve just drawn.

So, we can arrive at a recurrence that Ways(n) = sum[i = 0 to n-1] { Ways(i)*Ways(n-i-1) }.
Here we iterate over i, assuming that size of one of the sets is i and size of other set automatically is (n-i-1) since we’ve already used a pair of points and i pair of points in one set.
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

using namespace std;

vector<ll> dp;

const ll MOD_CONST = 1000000007;

ll chord_main(int n)
{
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = (sum + dp[i] * dp[n-i-1]) % MOD_CONST;
    }
    return sum;
}

class Solution {
public:
    int chordCnt(int A);
};

int Solution::chordCnt(int A)
{
    dp.resize(A+1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= A; ++i)
        dp[i] = chord_main(i);
    return dp[A];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int n;
    cout << "Input: ";

    // n = 3 --> Expected: 5
    // n = 4 --> Expected: 14
    cin >> n;

    cout << "Result: " << sol.chordCnt(n) << endl;

    return 0;
}

