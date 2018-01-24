/*
Highest Product

Highest Product
Given an array of integers, return the highest product possible by multiplying 3 numbers from the array

Input:

array of integers e.g {1, 2, 3}

NOTE: Solution will fit in a 32-bit signed integer 

Example:
[0, -1, 3, 100, 70, 50]

=> 70*50*100 = 350000

Hint:
Do we need to consider all the elements from the array ?

Is it enough to consider just the 3 maximum numbers from the array ? Obviously No. Product of 2 negative numbers is positive. So, Negative numbers with higher absolute value might also be of interest.

How about maximum 3 elements, and 2 negative elements with the highest absolute value ?
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
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
    int my_maxp3(vector<int> &nums);

    int maxp3(vector<int> &Vec) {
        assert(Vec.size() >= 3);
        multiset<int> MAX_3;
        multiset<int> MIN_2;
            
        multiset<int>::iterator it;

        int N = Vec.size();
        int max_ele = -1000000000; // -Infinity
        for(int i = 0; i < N; ++i) {
           
            // Update max 3 elements.
            int sz = MAX_3.size();
            if(sz == 3) {
                   it = MAX_3.begin();
                   if (*it < Vec[i]) {
                       MAX_3.erase(MAX_3.begin());
                       MAX_3.insert(Vec[i]);
                   }
            } else {
                  MAX_3.insert(Vec[i]);
            }

            max_ele = max(max_ele, Vec[i]);

            if (Vec[i] < 0) {
                int sz = MIN_2.size();
                if(sz == 2) {
                    it = MIN_2.begin();
                    if (*it < abs(Vec[i])) {
                        MIN_2.erase(MIN_2.begin());
                        MIN_2.insert(abs(Vec[i]));
                    }
                } else {
                    MIN_2.insert(abs(Vec[i]));
                }
            }
        }
       
        int ans = -1000000000; // -Infinity
        // CASE 1 : TOP 3 ELEMENTS
        if (MAX_3.size() == 3) {
            int mul = 1;
            for (it = MAX_3.begin(); it != MAX_3.end(); it++) {
                mul *= (*it);
            }
            ans = max(ans, mul);
        }

        // CASE 2 : 2 NEGATIVE + 1 POSITIVE 
        if (MIN_2.size() == 2 && MAX_3.size() > 0) {
            int neg_mul = 1;
            for(it = MIN_2.begin(); it != MIN_2.end(); ++it) {
                neg_mul *= (*it);
            }
            neg_mul *= max_ele;
            ans = max(ans, neg_mul);
        }

        return ans;
    }

};

int Solution::my_maxp3(vector<int> &nums) {
    int res, N;
    N = nums.size();

    sort(nums.begin(), nums.end());
    res = nums[N-1]*nums[N-2]*nums[N-3];
    res = max(res, nums[0]*nums[1]*nums[N-1]); 

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> nums;

    // Expected: 350000
    nums = {0, -1, 3, 100, 70, 50};

    // Expected: 350000
    nums = {0, -1, 3, 100, -70, -50}; 

    int res = sol.maxp3(nums);

    cout << "Result: " << res << endl;

    return 0;
}

