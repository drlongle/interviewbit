/*
Knight On Chess Board

Knight movement on a chess board

Given any source point and destination point on a chess board, we need to find whether Knight can move to the destination or not.

Note that a knight cannot go out of the board.

If yes, then what would be the minimum number of steps for the knight to move to the said point.
If knight can not move from the source point to the destination point, then return -1

Input:
N, M, x1, y1, x2, y2
where N and M are size of chess board
x1, y1  coordinates of source point
x2, y2  coordinates of destination point

Output:
return Minimum moves or -1

Example
Input : 8 8 1 1 8 8
Output :  6
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

#define pb push_back
#define ff first
#define ss second
#define mpa make_pair

using namespace std;

class Solution {
public:
    int my_knight(int N, int M, int begin_x, int begin_y, int end_x, int end_y);

    int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[8] = {-1, 1, 1, -1, 2, -2, 2, -2};
    
    bool valid(int x, int y, int N, int M) {
        if(x <= 0 || y <= 0 || x > N || y > M)
            return false;
        return true;
    }

    int bfs(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
        int N = p3.ff;
        int M = p3.ss;
        queue<pair<pair<int, int>, int> > Que;
        map<pair<int, int>, bool> Vis;
        
        Que.push(mpa(p1, 0));

        while(!Que.empty()) {
            pair<pair<int, int>, int> temp = Que.front();
            Que.pop();

            if(temp.ff.ff == p2.ff && temp.ff.ss == p2.ss)
                return temp.ss;
            int x = temp.ff.ff;
            int y = temp.ff.ss;
            int dis = temp.ss + 1;

            if(Vis.count(mpa(x, y)))
                continue;
            Vis[mpa(x, y)] = true;

            for(int i = 0; i < 8; ++i) {
                int x1 = x + dx[i];
                int y1 = y + dy[i];
                if(valid(x1, y1, N, M))
                    Que.push(mpa(mpa(x1, y1), dis));
            }
        }

        return -1;
    }

    int knight(int N, int M, int x1, int y1, int x2, int y2) {
        pair<int, int> p1;
        p1.ff = x1;
        p1.ss = y1;

        pair<int, int> p2;
        p2.ff = x2;
        p2.ss = y2;

        pair<int, int> p3;
        p3.ff = N;
        p3.ss = M;

        int ans = bfs(p1, p2, p3);
        return ans;
    }
};

int Solution::my_knight(int N, int M, int begin_x, int begin_y, int end_x, int end_y) {
    vector<vector<bool>> visited(N+1, vector<bool>(M+1, false));
    vector<pair<int, int>> offsets = {{-2,-1},{-2,1},{-1,-2},{-1,2},
                                      {1,-2},{1,2},{2,-1},{2,1}};
    queue<tuple<int,int,int>> q;

    q.emplace(make_tuple(begin_x, begin_y, 0));
    visited[begin_x][begin_y] = true;
    while (q.size()) {
        auto& t = q.front();
        int x = get<0>(t);
        int y = get<1>(t);
        int hops = get<2>(t);
        q.pop();
        if (x == end_x && y == end_y)
            return hops;
        for (auto& offset: offsets) {
            int new_x = x + offset.first;
            int new_y = y + offset.second;
            if (new_x > 0 && new_x <= N && new_y > 0 && new_y <= M &&
                !visited[new_x][new_y]) {
                q.emplace(make_tuple(new_x, new_y, hops+1));
                visited[new_x][new_y] = true;
            }
        }
    }

    return -1;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int N, M, start_x, start_y, end_x, end_y;

    N = 8, M = 8, start_x = 1, start_y = 1, end_x = 8, end_y = 8;

    N = 2, M = 20, start_x = 1, start_y = 18, end_x = 1, end_y = 5;

    cout << "Result: " << sol.knight(N, M, start_x, start_y, end_x, end_y) << endl;

    return 0;
}

