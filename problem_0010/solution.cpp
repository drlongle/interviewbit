/*
Greatest Common Divisor

Given 2 non negative integers m and n, find gcd(m, n)

GCD of 2 integers m and n is defined as the greatest integer g such that g is a
divisor of both m and n. Both m and n fit in a 32 bit signed integer.

Example
m : 6
n : 9
GCD(m, n) : 3 
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


using namespace std;

class Solution {
public:
    int gcd(int A, int B);
    int my_gcd(int A, int B);
};

int Solution::my_gcd(int A, int B) {
    if (A < 0) A = -A;
    if (B < 0) B = -B;
    if (!A || !B) return 1;
    if (B < A) swap(A, B);
    if (A == 1 || A == B || B%A == 0) return A;
    return gcd(A, B %A);
}

int Solution::gcd(int m, int n) {
    if(m < n)
        swap(m, n);

    if(n == 0)
        return m;

    return gcd(m % n, n);
}

int main()
{
    Solution sol;
    int m, n;
    m = 100;
    n = 120;
    cout << "Result: " << sol.gcd(n,m) << endl;
    return 0;
}
