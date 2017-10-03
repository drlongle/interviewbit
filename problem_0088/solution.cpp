/*
Shortest common superstring
Given a set of strings. Find the length of smallest string which
has all the strings in the set as substring

Constraints:
1) 1 <= Number of strings <= 18
2) Length of any string in the set will not exceed 100.

Example:
Input: ["abcd", "cdef", "fgh", "de"]
Output: 8 (Shortest string: "abcdefgh")
*/

#include <algorithm>
#include <array>
#include <bitset>
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

#define INF 1<<20
#define N 18

class Solution {
public:
    int solve(vector<string> &strs); 
    int my_solve(vector<string> &strs); 
};

unordered_map<int, string> cache;

void set_bit(int& bits, int index)
{
    bits |= 1 << index;
}

void clear_bit(int& bits, int index)
{
    bits &= ~(1 << index);
}

bool test_bit(int bits, int index)
{
    return bits & (1 << index);
}

int count_bits(int bits)
{
    int res = 0;
    for (int i = 0; i < N; ++i)
        res += test_bit(bits, i);
    return res;
}

string superstr(const string& s1, const string& s2)
{
    if (s2.empty())
        return s1;
    int i, j;
    for (i = 0; i < s1.size(); ++i) {
        bool suffix = true;
        for (j = 0; suffix && i + j < s1.size() && j < s2.size(); ++j) {
            if (s1[i+j] != s2[j])
                suffix = false;
        }
        if (suffix)
            return s1 + s2.substr(j);
    }

    return s1 + s2;
}

string superstring(const string& s1, const string &s2)
{
    string s12 = superstr(s1, s2);
    string s21 = superstr(s2, s1);
    return (s12.size() <= s21.size()) ? s12 : s21;
}

string superstring(vector<string>& strs, int bits)
{
    auto it = cache.find(bits);
    if (it != cache.end())
        return it->second;
    int bitcount = count_bits(bits);
    if (bitcount == 1) {
        for (int i = 0; i < strs.size(); ++i)
            if (test_bit(bits, i))
                return strs[i];
    }
    if (bitcount == 2) {
        vector<string*> ptrs;
        for (int i = 0; i < strs.size(); ++i)
            if (test_bit(bits, i))
                ptrs.emplace_back(&strs[i]);
        cache[bits] = superstring(*ptrs[0], *ptrs[1]);
        return cache[bits];
    } else {
        string res;
        for (int i = 0; i < strs.size(); ++i) {
            if (test_bit(bits, i)) {
                clear_bit(bits, i);
                string temp = superstring(superstring(strs, bits), strs[i]);
                set_bit(bits, i);
                if (res.empty() || res.size() > temp.size())
                    res = temp;
            }
        }
        cache[bits] = res;
        return res;
    }
}

int Solution::my_solve(vector<string>& strs)
{
    int bits = (1 << N) - 1;
    cache.clear();
    return superstring(strs, bits).size();
}

//Set the global variables
int targetMask;
int nonOverlapLen[N+2][N+2];
int dp[N][(1<<N) + 10];

// This can be done faster using KMP algorithm
//and some preprocessing
int combineString(vector<string> &words, int a, int b){
	/*
	Let's say s1 = words[a] and s1 = words[b].
	
	If we append string s2 to the solution, then as string s1 is already
	added, we would need to add only the characters of string words[b] that are
	not overlapping with the solution.
	lenToADD = len(s2)-len(suffix of s1 which is also a prefix of s2);
	
	e.g.: s1 = "lara", s2 = "raghav"
	      Now in the previous step, we added s1 to solution and let's say our solution
	      at the time looks like "brilara" [made from strings "brila" and "lara"],
	      if we add "raghav" to the solution, the only characters to be added are "ghav"
	      and new solution = "brilaraghav"
	*/
	
	//Only 1 string in the mask 
	if(a == -1){
		return words[b].size();
	}
  	
  	//Check if already calculated the ans
	if(nonOverlapLen[a][b] != -1){
		return nonOverlapLen[a][b];
	}
  	
  	//Calculate the answer if not already calculated
	for(int i=0; i<words[a].size(); ++i){
		bool suffix = true;
		for(int j=0; j<words[b].size()&& i+j<words[a].size() && suffix; ++j){
			if(words[a][i+j] != words[b][j]) suffix = false;
		}
		
		if(suffix){
			int overlap = words[a].size()-i;
			nonOverlapLen[a][b] = words[b].size() - overlap;
			return nonOverlapLen[a][b];
		}
	}
	
	nonOverlapLen[a][b] = words[b].size();
	return nonOverlapLen[a][b];
}

