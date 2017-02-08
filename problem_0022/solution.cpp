/*
Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space
characters ' ', return the length of last word in the string. If the last
word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space
characters only.

Example:
Given s = "Hello World",
return 5 as length("World") = 5.

Please make sure you try to solve this problem without using library
functions. Make sure you only traverse the string once.
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
    int lengthOfLastWord(const string &A);
};

int Solution::lengthOfLastWord(const string &A) {
    int result = 0;
    int index = A.size() -1;
    while (index >= 0 && A[index] == ' ') --index;
    while (index >= 0 && isalpha(A[index])) {
        --index; result++;
    }
    return result;
}

int main()
{
    Solution sol;
    string input;
    input = "Hello World";
    cout << "Result: " << sol.lengthOfLastWord(input) << endl;

    return 0;
}
