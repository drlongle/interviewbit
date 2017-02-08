/*
Rearrange Array

Rearrange a given array so that Arr[i] becomes Arr[Arr[i]] with O(1) extra
space.

Hint:
If you had extra space to do it, the problem will be very easy.
Store a copy of Arr in B.

And then for every element, do Arr[i] = B[B[i]]

Lets restate what we just said for extra space :

If we could somehow store 2 numbers in every index ( that is, Arr[i] can
contain the old value, and the new value somehow ), then the problem becomes
very easy. NewValue of Arr[i] = OldValue of Arr[OldValue of Arr[i]].

Now, we will do a slight trick to encode 2 numbers in one index. This trick
assumes that N * N does not overflow.

1) Increase every Array element Arr[i] by (Arr[Arr[i]] % n)*n.
2) Divide every element by N.

Given a number as
A = B + C * N if ( B, C < N ) A % N = B A / N = C

We use this fact to encode 2 numbers into each element of Arr.
*
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
    void my_arrange(vector<int> &A);
    void arrange(vector<int> &Vec) {
        int N = Vec.size();
        for(int i = 0; i < N; ++i) {
            Vec[i] = Vec[i] + (Vec[Vec[i]]%N) * N;
        }

        for(int i = 0; i < N; ++i) {
            Vec[i] = Vec[i] / N;
        }
    }
};

void Solution::my_arrange(vector<int> &A) {
    int size = static_cast<int>(A.size());
    if (!size) return;

    for (int i = 0; i < size; ++i)
    {
        if (A[i] >= size)
            continue;

        int next_index, next_value, curr_index = i;
        int temp = A[i];
        while (true) {
            next_index = A[curr_index];
            next_value = A[next_index];

            if (next_index >= size)
                next_index -= size;
            A[curr_index] = next_value >= size ? next_value : next_value+size;
            if (next_index == i)
                break;
            curr_index = next_index;
        }
        A[curr_index] = temp + size;
    }

    for (int i = 0; i < size; ++i)
        A[i] -= size;
}

int main()
{
    Solution sol;
    vector<int> data;

    // Expected output:  3 4 2 0 1
    data = { 4, 0, 2, 1, 3 };

    sol.arrange(data);
    copy(data.begin(), data.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}
