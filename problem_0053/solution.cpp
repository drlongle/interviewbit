/*
Fraction to Recurring Decimal
Total Accepted: 31483 Total Submissions: 205372 Difficulty: Medium

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,
    Given numerator = 1, denominator = 2, return "0.5".
    Given numerator = 2, denominator = 1, return "2".
    Given numerator = 2, denominator = 3, return "0.(6)".

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
    string my_fractionToDecimal(int numerator, int denominator);

    string fractionToDecimal(int numerator, int denominator) {
        int64_t n = numerator, d = denominator;
        // zero numerator
        if (n == 0) return "0";

        string res;
        // determine the sign
        if (n < 0 ^ d < 0) res += '-';

        // remove sign of operands
        n = abs(n), d = abs(d);

        // append integral part
        res += to_string((n / d));

        // in case no fractional part
        if (n % d == 0) return res;

        res += '.';

        unordered_map<int, int> map;

        // simulate the division process
        for (int64_t r = n % d; r; r %= d) {

            // meet a known remainder
            // so we reach the end of the repeating part
            if (map.find(r) != map.end()) {
                // insert '(' at the start position where we first saw
                // the remainder
                res.insert(map[r], 1, '(');
                res += ')';
                break;
            }

            // the remainder is first seen
            // remember the current position for it
            map[r] = res.size();

            r *= 10;

            // append the quotient digit
            res.push_back((char)('0' + (r / d)));
        }

        return res;    
    }
};

string Solution::my_fractionToDecimal(int numerator, int denominator) {
    string res;
    unordered_map<int, size_t> seen_numbers;
    ll num = numerator, denom = denominator, quotient;
    if (num*denom < 0) res.insert(0,1,'-');
    if (!denom)
    {
       num != 0 ? res.append("MAX_INT") : res.append("NaN");
       return res;
    }
    num = abs(num);
    denom = abs(denom);

    quotient = num / denom;
    num %= denom;
    res.append(to_string(quotient));
    if (!num)
        return res;
    res.push_back('.');
    while (num)
    {
        num *= 10;
        unordered_map<int,size_t>::iterator it = seen_numbers.find(num);
        if (it == seen_numbers.end())
        {
            seen_numbers[num] = res.size();
            res.push_back('0' + (num / denom));
            num %= denom;
        }
        else
        {
            res.insert(it->second, 1, '(');
            res.push_back(')');
            break;
        }
    } 

    return res;
}

int main()
{
    Solution sol;
    int num, denom;
    string res;

    num = 1, denom = 2;
    num = 2, denom = 1;
    num = -2147483648, denom = -1;
    res = sol.fractionToDecimal(num, denom);
    cout << "Result : " << res << endl;

    return 0;
}

