/*
Seats

There is a row of seats. Assume that it contains N seats adjacent to each other. There is a group of people who are already seated in that row randomly. i.e. some are sitting together & some are scattered.

An occupied seat is marked with a character 'x' and an unoccupied seat is marked with a dot ('.')

Now your target is to make the whole group sit together i.e. next to each other, without having any vacant seat between them in such a way that the total number of hops or jumps to move them should be minimum.

Return minimum value % MOD where MOD = 10000003

Example
Here is the row having 15 seats represented by the String (0, 1, 2, 3, ......... , 14) -

              . . . . x . . x x . . . x . .

Now to make them sit together one of approaches is -
              . . . . . . x x x x . . . . .

Following are the steps to achieve this -
1 - Move the person sitting at 4th index to 6th index -  
    Number of jumps by him =   (6 - 4) = 2

2 - Bring the person sitting at 12th index to 9th index - 
    Number of jumps by him = (12 - 9) = 3

So now the total number of jumps made = 
    ( 2 + 3 ) % MOD = 
    5 which is the minimum possible jumps to make them seat together.

There are also other ways to make them sit together but the number of jumps will exceed 5 and that will not be minimum.

For example bring them all towards the starting of the row i.e. start placing them from index 0. 
In that case the total number of jumps will be 
    ( 4 + 6 + 6 + 9 )%MOD 
    = 25 which is very costly and not an optimized way to do this movement

Hint : Is it possible to use the median position somehow ?

Are you getting “Wrong Answer” on time complexity check ? Did you miss taking mod from MOD = 10000003

Lets take an exmaple: string :  .x..x..x.
positions where x are present {1, 4, 7}
Median is 4. So we will move all x near our median. 1st person would need to jump 2 steps and 3rd person would also need to jump 2 steps. Total answer = 4. 

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

const int MOD = 10000003;

class Solution {
public:
    int seats(string setting);

};

int Solution::seats(string str) {
    int N = str.size();
    vector<int> Pos;
    for(int i = 0; i < N; ++i) {
        if(str[i] == 'x')
            Pos.push_back(i);
    }

    int n = Pos.size();
    if(n == 0)
        return 0;

    int mid = n / 2;
    int median = n & 1 ? Pos[mid] : (Pos[mid] + Pos[mid - 1])/2;
    int ans = 0;
    int empty = str[median] == 'x' ? median - 1 : median;
    for(int i = median - 1; i >= 0; --i) {
        if(str[i] == 'x') {                
            ans += empty - (i);
            if(ans >= MOD)
                ans %= MOD;
            empty--;
        }
    }

    empty = median + 1;
    for(int i = median + 1; i < N; ++i) {
        if(str[i] == 'x') {
            ans += (i) - empty;
            if(ans >= MOD)
                ans %= MOD;
            empty++;
        }
    }

    return ans;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    string setting;
    int res;

    // Expected: 5
    setting = "....x..xx...x..";

    // Expected: 4
    //setting = ".x..x..x.";

    // Expected: 5
    //setting = ".x.x.x..x";

    // Expected: 12 
    //setting = "x.......x.....x";

    // Expected: 1
    //setting = "............x.x";

    // Expected: 13
    setting = "x.............x";

    // Expected: 79
    setting = "xx.....xx.x..xxxx..xxxx.xx..xx..x.xxxx";

    res = sol.seats(setting);
    cout << "Result: " << res << endl;

    return 0;
}

