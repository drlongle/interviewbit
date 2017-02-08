/*
Compare Version Numbers

Compare two version numbers version1 and version2.
        If version1 > version2 return 1,
        If version1 < version2 return -1,
        otherwise return 0.

You may assume that the version strings are non-empty and contain only digits
and the . character. The . character does not represent a decimal point and is
used to separate number sequences. For instance, 2.5 is not "two and a half"
or "half way to version three", it is the fifth second-level revision of the
second first-level revision.

Here is an example of version numbers ordering:
0.1 < 1.1 < 1.2 < 1.13 < 1.13.4
 
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
    int my_compareVersion(string A, string B);
    int get_remain_version(const string s, string::size_type index);

    string transform(string str) {
        // In our current context, "" is equivalent to version 0.
        if (str.length() == 0) return "0";
        return str;
    }

    string nextSubstr(string str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '.') {
                return str.substr(i + 1);
            }
        }
        return transform("");
    }

    string curSubstr(string str) {
        int zeroIndex = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '.') {
                return transform(str.substr(zeroIndex, i - zeroIndex));
            }
            if (str[i] == '0' && zeroIndex == i) zeroIndex++;
        }
        return transform(str.substr(zeroIndex,(int)str.length() - zeroIndex));
    }

    int compareVersion(string version1, string version2) {
        for (; version1 != version2; version1 = nextSubstr(version1),
            version2 = nextSubstr(version2)) {
            string current1 = curSubstr(version1),
                   current2 = curSubstr(version2);
            int lenGap = (int)current1.length() - (int)current2.length();
            if (lenGap != 0) {
                return lenGap > 0 ? 1 : -1;
            } else if (current1 != current2) {
                return current1 > current2 ? 1 : -1;
            }
        }
        return 0;
    }
};

int Solution::get_remain_version(const string s, string::size_type index)
{
    if (index == string::npos)
        return 0;
    int result = 0;
    for ( ; index < s.size(); ++index) {
        if (isdigit(s[index]))
            result = result*10 + (s[index] - '0');
    }
    return result;
}

int Solution::my_compareVersion(string A, string B) {
    string::size_type a_index = 0, b_index = 0;
    while (a_index != string::npos && b_index != string::npos) {
        string::size_type a_nextindex = A.find('.', a_index);
        double val_a;
        if (a_nextindex == string::npos) {
            val_a = stoi(A.substr(a_index, a_nextindex));
            a_index = string::npos;
        } else {
            val_a = stoi(A.substr(a_index, a_nextindex-a_index));
            a_index = a_nextindex+1;
        }

        string::size_type b_nextindex = B.find('.', b_index);
        double val_b;
        if (b_nextindex == string::npos) {
            val_b = stoi(B.substr(b_index, b_nextindex));
            b_index = string::npos;
        } else {
            val_b = stoi(B.substr(b_index, b_nextindex-b_index));
            b_index = b_nextindex+1;
        }
        if (val_a > val_b)
            return 1;
        else if (val_a < val_b)
            return -1;
    }
    int rest_a = get_remain_version(A, a_index);
    int rest_b = get_remain_version(B, b_index);
    if (rest_a == rest_b)
        return 0;
    else if (rest_a > rest_b)
        return 1;
    else
        return -1;
}

int main()
{
    Solution sol;
    string A, B;
    A = "1.13";
    B = "1.13.4";

    A = "01";
    B = "1";
    cout << "Result: " << sol.compareVersion(A,B) << endl;

  return 0;
}
