/*
 * Letter Combinations of a Phone Number
 * 
Given a digit string, return all possible letter combinations that the number
could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in
any order you want. 
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

vector<char> digit_to_chars(char digit)
{
    vector<char> result;
    char ch;
    switch(digit)
    {
    case '0':
        result = {'0'};
        break;
    case '1':
        result = {'1'};
        break;
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
        if (digit >= '2' && digit <= '6')
        {
            ch = 'a' + (digit - '2')*3;
            for (int i = 0; i < 3; ++i)
                result.emplace_back(ch++);
        }
        break;
    case '7':
        result = {'p','q','r','s'};
        break;
    case '8':
        result = {'t','u','v'};
        break;
    case '9':
        result = {'w','x','y','z'};
        break;
    }

    return result;
}

void letter_combinations(string digits, size_t index, string& temp,
    vector<string>& results) {
    if (index ==  digits.size()) {
        results.emplace_back(temp);
        return;
    }
    vector<char> chs = digit_to_chars(digits[index]);
    for (auto& ch: chs) {
        temp.push_back(ch);
        letter_combinations(digits, index+1, temp, results);
        temp.pop_back();
    }
}

class Solution {
    public:
        string charmap[10];

        Solution() {
            charmap[0] = "0";
            charmap[1] = "1";
            charmap[2] = "abc";
            charmap[3] = "def";
            charmap[4] = "ghi";
            charmap[5] = "jkl";
            charmap[6] = "mno";
            charmap[7] = "pqrs";
            charmap[8] = "tuv";
            charmap[9] = "wxyz";
        }

        void generateHelper(string &current, int index, string &digits,
            vector<string> &ans) {
            if (index == digits.length()) {
                ans.push_back(current);
                return;
            }
            int digit = digits[index] - '0';
            for (int i = 0; i < charmap[digit].length(); i++) {
                current.push_back(charmap[digit][i]);
                generateHelper(current, index + 1, digits, ans);
                current.pop_back();
            }
            return;
        }

        vector<string> letterCombinations(string digits) {
            vector<string> ans;
            string current = "";
            generateHelper(current, 0, digits, ans);
            return ans;
        }
        
        vector<string> my_letterCombinations(string digits);
};

vector<string> Solution::my_letterCombinations(string digits) {
    vector<string> result;
    if (digits.size()) {
        string one_result;
        letter_combinations(digits, 0, one_result, result);
    }
    return result;
}

int main()
{
    Solution sol;
    string digits;
    vector<string> result;
  
    digits = "23";
    digits = "0";
    digits = "0120";

    result = sol.letterCombinations(digits);
    copy(result.begin(), result.end(), ostream_iterator<string>(cout, ", "));

    return 0;
}

