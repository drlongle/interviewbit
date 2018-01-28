/*
Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. 

Hint:
Firstly, we should be able to answer if substring [i,i+1,….j] is palindrome or not in O(1) with pre-computation of O(n^2).

Now try to come up with some DP state which can find minimum cut using above data.
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
#include <unordered_map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

unordered_map<int, int> cache;
vector<vector<bool> > palin_cache;

void expand_palindrome(const string& s, int i, int j)
{
    int ssize = s.size();
    while (i >= 0 && j < ssize && s[i] == s[j])
    {
        palin_cache[i][j] = true;
        --i, ++j;
    }
}

int palindrome_mincut(string s, int index)
{
    unordered_map<int,int>::iterator it = cache.find(index);
    if (it != cache.end())
        return it->second;

    int result = numeric_limits<int>::max();
    int ssize = s.size();
    for (int i = ssize-1; i >= index && result > 1; --i)
    {
        if (!palin_cache[index][i])
            continue;
        if (i == ssize-1)
            result = 0;
        else
        {
            int tempresult = palindrome_mincut(s, i+1);
            if (result > tempresult+1)
                result = tempresult+1;
        }
    }
    
    cache[index] = result;
    return result;
}

bool isPalindrome(string A) {
    int left = 0;
    int right = A.size()-1;
    while(left < right) {
        if(A[left] != A[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

class Solution {
public:
    int minCut(string s);

    int my_minCut(string s) {
        cache.clear();
        int ssize = s.size();
        palin_cache = vector<vector<bool> >(ssize, vector<bool>(ssize, false));
        for (int i = 0; i < ssize; ++i)
        {
            expand_palindrome(s, i, i);
            if (i+1 < ssize && s[i] == s[i+1])
                expand_palindrome(s, i, i+1);
        }
        if (palin_cache[0][s.size()-1]) return 0;
        return palindrome_mincut(s, 0);
    }

    int min_cut_iterative(string s) {
        int ssize = s.size();
        vector<int> cuts(ssize);
        iota(cuts.begin(), cuts.end(), 0);
        for (int i = 1; i < ssize; ++i)
        {
            for (int j = 0; j < i && cuts[i] > 1; ++j)
            {
                if (!palin_cache[i][j])
                    continue;
                if (cuts[i] > cuts[j]+1)
                    cuts[i] = cuts[j]+1;
            }
        }
        return cuts[ssize-1];
    }
};

int Solution::minCut(string A) {
    int n = A.size();
    vector<int> result(n+1);
    result[n] = -1;
    for(int i=n-1;i>=0;i--) {
        result[i] = n-i-1;
        for(int j=i;j<n;j++) {
            if(isPalindrome(A.substr(i, j-i+1))) {
                result[i] = min(result[i], 1 + result[j+1]);
            }
        }
    }
    return result[0];
}

int main()
{
    Solution sol;
    string s;
    int result;
  
    // Expected: 1
    s = "aab";
    result = sol.minCut(s);
    cout << "Result: " << result << endl;

    return 0;
}

