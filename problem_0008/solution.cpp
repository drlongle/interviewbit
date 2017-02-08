/*
Prime Sum

Given an even number (greater than 2), return two prime numbers whose sum will
be equal to given number.

NOTE A solution will always exist. read Goldbach's conjecture

Example:

Input : 4
Output: 2 + 2 = 4

If there are more than one solutions possible, return the lexicographically
smaller solution.

If [a, b] is one solution with a <= b,
and [c,d] is another solution with c <= d, then

[a, b] < [c, d] 

If a < c OR a==c AND b < d.
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
    vector<int> my_primesum(int A);
    vector<int> primesum(int N) {

        // Generate isPrime List less equal than N
        vector<bool> isPrime(N + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;

        // Sieve of Erastothenes
        for(int i = 2; i <= N; i++) {
            if (!isPrime[i]) continue;
            if (i > N / i) break;
            for (int j = i * i; j <= N; j += i) isPrime[j] = false;
        }

        for(int i = 2; i <= N; ++i) {
            if(isPrime[i] && isPrime[N - i]) {
                vector<int> ans;
                ans.push_back(i);
                ans.push_back(N - i);
                return ans;
            }
        }

        vector<int> ans;
        return ans;
    }
};

vector<int> Solution::my_primesum(int A) {
    vector<int> result;
    int size = A+1;
    vector<bool> flags(size, true);
    flags[0] = false;
    flags[1] = false;
    for (int i = 2; i <= A; ++i)
    {
        if (flags[i]) {
            for (int j = 2; i*j <= size; ++j) {
                flags[i*j] = false;
            }
        }
    }

    for (int i = 2; i <= A; ++i) {
        if (flags[i] && flags[A-i])
            return {i,A-i};
    }
    return result;
}

int main()
{
    Solution sol;
    int input;

    cout << "Input: ";
    cin >> input;
    vector<int> result = sol.primesum(input);

    cout << "Result: " << result.front() << ", " << result.back() << endl;
    return 0;
}
