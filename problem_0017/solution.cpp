/*
Search for a Range

Given a sorted array of integers, find the starting and ending position of a
given target value. Your algorithm's runtime complexity must be in the order
of O(log n). If the target is not found in the array, return [-1, -1].

Example:
Given [5, 7, 7, 8, 8, 10]
and target value 8,
return [3, 4].
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
    vector<int> my_searchRange(const vector<int> &A, int B);
    vector<int> searchRange(const vector<int> &A, int target) {
        int n = A.size();
        int i = 0, j = n - 1;
        vector<int> ret(2, -1);
        // Search for the left one
        while (i < j)
        {
            int mid = (i + j) /2;
            if (A[mid] < target) i = mid + 1;
            else j = mid;
        }
        if (A[i]!=target) return ret;
        else ret[0] = i;

        // Search for the right one
        j = n-1;  // We don't have to set i to 0 the second time.
        while (i < j)
        {
            int mid = (i + j) /2 + 1;   // Make mid biased to the right
            if (A[mid] > target) j = mid - 1;  
            else i = mid; // So that this won't make the search range stuck.
        }
        ret[1] = j;
        return ret; 
    }
};

vector<int> Solution::my_searchRange(const vector<int> &A, int B)
{
    int begin = 0, end = A.size() -1;
    if (end < 0)
        return {-1,-1};
    if (!end) {
        if (A[0] == B)
            return {0,0};
        else
            return {-1,-1};
    }
    int mid;
    while (begin < end) {
        mid = begin + ((end-begin)>>1);
        if (A[mid] == B) {
            begin = mid;
            break;
        }
        if (A[mid] < B)
            begin = mid+1;
        else
            end = mid-1;
    }
    if (A[begin] != B)
        return {-1,-1};
    int low = begin, high = begin;
    begin = 0;
    end = low;
    while (begin < end) {
        if (begin+1 == end) {
            if (A[begin] == B)
                end = begin;
            else
                begin = end;
        }
        else {
            mid = begin +((end-begin)>>1);
            if (A[mid] == B)
                end = mid;
            else
                begin = mid+1;
        }
    }
    if (A[begin] == B)
        low = begin;

    begin = high;
    end = A.size()-1;
    while (begin < end) {
        if (begin+1 == end) {
            if (A[end] == B)
                begin = end;
            else
                end = begin;
        }
        else {
            mid = begin +((end-begin)>>1);
            if (A[mid] == B)
                begin = mid;
            else
                end = mid-1;
        }
    }
    if (A[begin] == B)
        high = begin;
    return {low,high};
}

int main()
{
    Solution sol;
    vector<int> nums, result;
    int target;
  
    nums = {1};
    target = 1;
  
    result = sol.searchRange(nums,target);
    cout << "Result: " << result[0] << ", " << result[1] << endl;

    return 0;
}
