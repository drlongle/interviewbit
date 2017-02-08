/*
Implement Power Function

Implement pow(x, n) % d. In other words, given x, n and d,
find (x ^ n % d)

Note that remainders on division cannot be negative. In other words, make sure
the answer you return is non negative.

Input : x = 2, n = 3, d = 3
Output : 2
2^3 % 3 = 8 % 3 = 2.

*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
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


using namespace std;

class Solution {
public:
    int my_pow(int x, int n, int d) ;

    int pow(int x, int n, int p) {
        if (n == 0) return 1 % p;

        long long ans = 1, base = x;
        while (n > 0) {
            // We need (base ** n) % p.
            // Now there are 2 cases.
            // 1) n is even. Then we can make base = base^2 and n = n / 2.
            // 2) n is odd. So we need base * base^(n-1)
            if (n % 2 == 1) {
                ans = (ans * base) % p;
                n--;
            } else {
                base = (base * base) % p;
                n /= 2;
            }
        }
        if (ans < 0) ans = (ans + p) % p;
        return ans;
    }
};

int Solution::my_pow(int x, int n, int d) {
    long long result = x % d;
    int p = 1;
    if (!x)
        return 0;
    if (n == 0)
        return 1;
    if (n == 1) {
        while (result < 0)
            result += d;
        return result;
    }

    while ((p << 1) <= n) {
        result = result * result % d;
        p <<= 1;
    }

    result = result * pow(x, n-p, d) % d;
    while (result < 0)
        result += d;
    return result;
}

int main()
{
    Solution sol;
    int x = 2, n = 3, d = 3;
    x = -1; n = 1; d= 20;

    cout << "Result: " << sol.pow(x,n,d) << endl;

    return 0;
}
