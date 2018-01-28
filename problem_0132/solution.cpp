/*
Maximum Product Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

Hint:
This problem can be solved in different ways:
- DP based solution: Try to compute the maximum positive/negative product ending at any index i.
- Observation based solution: Maintain something similar to slider and try to figure out when to change the position of slider. Keep maintaing positive/negative maximum product too.

Solution approach:

If there were no zeros or negative numbers, then the answer would definitely be the product of the whole array.

Now lets assume there were no negative numbers and just positive numbers and 0. In that case we could maintain a current maximum product which would be reset to A[i] when 0s were encountered. 
When the negative numbers are introduced, the situation changes ever so slightly. We need to now maintain the maximum product in positive and maximum product in negative. On encountering a negative number, the maximum product in negative can quickly come into picture.
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
    int maxProduct(int A[], int n) {
        // store the result that is the max we have found so far
        int r = A[0];

        // imax/imin stores the max/min product of
        // subarray that ends with the current number A[i]
        for (int i = 1, imax = r, imin = r; i < n; i++) {
            // multiplied by a negative makes big number smaller, small number bigger
            // so we redefine the extremums by swapping them
            if (A[i] < 0)
                swap(imax, imin);

            // max/min product for the current number is either the current number itself
            // or the max/min by the previous number times the current one
            imax = max(A[i], imax * A[i]);
            imin = min(A[i], imin * A[i]);

            // the newly computed max value is a candidate for our global result
            r = max(r, imax);
        }
        return r;
    }

    int my_maxProduct(vector<int>& nums) {
        int nsize = nums.size();
        vector<int> down = vector<int>(nsize, 1);

        int res = nums[0];
        int temp = 1;
        int total_product = 1;
        for (int i = 0; i < nsize; ++i)
        {
            temp = temp ? temp*nums[i] : nums[i];
            total_product *= nums[i];
            if (total_product > res)
                res = total_product;
        }

        temp = 1;
        for (int i = nsize-1; i >= 0; --i)
        {
            temp = temp ? temp*nums[i] : nums[i];
            down[i] = temp;
        }

        int up_index, down_index;
        for (up_index = 0; up_index < nsize; ++up_index)
            if (nums[up_index] != 1 && nums[up_index] != -1)
                break;
        for (down_index = nsize-1; down_index >= 0; --down_index)
            if (nums[down_index] != 1 && nums[down_index] != -1)
                break;
        if (up_index == nsize)
            return res;

        for (int i = up_index; i < nsize; ++i)
        {
            int dividend = down[i];
            if (dividend > res)
                res = dividend;
            for (int j = i; j <= down_index && nums[j]; ++j)
            {
                int divisor = (j == nsize-1 ? 1 : down[j+1]);
                if (divisor == 0 || divisor == 1)
                    continue;
                int temp = dividend / divisor;
                if (temp > res)
                    res = temp;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums;
    nums = {-2,1,-3,4,-1,2,1,-5,4};
    int res = sol.maxProduct(nums);
    cout << "Result: " << res << endl;

    return 0;
}

