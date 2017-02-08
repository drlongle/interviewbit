/*
Evaluate Expression

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6


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
    int my_evalRPN(vector<string> &symbols) ;

    int evalRPN(vector<string> &tokens) {
        stack<int> st;
        for(int i = 0; i < tokens.size(); ++i) {
            if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
                tokens[i] == "/") {
                int v1=st.top();
                st.pop();
                int v2=st.top();
                st.pop();
                switch(tokens[i][0]) {
                    case '+':
                        st.push(v2 + v1);
                        break;
                    case '-':
                        st.push(v2 - v1);
                        break;
                    case '*':
                        st.push(v2 * v1);
                        break;
                    case '/':
                        st.push(v2 / v1);
                        break;
                }
            } else {
                st.push(atoi(tokens[i].c_str()));
            }
        }
        return st.top();
    }

};

int calc(char c, int a, int b)
{
    switch(c)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
    }
    return 0;
}

int Solution::my_evalRPN(vector<string> &symbols) {
    stack<int> numbers;
    for (const auto& s: symbols)
    {
        if (s == "+" || s == "-" || s == "*" || s == "/")
        {
            int b = numbers.top();
            numbers.pop();
            int a = numbers.top();
            numbers.pop();
            numbers.emplace(calc(s[0],a,b));
        }
        else
            numbers.emplace(stoi(s));
    }

    return numbers.top();
}

int main()
{
    Solution sol;
    vector<string> symbols;

    // Expected: 9
    symbols = {"2", "1", "+", "3", "*"};

    // Expected: 9
    //symbols = {"4", "13", "5", "/", "+"};

    cout << "Result: " << sol.evalRPN(symbols) << endl;

    return 0;
}

