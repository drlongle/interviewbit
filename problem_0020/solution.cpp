/*
Palindrome String

Given a string, determine if it is a palindrome, considering only alphanumeric
characters and ignoring cases.

Example:
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Return 0 / 1 ( 0 for false, 1 for true ) for this problem.
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
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
    int my_isPalindrome(string A) ;

    bool isPalindrome(string s) {
        int i = 0, j = (int)s.size() - 1;
        while(i < j)
        {
            while(i < j && !isalnum(s[i])) i++;
            while(i < j && !isalnum(s[j])) j--;
            if (toupper(s[i]) != toupper(s[j])) return false;
            i++;
            j--;
        }
        return true;
    }
};

int Solution::my_isPalindrome(string A) {
    int low = 0;
    int high = A.size()-1;
    while (low < high) {
        while (low < high && !isalnum(A[low]))
            ++low;
        while (low < high && !isalnum(A[high]))
            --high;
        char l = A[low];
        char h = A[high];
        if (isalpha(l) && isupper(l))
            l = tolower(l);
        if (isalpha(h) && isupper(h))
            h = tolower(h);
        if (l != h)
            return 0;
        ++low, --high;
    }
    return 1;
}

int main()
{
    Solution sol;
    string st;
 
    st = "A man, a plan, a canal: Panama";
    //st = "race a car";
    cout << "Result: " << sol.isPalindrome(st) << endl;

    return 0;
}
