/*
Max Continuous Series of 1s

You are given an array of 1s and 0s. And you are given an integer M, which
signifies number of flips allowed. Find the position of zeros which when
flipped will produce maximum continuous series of 1s. For this problem, return
the indices of maximum continuous series of 1s in order.

Example:

Input : 
Array = {1 1 0 1 1 0 0 1 1 1 } 
M = 1

Output : 
[0, 1, 2, 3, 4] 

If there are multiple possible solutions, return the sequence which has the
minimum start index.

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
    vector<int> my_maxone(vector<int> &A, int B) ;

    vector<int> maxone(vector<int> Vec, int M)
    {
        int N = Vec.size();
        int i = 0;
        int j = 0;
        int max_len = 0;
        int cnt = 0;
        vector<int> ans;
	
	int ans_start = 0; 
	int ans_end = 0;

        while(i < N) {
            if(cnt + (Vec[i] == 0) > M) {
                int temp_len = (i - j); // length from j to i - 1. 
                if(temp_len > max_len) {
                        max_len = temp_len;
                        ans_start = j;
			ans_end = i - 1;
                }

                while(i >= j && cnt + (Vec[i] == 0) > M) {
                    cnt -= (Vec[j] == 0);
                    j++;
                }
                cnt += (Vec[i] == 0);
            } else {
                cnt +=(Vec[i] == 0);
            }
            i++;
        }

        int temp_len = (i - j);
        if(temp_len > max_len) {
            temp_len = max_len;
	    ans_start = j;
	    ans_end = i - 1;
        }

	for (int ele = ans_start; ele <= ans_end; ele++) {
		ans.push_back(ele);
	}
	return ans;
    }
};

vector<int> Solution::my_maxone(vector<int> &A, int B) {
    int index=0, length= 0, nsize = A.size();
    int fast = 0, slow=0, changes = B;

    while ( fast < nsize) {
        while ((A[fast] || (!A[fast] && changes > 0)) && fast < nsize) {
            if (!A[fast])
                --changes;
            ++fast;
        }

        int newlength = fast - slow;
        if (newlength > length) {
            index = slow;
            length = newlength;
        }

        while (slow < fast && !changes) {
            if (!A[slow])
                ++changes;
            ++slow;
        }
        if (slow == fast && !B) {
            ++fast;
            ++slow;
        }
    }

    vector<int> result(length);
    iota(result.begin(), result.end(), index);

    return result;
}

int main()
{
    Solution sol;
    vector<int> A, result;
    int M;

    A = {1, 1, 0, 1, 1, 0, 0, 1, 1, 1 };
    M = 1;

    result = sol.maxone(A,M);
    cout << "Result: " << result.size() << endl;
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}