//Main function to find the optimal solution
int findOptimal(vector<string> &words, int last, int mask){
	//mask --> Set of strings that are considered for the solution.
	//last --> String that we added into the mask the last time
	//dp[i][mask] --> optimal answer for set of strings corresponding to mask(1's in mask) if the
	// last added string in mask is i-th string
	
	if(mask == targetMask){
		//We considered all strings into the solution
		dp[last+1][mask] = 0;
		return dp[last+1][mask];
	}
	
	//Check if we solved this sub problem before
 	if(dp[last + 1][mask] != -1){
 		return dp[last+1][mask];
 	}
	
	// Calculate the answer if not already calculated
	int ans = INF;
	
	for(int i=0; i<words.size(); ++i){
		//Check if i-th word is already considered or not
		if(!((mask>>i)&1)){
			ans = min(ans, findOptimal(words, i, mask|(1<<i)) + combineString(words, last, i));
		}
	}
    
    //Memoization step
    dp[last + 1][mask] = ans;
    
    return ans;
}

int Solution::solve(vector<string>& A){
	int n = A.size();
	
	// Check the strings which are completely overlapping with some other string
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i!=j && A[i].find(A[j]) != string::npos) A[j] = "";
		}
	}
	
	//Make a new vector of only the strings which are not completely overlapping
	//with some other string

 	vector<string> newA;
 	for(int i=0; i<n; i++){
 		if(A[i] != "") newA.push_back(A[i]);
 	}
  
  	//initialize the required arrays
	memset(nonOverlapLen, -1, sizeof(nonOverlapLen));
	memset(dp, -1, sizeof(dp));
	  
	//Set the mask initially to all 0's
    int mask = 0;
	
	//Set the target mask
    targetMask = (1<<newA.size())-1;
    
    //Find the length of optimal solution
    int ans = findOptimal(newA, -1, mask);
    
    return ans;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<string> strs;

    // Expected: "abcdefgh" --> 8
    strs = {"abcd", "cdef", "fgh", "de"};

    // Expected: 108
    //strs = {"nejqokaplfbrqe", "cjqpuidbwnbaml", "naiwqahtpubspt", "jvidmdlrhjhkjt", "pjvyhpbqlsm", "lcgkneuqsydk", "mruvnqlapmjhp", "sioft", "nehtaxnb", "xlpsgn"};

    // Expected: 39
    //strs = {"qfgxmuvgfaj", "lfvenhyuhuor", "osamibdnj", "beyhkbso"};

    // Expected: 45
    //strs = {"cpsklryvmcp", "nbpbwllsrehfmx", "kecwitrsglre", "vtjmxypu"};

    // Expected: 106
    //strs = {"wpssfoqald", "cuhem", "pvbwfcdd", "ucxunvkiqrxhrl", "dnimsuxksb", "xdmexhgxevtrfm", "fweqjjgrxbnvni", "wjflpfvxdauarc", "ehjiatr", "lpkboxmpxvujn"};
    /*
    for (size_t i = 0; i < strs.size(); ++i)
        for (size_t j = 0; j < strs.size(); ++j)
        {
            string s = superstr(strs[i], strs[j]);
            cout << strs[i] << ", " << strs[j] << " -> " << s << endl;
        }
    */

    cout << "Result: " << sol.my_solve(strs) << endl;
    return 0;
}

