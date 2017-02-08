/*
Wave Array

Given an array of integers, sort the array into a wave like array and return
it. In other words, arrange the elements into a sequence such that
a1 >= a2 <= a3 >= a4 <= a5.....

Example

Given [1, 2, 3, 4]

One possible answer : [2, 1, 4, 3]
Another possible answer : [4, 1, 3, 2]

NOTE : If there are multiple answers possible, return the one thats
lexicographically smallest. So, in example case, you will return [2, 1, 4, 3].

Can you solve this problem in O(N) ?? Hint: we can find median of array in O(N).
Now, can you define a relation between median of the array and the wave formed
array?

*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <string.h>

using namespace std;

class Solution {
public:
    vector<int> wave(vector<int> &A) ;
};

vector<int> Solution::wave(vector<int> &A) {
    vector<int> result;
    copy(A.begin(), A.end(), back_inserter(result));
    sort(result.begin(), result.end());
    int size = static_cast<int>(result.size());
    for (int i = 0; i < size; i+=2)
    {
        if (i+1 < size)
            swap(result[i], result[i+1]);
    }
    return result;
}

int main()
{
    Solution sol;
    vector<int> input;

    input = {1,2,3,4};
    input = {1,2,3,4,5,6,7,8,9,10};
    vector<int> result = sol.wave(input);
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}
