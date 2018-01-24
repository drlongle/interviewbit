/*
Distribute Candy

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:
Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

Sample Input : Ratings : [1 2]
Sample Output : 3

The candidate with 1 rating gets 1 candy and candidate with rating cannot get 1 candy as 1 is its neighbor. So rating 2 candidate gets 2 candies. In total, 2+1 = 3 candies need to be given out.
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
    int my_candy(vector<int> &ratings);

    int candy(vector<int> &ratings) {
        int candiesCnt = 0, curCandy, pos;
        vector<pair<int, int> > valueWithPos; 
        for (int i = 0; i < ratings.size(); i++) {
            valueWithPos.push_back(make_pair(ratings[i], i));
        }
        sort(valueWithPos.begin(), valueWithPos.end());
        vector<int> candies (ratings.size(), 0);
        for (int i = 0; i < valueWithPos.size(); i++) {
            pos = valueWithPos[i].second;
            curCandy = 0;
            if (pos > 0 && ratings[pos - 1] < ratings[pos]) {
                curCandy = candies[pos - 1];
            } 
            if (pos < ratings.size() - 1 && ratings[pos + 1] < ratings[pos]) {
                curCandy = max(curCandy, candies[pos + 1]);
            }
            candies[pos] = curCandy + 1;
            candiesCnt += candies[pos];
        }
        return candiesCnt;
    }

};

int Solution::my_candy(vector<int> &ratings) {
    int length = ratings.size();
    vector<int> left(length, 1);
    for (int i = 1; i < length; ++i)
        if (ratings[i] > ratings[i-1])
            left[i] = left[i-1]+1;
        
    vector<int> right(length, 1);
    for (int i = length-2; i >= 0; --i)
        if (ratings[i] > ratings[i+1])
            right[i] = right[i+1]+1;
        
    int sum = 0; 
    for (int i = 0; i < length; ++i)
        sum += max(left[i], right[i]);
        
    return sum;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> ratings;
    int res;

    ratings = {1, 2};
    res = sol.candy(ratings);
    cout << "Result: " << res << endl;

    return 0;
}

