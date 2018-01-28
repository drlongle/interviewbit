/*
Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
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
    int my_minDistance(string word1, string word2)
    {
        int size1 = word1.size();
        int size2 = word2.size();
        if (!size1 || !size2)
            return abs(size1 - size2);
        vector<vector<int>> dist = vector<vector<int>>(size1+1,
            vector<int>(size2+1));

        for (int i = 0; i <= size1; ++i)
            dist[i][0] = i;
        for (int i = 0; i <= size2; ++i)
            dist[0][i] = i;

        for (int i = 0; i < size1; ++i)
            for (int j = 0; j < size2; ++j)
            {
                if (word1[i] == word2[j])
                    dist[i+1][j+1] = dist[i][j];
                else
                    dist[i+1][j+1] = 1 +
                        min(min(dist[i][j+1], dist[i+1][j]), dist[i][j]);
            }
        return dist[size1][size2]; 
    }

    int minDistance(string word1, string word2) {
        // DP talbe, i is the position in word1, and j is the position in word2
        vector<vector<int>> distance(word1.length() + 1, vector<int>(word2.length() + 1, 0));

        // when i or j=0 means empty string, the distance is the length of another string
        for (int i = 0; i < distance.size(); i++) {
            for (int j = 0; j < distance[0].size(); j++) {
                if (i == 0)
                    distance[i][j] = j;
                else if (j == 0)
                    distance[i][j] = i;
            }
        }

        // if word1[i] == word2[j], then the distance of i and j is the previous i and j
        // otherwise we either replace, insert or delete a char
        // when insert a char to word1 it means we are trying to match word1 at i-1 to word2 at j
        // when delete a char from word1 it equals to insert a char to word2, which
        // means we are trying to match word1 at i to word2 at j-1
        // when replace a char to word1, then we add one step to previous i and j
        for (int i = 1; i < distance.size(); i++) {
            for (int j = 1; j < distance[0].size(); j++) {
                if (word1[i - 1] == word2[j - 1])
                    distance[i][j] = distance[i - 1][j - 1];
                else
                    distance[i][j] = 1 + min(distance[i - 1][j - 1], min(distance[i - 1][j], distance[i][j - 1]));
            }
        }

        return distance[word1.length()][word2.length()];    
    }

};

int main()
{
    Solution sol;
    string word1, word2;
    word1= "cat";
    word2= "dog";
    cout << "Result: " << sol.minDistance(word1,word2) << endl;

    return 0;
}

