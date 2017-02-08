/*
Decode Ways
Total Accepted: 72667 Total Submissions: 408775 Difficulty: Medium

A message containing letters from A-Z is being encoded to numbers using the
following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of ways
to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

Hint:

Lets first look at the bruteforce solution.
It only makes sense to look at 1 digit or 2 digit pairs ( as 3 digit sequence
will be greater than 26 ).

So, when looking at the start of the string, we can either form a one digit
code, and then look at the ways of forming the rest of the string of length
L - 1, or we can form 2 digit code if its valid and add up the ways of decoding
rest of the string of length L - 2. This obviously is exponential.

The code would go something like the following :

 int ways(string &s, int startIndex) {
    // BASE CASES

    int answer = 0;
if (isValid(s[startIndex])) answer += ways(s, startIndex + 1);
    if (isValid(s[startIndex] + s[startIndex + 1])) answer += ways(s, startIndex + 2);
    return answer;
 }

Note that in this case, startIndex can only take L number of values. Can you use
the fact to store the result so that the function processing does not happen so
many times ?

 */

#include <algorithm>
#include <array>
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
    int my_numDecodings(string s) {
        int ssize = s.size();
        if (!ssize) return 0;
        vector<int> count(ssize, 0);

        for (int i = ssize-1; i >= 0; --i)
        {
            switch(s[i])
            {
            case '0':
                if (i == 0 || (i < ssize-1 && s[i+1] == '0'))
                    return 0;
                else
                    count[i] = (i == ssize-1) ? 0 : count[i+1];
                break;
            case '1':
            case '2':
                if (i == ssize-1)
                    count[i] = 1;
                else if (s[i+1] == '0')
                    count[i] = (i+1 == ssize-1) ? 1 : count[i+2];
                else
                    count[i] = count[i+1];
                if ((i+1 <= ssize-1) &&
                    ((s[i] == '1') || (s[i] == '2' && s[i+1] <= '6'))
                    && s[i+1] > '0' && (s[i+2] != '0'))
                    count[i] += (i == ssize-2) ? 1 : count[i+2];
                break;
            default:
                if (i < ssize-1 && s[i+1] == '0')
                    return 0;
                count[i] = (i == ssize-1 || s[i+1] == '0') ? 1 : count[i+1];
            }
        }

        return count[0];
    }
    
private:
    int solution[100001];
public:

    bool isValid(char ch) {
        return (isdigit(ch) && ch > '0');
    }

    int numDecodings(string s) {
        memset(solution, -1, s.length() * sizeof(int));
        if (s.length() == 0) return 0;
        return ways(s, 0);
    }

    int ways(string &s, int startIndex) {
        if (startIndex == s.length()) return 1;
        if (!isValid(s[startIndex])) return 0;
        
        // memoize
        if (solution[startIndex] != -1) return solution[startIndex];
        
        int answer = 0;
        // 1 digit
        answer += ways(s, startIndex + 1);
        // 2 digit
        if (startIndex < s.length() - 1 && isdigit(s[startIndex + 1]) &&
            ((s[startIndex] - '0') * 10 + s[startIndex + 1] - '0') <= 26) {
            answer += ways(s, startIndex + 2);
        }

        return solution[startIndex] = answer;
    }
};

int main()
{
    Solution sol;
    string s;
  
    // Expected: 0?
    s = "100";
  
    // Expected: 1
    s = "110";
  
    // Expected: 4
    s = "2611055971756562";
  
    cout << "Input: ";
    cin >> s;
    cout << "Result: " << sol.numDecodings(s) << endl;

    return 0;
}

