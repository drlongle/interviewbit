/*
Interleaving Strings

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",
When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false. 

Hint:
Let n,m be the length of s1 and s2 respectively.
You need to check if using portion upto n and portion upto m if s3 can be formed or not.
So basically last character of s3 should be something from nth postion of s1 or mth position of s2. How can you recursively simulate this?

Lets again look at the bruteforce solution for this question. 
Given the string S1, S2, S3, the first character of S3 has to match with either the first character of S1 or S2. If it matches with first character of S1, we try to see if solution is possible with remaining part of S1, all of S2, and remaining part of S3. Then we do the same thing for S2.

The pseudocode might look something like this :

    bool isInterleave(int index1, int index2, int index3) {
                    // HANDLE BASE CASES HERE
        
        bool answer = false; 
        if (index1 < s1.length() && s1[index1] == s3[index3]) answer |= isInterleave(index1 + 1, index2, index3 + 1);
        if (index2 < s2.length() && s2[index2] == s3[index3]) answer |= isInterleave(index1, index2 + 1, index3 + 1);
        
        return answer;
    }
Again, index1, index2, and index3 can only take S1.length(), S2.length() and S3.length() possibilities respectively. Can you think of a memoization solution using the observation ?

BONUS: Can you eliminate one of the state i.e. come up with something having only two arguments.
*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <climits>
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

#include <string.h>

using namespace std;

struct Entry {
    Entry(size_t i1, size_t i2, size_t i3) : index1(i1), index2(i2), index3(i3)
    {

    }
    size_t index1, index2, index3;
};

class Solution {
public:

    bool simple_checks(string& s1, string& s2, string& s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        if (s3.size() == 0) return true;
        if (s1.size() == 0) return s2.compare(s3) == 0;
        if (s2.size() == 0) return s1.compare(s3) == 0;
        if (s3.back() != s1.back() && s3.back() != s2.back()) return false;

        map<char, int> count;
        map<char, int>::iterator it;
        for (const auto& c : s1) {
            it = count.find(c);
            if (it != count.end()) it->second++;
            else count[c] = 1;
        }
        for (const auto& c : s2) {
            it = count.find(c);
            if (it != count.end()) it->second++;
            else count[c] = 1;
        }
        for (const auto& c : s3) {
            it = count.find(c);
            if (it != count.end()) {
                it->second -= 1;
                if (it->second == 0) count.erase(it);
            }
            else
                return false;
        }

        return true;
    }

    bool my_isInterleave(string s1, string s2, string s3) {
        if (!simple_checks(s1,s2,s3)) return false;
            return isInterleave_iterative(s1,s2,s3);
    }

    bool isInterleave_recursive(string& s1, size_t index1, string& s2,
        size_t index2,  string& s3, size_t index3)
    {
        if (index1 == s1.size())
            return s2.compare(index2, s2.size()-index2, s3, index3,
                s3.size()-index3) == 0;
        if (index2 == s2.size())
            return s1.compare(index1, s1.size()-index1, s3, index3,
                s3.size()-index3) == 0;

        if (s1[index1] == s3[index3])
            if (isInterleave_recursive(s1, index1+1, s2, index2, s3, index3+1))
                return true;
        if (s2[index2] == s3[index3])
            if (isInterleave_recursive(s1, index1, s2, index2+1, s3, index3+1))
                return true;

        return false;
    }

    bool isInterleave_iterative(string s1, string s2, string s3) {
        size_t size1 = s1.size();
        size_t size2 = s2.size();
        size_t size3 = s3.size();
        if (size1 + size2 != size3)
            return false;

        queue<Entry> entries;
        entries.emplace(0,0,0);
        set<pair<int,int>> hash;
        while(entries.size()) {
            Entry& e = entries.front();
            if (e.index1 == size1 && e.index2 == size2 && e.index3 == size3)
                return true;
            if (e.index1 == size1)
                if (s2.compare(e.index2, size2-e.index2, s3, e.index3,
                    size3-e.index3) == 0)
                    return true;
            if (e.index2 == size2)
                if (s1.compare(e.index1, size1-e.index1, s3, e.index3,
                    size3-e.index3) == 0)
                    return true;

            if (s1[e.index1] == s3[e.index3])
            {
                pair<int,int> p(e.index1+1,e.index2);
                if (hash.find(p) == hash.end()) {
                    hash.emplace(p);
                    entries.emplace(e.index1+1, e.index2, e.index3+1);
                }
            }

            if (s2[e.index2] == s3[e.index3])
            {
                pair<int,int> p(e.index1,e.index2+1);
                if (hash.find(p) == hash.end()) {
                    hash.emplace(p);
                    entries.emplace(e.index1, e.index2+1, e.index3+1);
                }
            }
            entries.pop();
        }
  
        return false;
    }


    bool isInterleave(int index1, int index2, int index3) {
        if (index1 == s1.length() && index2 == s2.length()) {
            return index3 == s3.length();
        }
        if (index3 >= s3.length()) return false;

        if (memo[index1][index2][index3] != -1) return memo[index1][index2][index3];
        bool answer = false; 
        if (index1 < s1.length() && s1[index1] == s3[index3]) answer |= isInterleave(index1 + 1, index2, index3 + 1);
        if (index2 < s2.length() && s2[index2] == s3[index3]) answer |= isInterleave(index1, index2 + 1, index3 + 1);
        return memo[index1][index2][index3] = answer;
    }

    bool isInterleave(string S1, string S2, string S3) {
        s1 = S1; 
        s2 = S2;
        s3 = S3;
        memset(memo, -1, sizeof(memo));
        if (S3.length() != S1.length() + S2.length()) return false;
        return isInterleave(0, 0, 0);
    }
 

private:
    string s1, s2, s3;
    short memo[101][101][101];

};

int main()
{
    Solution sol;
    string s1, s2, s3;
    // expected true;
    s1 = "aabcc";
    s2 = "dbbca";
    s3 = "aadbbcbcac",
    cout << "Result: " << boolalpha << sol.isInterleave(s1,s2,s3) << endl;

    return 0;
}
