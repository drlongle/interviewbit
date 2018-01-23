/*
Tushar's Birthday Bombs

It’s Tushar’s birthday today and he has N friends. Friends are numbered [0, 1, 2, …., N-1] and i-th friend have a positive strength S(i). Today being his birthday, his friends have planned to give him birthday bombs (kicks :P). Tushar’s friends know Tushar’s pain bearing limit and would hit accordingly.
If Tushar’s resistance is denoted by R (>=0) then find the lexicographically smallest order of friends to kick Tushar so that the cumulative kick strength (sum of the strengths of friends who kicks) doesn’t exceed his resistance capacity and total no. of kicks hit are maximum. Also note that each friend can kick unlimited number of times (If a friend hits x times, his strength will be counted x times)

Note:

Answer format = Vector of indexes of friends in the order in which they will hit.
Answer should have the maximum no. of kicks that can be possibly hit. If two answer have the same no. of kicks, return one with the lexicographically smaller.
[a1, a2, …., am] is lexicographically smaller than [b1, b2, .., bm] if a1 < b1 or (a1 = b1 and a2 < b2) … .
Input cases are such that the length of the answer does not exceed 100000.
Example:
R = 11, S = [6,8,5,4,7]

ans = [0,2]
Here, [2,3], [2,2] or [3,3] also give the maximum no. kicks

Hint:
If you are Greedy and want to give the maximum no. of kicks, which friends would you choose to give the kicks?

Greedy works :)

Observations:
Let the index of friend with minimum strength be F. (Take smallest index in case of a tie)

It is obvious that –> Maximum no. of kicks = R/(S[F]).
This is the length of the answer but since we need lexicographically smaller order (according to index), friends whose index is less than the F can also hit provided they do not change the length of the answer. There is also a crucial observation here, we need not consider the friend which have a friend to their left (lesser index) and have lesser than or equal strength than him. (Otherwise we can just take that friend with lesser index instead).

Below is an example to clear the things out:

R = 11, S = [6, 8, 5, 4, 7]
In this case:
Max no. of kicks = 11/4 = 2.
answer = [3,3] (if we do not consider the lexicographic order)
But answer may be [0,3] or [0,2] or [2,3] as they also have the same length. 
Here, only required friends to consider are newS = [6,5,4] as we will rather choose friend with strength 6 than choosing a friend with strength 8, and rather choose any of [6,5,4] than choosing friend with strength 7. (Give it a thought, it’s true because our answer should be lexicographically smallest)

Note that the friend with the minimum strength will be the last element of our newS vector (as newS will be in strict decreasing order)

Algorithm:

Find the max no. of kicks (length of our answer).
Make a new S vector which only takes the friends that can be in the answer.
Iterate through the S vector formed above and see if the friend at consideration can be used instead of the friend with minimum strength.
If he can be successfully used then use him instead of the friend with minimum strength to get a lexicographically smaller answer.
Can you code it?

Suggest EditsClose

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
    vector<int> my_solve(int limit, vector<int> &nums);
    vector<int> solve(int limit, vector<int> &nums);
};

vector<int> Solution::my_solve(int limit, vector<int> &nums) {
    vector<int> res;
    if (nums.empty()) return res;

    vector<pair<int,int>> S;
    int min = nums[0];
    S.emplace_back(0, min);

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < min) {
            S.emplace_back(make_pair(i, nums[i]));
            min = nums[i];
        }
    }
    int length = limit/min;
    res = vector<int>(length, S.back().first);
    int sum = length * S.back().second;
    int j = 0;
    for (int i = 0; i < S.size(); ++i) {
        while (sum + S[i].second - min <= limit && j < res.size()) {
            res[j++] = S[i].first;
            sum += S[i].second - min;
        }
    }

    return res;
}

#define F first
#define S second

vector<int> Solution::solve(int A, vector<int>& B){
	// newB -> only those strengths which are useful
	// pair {i,j} -> i = original index of the person, j = strength
	vector<pair<int, int> > newB;
	
	int prev = INT_MAX;
	for(int i=0; i<B.size(); i++){
		if(B[i] < prev){
			newB.push_back({i, B[i]});
			prev = B[i];
		} 
	}
	
	int n = newB.size();
	
	vector<int> ans;
	
	int R = A;
	int temp = newB[n-1].second;   //smallest strength
	int i=0;
	
	
	while(i<n){
		// check if the current person can hit and if he can hit
		// would he change the answer or not
		if(R >= newB[i].S && (1 + (R-newB[i].S)/temp) == R/temp){
			ans.push_back(newB[i].F);
			R -= newB[i].S;
		} 
		else i++;
	}
	
	return ans;
}

int main(int argc, const char* argv[])
{
    Solution sol;

    int limit;
    vector<int> nums, res;

    limit = 11;
    nums = {6,8,5,4,7};

    //limit = 10;
    //nums = { 8, 8, 6, 5, 4 };

    //limit = 9383;
    //nums = { 17786, 11924, 22802, 13344, 10395, 10501, 16658, 16430, 2371, 15036, 18699, 20068, 22772, 13935, 5549, 8435, 14181, 5745, 5220, 20377, 2576, 6438, 15791, 21539, 22871, 15132, 24076, 3144, 13938, 4811, 9031, 23067, 8078, 23176, 11402, 18465, 20, 3051, 1238, 2382, 9430, 19928, 13793, 23546, 207, 19333, 23324, 14379, 16422, 3535, 1100, 18989, 9965, 16882, 6871, 24179, 7005, 22290, 2314, 20934, 2093, 11336, 10345, 1514, 855, 21738, 11322, 866, 16133, 3904, 19591, 554, 23823, 8376, 15443, 15373, 19052, 13759, 21096, 1817, 17285, 22187, 20797, 18593, 5412, 2660 };

    res = sol.solve(limit, nums);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}

