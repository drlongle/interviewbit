/*
Palindrome Integer

Determine whether an integer is a palindrome. Do this without extra space.

A palindrome integer is an integer x for which reverse(x) = x where reverse(x)
is x with its digit reversed. Negative numbers are not palindromic.

Example :

Input : 12121
Output : True

Input : 123
Output : False
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
    bool my_isPalindrome(int A) ;

    int reverse(int x) {
        int rev = 0, digit;
        while (x > 0) {
            digit = x%10;
            // check for overflow here
            if (rev > (INT_MAX / 10) ||
                (rev == (INT_MAX / 10) && digit > (INT_MAX % 10))) {
                return -1;
            }
            rev = rev * 10 + digit;
            x/=10;
        }
        return rev;
    }

    bool isPalindrome(int x) {
        if (x < 0) return false;
        // Lets try reversing x. If reverse overflows,
        // then the number is not palindromic anyway.
        return x == reverse(x);
    }
};

bool Solution::my_isPalindrome(int A) {
    long long running = 0, temp = A;
    if (A < 0) return false;

    while (temp) {
        running = running * 10 + temp % 10;
        temp /= 10;
    }
    return running == A;
}

int main()
{
    Solution sol;
    int A;
    cout << "Input: ";
    cin >> A;
    cout << boolalpha << "Result: " << sol.isPalindrome(A) << endl;

    return 0;
}
