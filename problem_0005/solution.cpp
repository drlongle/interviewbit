/*
Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

For example: Given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <string.h>

using namespace std;

struct Number
{
    Number(const int& i) : m_string(to_string(i)) { }

    bool operator<(const Number& other) const
    {
        string st1 = m_string + other.m_string;
        string st2 = other.m_string + m_string;
        return (st1 > st2) ;
    }
    string m_string;
};

class Solution {
public:
    static bool compareNum(string a, string b) {
        return a + b > b + a;
    }

    string my_largestNumber(const vector<int> &num);
    string largestNumber(const vector<int> &num) {
        string result;
        vector<string> str;
        for (int i = 0; i < num.size(); i++) {
            str.push_back(to_string(num[i]));
        }
        sort(str.begin(), str.end(), compareNum);
        for (int i = 0; i < str.size(); i++) {
            result += str[i];
        }

        int pos = 0;
        while (result[pos] == '0' && pos + 1 < result.size()) pos++;
        return result.substr(pos);
    }
};

string Solution::my_largestNumber(const vector<int> &A) {
    vector<Number> numbers;
    for (const auto& a: A)
        numbers.emplace_back(a);

    sort(numbers.begin(), numbers.end());
    ostringstream oss;
    for (const auto& n: numbers)
        oss << n.m_string;

    string result = oss.str();
    if (!atoi(result.c_str()))
        return "0";
    return result;
}

int main()
{
    Solution sol;
    vector<int> input;

    input = {9,12,3,5};
    input = {3, 30, 34, 5, 9};
    input = {102, 804, 374, 895, 1009, 22, 99};
    input = { 0, 0, 0, 0, 0 };

    string result = sol.largestNumber(input);
    cout << "Result: " << result << endl;

    return 0;
}
