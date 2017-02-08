/*
Excel Column Number

Given a column title as appears in an Excel sheet, return its corresponding
column number.

Example:
    A -> 1
    B -> 2
    C -> 3
    ...
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
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


using namespace std;

class Solution {
public:
    int titleToNumber(string A);
};

int Solution::titleToNumber(string A) {
    int result = 0;
    int length = static_cast<int>(A.size());
    for (int i = 0; i < length; ++i) {
        result = 26*result + A[i] - 'A' + 1;
    }
    return result;
}


int main()
{
    Solution sol;
    string A;

    cout << "Input: ";
    cin >> A;
    cout << "Result: " << sol.titleToNumber(A) << endl;

    return 0;
}
