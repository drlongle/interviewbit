/*
Median of Array

There are two sorted arrays A and B of size m and n respectively.

Find the median of the two sorted arrays ( The median of the Cay formed by
merging both the arrays). The overall run time complexity should be
O(log (m+n)).

Sample Input:
A : [1 4 5]
B : [2 3]

Sample Output:
3
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
    double my_findMedianSortedArrays(const vector<int> &A,
        const vector<int> &B);

    double findMedianSortedArrays(const vector<int> &A,
        const vector<int> &B) {
        int m = A.size(), n = B.size();
        if (m > n) return findMedianSortedArrays(B, A);
        int imin, imax, i, j;
        imin = 0;
        imax = m;
        while (imin <= imax) {
            i = (imin + imax)/2;
            j = (m+n+1)/2 - i;
            if (j > 0 && i < m && B[j - 1] > A[i]) {
                imin = i + 1;
            } else if (i > 0 && j < n && A[i - 1] > B[j]) {
                imax = i - 1;
            } else {
                // Figure out median now.
                int median1 = 0, median2 = 0;
                if (i == 0) {
                    median1 = B[j - 1];
                } else if (j == 0) {
                    median1 = A[i - 1];
                } else {
                    median1 = max(A[i - 1], B[j - 1]);
                }
                if ((m+n) % 2 == 1) {
                    return 1.0 * median1;
                }
                if (i == m) {
                    median2 = B[j];
                } else if (j == n) {
                    median2 = A[i];
                } else {
                    median2 = min(A[i], B[j]);
                }
                return 1.0 * (median1 + median2) / 2.0;
            }
        }
        return -1.0;
    }
};

  /*
  Note: a should point to the shorter array so that (*b)[j] is always a valid
  element, i.e., j < n.

  When (m+n) is even, j = (m+n)/2 -i
  When (m+n) is odd, j = (m+n+1)/2 -i
  For both cases, we can write j = (m+n+1)/2 -i
  */

double Solution::my_findMedianSortedArrays(const vector<int> &A,
    const vector<int> &B) {
    int m = static_cast<int>(A.size());
    int n = static_cast<int>(B.size());

    const vector<int>* a = &A;
    const vector<int>* b = &B;
    if (m > n) {
        swap(m,n);
        swap(a,b);
    }

    int imin = 0;
    int imax = m-1;

    int ix, jx;
    ix = (imin + imax) / 2;
    jx = ((m + n + 1) / 2) - ix;
    while (imin <= imax) {
        int i = (imin + imax) / 2;
        int j = ((m + n + 1) / 2) - i;
        if (j <= 0 || (*b)[j - 1] > (*a)[i]) {
           imin = i + 1;
           ix = i+1;
           jx = ((m + n + 1) / 2) - ix;
        } else if (i <= 0 || i > m || (*a)[i - 1] > (*b)[j])
            imax = i - 1;
        else {
            ix = i;
            jx = ((m + n + 1) / 2) - ix;
            break;
        }
    }

    if ((m + n) & 0x1)
        return max(ix > 0 && ix<=m ? (*a)[ix-1] : numeric_limits<int>::min(),
            jx > 0 && jx <= n ? (*b)[jx - 1] : numeric_limits<int>::min());
    else {
        double first = max(ix > 0 &&
            ix <= m ? (*a)[ix - 1] : numeric_limits<int>::min(),
            jx > 0 && jx <= n ? (*b)[jx - 1] : numeric_limits<int>::min());
        double second = min(ix < m ? (*a)[ix] : numeric_limits<int>::max(),
            jx < n ? (*b)[jx] : numeric_limits<int>::max());

        return (first + second) / 2;
    }
}

int main()
{
    Solution sol;
    vector<int> A, B;

    A = { -50, -41, -40, -19, 5, 21, 28 };
    B = { -50, -21, -10 };

    cout << "Result: " << sol.findMedianSortedArrays(A,B) << endl;

    return 0;
}
