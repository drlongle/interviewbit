/*
Colorful Number

For Given Number N find if its COLORFUL number or not

Return 0/1

COLORFUL number:

A number can be broken into different sub-sequence parts. 
Suppose, a number 3245 can be broken into parts like 3 2 4 5 32 24 45 324 245. 
And this number is a COLORFUL number, since product of every digit of a sub-sequence are different

Example:

N = 23
2 3 23
2 -> 2
3 -> 3
23 -> 6
this number is a COLORFUL number since product of every digit of a sub-sequence are different. 

Output : 1

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
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    int my_colorful(int num);
    int colorful(int N) {
        char st[20];
        sprintf(st, "%d", N);
        int len = strlen(st);
        map<long long, bool> Hash;

        for(int i = 0; i < len; ++i) {
            long long mul = 1;
            for(int j = i; j < len; ++j) {
                mul *= (long long)(st[j] - '0');
                if(Hash.find(mul) != Hash.end())
                        return 0;
                Hash[mul] = true;
            }
        }

        return 1;
    }
};

ll product_digits(const string& s)
{
    ll sum = 1;
    int ssize = s.size();
    for (int i = 0; i < ssize; ++i)
        sum *= (s[i]-'0');
    return sum;
}

int Solution::my_colorful(int num)
{
    string s = to_string(num);
    int ssize = s.size();
    unordered_set<ll> seen_numbers;
    for (int i = 1; i <= ssize; ++i)
    {
        for (int j = 0; j <= ssize -i; ++j)
        {
            string ss = s.substr(j, i);
            ll subnr = product_digits(s.substr(j, i));
            if (seen_numbers.find(subnr) != seen_numbers.end())
                return 0;
            seen_numbers.emplace(subnr);
        }
    }
    
    return 1;
}

int main()
{
    Solution sol;
    int n;
  
    n = 3245;
    n = 123;
    n = 12;
    cout << n << " -> " << sol.colorful(n) << endl;

    return 0;
}

