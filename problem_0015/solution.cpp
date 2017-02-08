/*
Square Root of Integer

Implement int sqrt(int x). Compute and return the square root of x.
If x is not a perfect square, return floor(sqrt(x))

Example :
Input : 11
Output : 3
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
    int my_sqrt(int x) {
        if (x <= 0)
            return 0;
        int begin = 0, end = x;
        long long mid = 0;
        while (begin <= end) {
            mid = begin + ((end-begin) >> 1);
            long long temp = mid*mid;
            if (temp == x)
                return mid;
            else if (temp > x)
                end = mid-1;
            else
                begin = mid+1;
        }

        return end;
    }

    int sqrt(int x) {
        if (x == 0) return 0;
        int start = 1, end = x, ans;
        while (start <= end) {
            int mid = (start + end) / 2;
            if (mid <= x / mid) {
                start = mid + 1;
                ans = mid;
            } else {
                end = mid - 1;
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;

    int x;
    cout << "Input: ";
    cin >> x;
    cout << "Result: " << sol.mySqrt(x) << endl;

    return 0;
}
