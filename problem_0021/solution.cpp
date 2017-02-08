/*
Implement StrStr
Please Note:
Another question which belongs to the category of questions which are
intentionally stated vaguely. Expectation is that you will ask for correct
clarification or you will state your assumptions before you start coding.
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
    int my_strStr(const string &haystack, const string &needle);

    int strStr(const string &haystack, const string &needle) {
        if (needle[0] == '\0') return 0;
        for (int i = 0; haystack[i] != '\0'; i++) {
            bool isMatched = true; 
            for (int j = 0; needle[j] != '\0'; j++) {
                // If remaining haystack length is less than needle's length,
                // we know needle is not present in haystack.
                if (haystack[i + j] == 0) return -1;
                if (haystack[i + j] != needle[j]) {
                    isMatched = false;
                    break;
                }
            }
            if (isMatched) return i; // Match found
        }
        return -1;
    }
};

static const int mod_const = 997;
static const int mul_const = 256;

int Solution::my_strStr(const string &haystack, const string &needle) {
    int needle_sum = 0, stack_sum = 0;
    int needle_size = static_cast<int>(needle.size());
    int stack_size = static_cast<int>(haystack.size());
    if (stack_size < needle_size)
        return -1;
    int mul_factor = 1;
    for (int i = 0; i < needle_size; ++i) {
        needle_sum = (needle_sum*mul_const + needle[i]) % mod_const;
        stack_sum = (stack_sum*mul_const + haystack[i]) % mod_const;
        if (i < needle_size - 1)
            mul_factor = (mul_factor * 256) % mod_const;
    }
    if (needle_sum == stack_sum &&
        haystack.compare(0, needle_size, needle) == 0)
        return 0;
    for (int i = needle_size; i < stack_size; ++i) {
        stack_sum = (stack_sum-haystack[i-needle_size]*mul_factor) %mod_const;
        stack_sum = (stack_sum * mul_const + haystack[i]) % mod_const;
        while (stack_sum < 0)
            stack_sum += mod_const;
        if (stack_sum == needle_sum &&
            haystack.compare(i-needle_size+1, needle_size, needle) == 0)
            return i - needle_size + 1;
    }

    return -1;
}

int main()
{
    Solution sol;
    string haystack, needle;
    haystack = "abcdef";
    needle = "cde";
    cout << "Result: " << sol.strStr(haystack, needle) << endl;

    return 0;
}
