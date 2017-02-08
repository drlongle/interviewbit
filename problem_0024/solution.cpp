/*
Integer To Roman

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
    string my_intToRoman(int num);
    string intToRoman(int num) {
        // 1000, 2000, 3000
        string M[] ={"", "M", "MM", "MMM"};
        // 100, 200, 300, .. 900
        string C[] ={"","C","CC","CCC","CD","D", "DC", "DCC", "DCCC", "CM"};
        // 10, 20, ... 90
        string X[] ={"","X","XX","XXX","XL","L", "LX", "LXX", "LXXX", "XC"};
        // 1, 2, ... 9
        string I[] ={"","I","II","III","IV","V", "VI", "VII", "VIII", "IX"};
        return M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[num%10];
    }
};

string Solution::my_intToRoman(int num)
{
    ostringstream oss;
    while(num >= 1000) {
        oss << "M";
        num -= 1000;
    }
    if (num >= 900) {
        oss << "CM";
        num -= 900;
    }
    if (num >= 500) {
        oss << "D";
        num -= 500;
    }
    if (num >= 400) {
        oss << "CD";
        num -= 400;
    }
    while(num >= 100) {
        oss << "C";
        num -= 100;
    }
    if (num >= 90) {
        oss << "XC";
        num -= 90;
    }
    if (num >= 50) {
        oss << "L";
        num -= 50;
    }
    if (num >= 40) {
        oss << "XL";
        num -= 40;
    }
    while(num >= 10) {
        oss << "X";
        num -= 10;
    }
    if (num >= 9) {
        oss << "IX";
        num -= 9;
    }
    if (num >= 5) {
        oss << "V";
        num -= 5;
    }
    if (num >= 4) {
        oss << "IV";
        num -= 4;
    }
    while(num > 0) {
        oss << "I";
        num -= 1;
    }
    string ret = oss.str();
    return ret;
}

int main()
{
    Solution sol;
    int input;
  
    cout << "Input: ";
    cin >> input;
    cout << "Result: " << sol.intToRoman(input) << endl;

    return 0;
}
