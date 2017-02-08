/*
Intersection Of Sorted Arrays

Find the intersection of two sorted arrays.
OR in other words,
Given 2 sorted arrays, find all the elements which occur in both the arrays.

Example :
Input : 
    A : [1 2 3 3 4 5 6]
    B : [3 3 5]
Output : [3 3 5]

Input : 
    A : [1 2 3 3 4 5 6]
    B : [3 5]
Output : [3 5]
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
    vector<int> my_intersect(const vector<int> &A, const vector<int> &B);
    vector<int> intersect(vector<int> &A, vector<int> &B) {
        vector<int> intersection;
        int n1 = A.size();
        int n2 = B.size();
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (A[i] > B[j]) {
                j++;
            } else if (B[j] > A[i]) {
                i++;
            } else {
                intersection.push_back(A[i]);
                i++;
                j++;
            }
        }
        return intersection;
    }
};


vector<int> Solution::my_intersect(const vector<int> &A, const vector<int> &B) {
    vector<int> result;
    size_t i_a = 0, i_b = 0;
    while (i_a < A.size() && i_b < B.size()) {
        if (A[i_a] == B[i_b]) {
            result.emplace_back(A[i_a]);
            ++i_a;
            ++i_b;
        }
        else if (A[i_a] < B[i_b]) {
            ++i_a;
        } else {
            ++i_b;
        }
    }
    return result;
}

int main()
{
  Solution sol;
  vector<int> A, B, result;
  
  A = {1, 2, 3, 3, 4, 5, 6};
  B = {3, 3, 5};

  A = {1, 2, 3, 3, 4, 5, 6};
  B = {3, 5};
  
  result = sol.intersect(A,B);
  copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));

  return 0;
}
