/*
Sum Of Fibonacci Numbers

How many minimum numbers from fibonacci series are required such that sum of numbers should be equal to a given Number N?
Note : repetition of number is allowed.

Example:

N = 4
Fibonacci numbers : 1 1 2 3 5 .... so on
here 2 + 2 = 4 
so minimum numbers will be 2 
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
    int my_fibsum(int A);
    int fibsum(int N)
    {
        vector<int> Fib;
        Fib.push_back(1);
        Fib.push_back(1);
        for(int i = 2; Fib[i - 1] < N; ++i) {
            int data = Fib[i - 1] + Fib[i - 2];
            Fib.push_back(data);
        }
        
        int ans = 0;
        int index = Fib.size() - 1;
        while (N > 0) {
            // find the largest fibonacci less than N.
            while (Fib[index] > N) index--;
            N -= Fib[index];
            ans++;
        }
        return ans;
    }

};

int Solution::my_fibsum(int A) {
    set<int> fibs;
    int f1, f2, temp;
    f1 = f2 = 1;
    fibs.emplace(f1);
    do {
        temp = f1 + f2;
        f2 = f1;
        f1 = temp;
        fibs.emplace(f1);
    } while (f1 < A);

    int count = 0;
    while (A > 0) {
        auto it = fibs.lower_bound(A);
        if (*it > A)
            --it;
        A -= *it;
        ++count;
    }

    return count;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int A, res;

    cout << "Enter a number: ";
    cin >> A;
    res = sol.fibsum(A);
    cout << "Result: " << res << endl;

    return 0;
}

