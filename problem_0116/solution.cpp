/*
Valid Path

There is a rectangle with left bottom as  (0, 0) and right up as (x, y). There are N circles such that their centers are inside the rectangle. Radius of each circle is R. Now we need to find out if it is possible that we can move from (0, 0) to (x, y) without touching any circle.
Note : We can move from any cell to any of its 8 adjecent neighbours and we cannot move outside the boundary of the rectangle at any point of time.

Constraints
 0 <= x , y , R <= 100  
 1 <= N <= 1000 
Center of each circle would lie within the grid

Input
Input contains x, y , N , R  and two array of size N containing centers of circles.
The ith index of first array contains x co-ordinate of the ith circle and ith index of second array contains the y co-ordinate of the ith circle.

Output 
YES or NO depending on weather it is possible to reach cell  (x,y) or not starting from (0,0).

Sample Input 
2 3 1 1 
2
3

Sample Output
NO
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

#define CACHE_SIZE 101
using namespace std;

class Solution {
public:
    string my_solve(int A, int B, int circles, int radius, vector<int> &E, vector<int> &F);
    string solve(int A, int B, int circles, int radius, vector<int> &E, vector<int> &F);
};

// cache[x][y] = 0 --> cell has not been visited
// cache[x][y] = 1 --> cell is being visited
// cache[x][y] = 2 --> cell has not been visited and has negative result
int cache[CACHE_SIZE][CACHE_SIZE];

pair<int, int> dest;

bool is_valid_position(int x, int y, int radius, vector<int>& E, vector<int>& F) {
    int ssize = E.size();
    for (int i = 0; i < ssize; ++i) {
        int dist = sqrt((E[i]-x)*(E[i]-x) + (F[i]-y)*(F[i]-y));
        if (dist <= radius) {
            cache[x][y] = 2;
            return false;
        }
    }
    return true;
}

string find_path(int x, int y, int radius, vector<int>& E, vector<int>& F) {
    if (cache[x][y] == 2)
        return "NO";
    cache[x][y] = 1;
    if (x == dest.first && y == dest.second)
        return "YES";
    vector<pair<int,int>> offset = { {1,-1}, {1,0}, {1,1}, {-1,-1},
                                     {-1,0}, {-1,1}, {0,-1}, {0,1} };
    for (auto& p: offset) {
        int new_x = x + p.first;
        int new_y = y + p.second;
        if (new_x >= 0 && new_x <= dest.first && new_y >= 0 && new_y <= dest.second &&
            !cache[new_x][new_y] && is_valid_position(new_x, new_y, radius, E, F)) {
            if (find_path(new_x, new_y, radius, E, F) == "YES")
                return "YES";
        }
    }
    cache[x][y] = 2;

    return "NO";
}

string Solution::my_solve(int A, int B, int circles, int radius, vector<int> &E, vector<int> &F) {
    memset(cache, 0, sizeof(cache[0][0]) * CACHE_SIZE * CACHE_SIZE);
    dest = make_pair(A, B);

    return find_path(0, 0, radius, E, F);
}

bool check(int x,int y,int R,vector<int>&E,vector<int>&F)
{
    int r=R*R;
    for(int i=0;i<E.size();i++)
    {
        int dx=abs(x-E[i]);
        int dy=abs(y-F[i]);
        dx=dx*dx;
        dy=dy*dy;
        if(dx+dy<=r)
        return true;
    }
    return false;
}
bool safe(int a,int b,int x,int y)
{
    if(x<=a && x>=0 && y<=b && y>=0)
        return true;
    return  false;
}

string Solution::solve(int A, int B, int C, int D, vector<int> &E, vector<int> &F) {
    queue<pair<int,int> >q;
    q.push(make_pair(0,0));
    bool visit[A+1][B+1];
    visit[0][0]=true;
    memset(visit,false,sizeof(visit));
    while(!q.empty())
    {
        int x=q.front().first;
        int y=q.front().second;
     
        q.pop();
        if(x==A&&y==B)
        return "YES";
        
        for(int i=-1;i<2;i++)
            for(int j=-1;j<2;j++)
            {
                if(i==0&&j==0)
                continue;
                
                if(!check(x+i,y+j,D,E,F)&&safe(A,B,x+i,y+j)&&!visit[x+i][y+j])
                {
                    q.push(make_pair(x+i,y+j));
                    visit[x+i][y+j]=true;
                }
            }
    }

    return "NO";
}

int main(int argc, const char* argv[])
{
    Solution sol;
    string res;
    vector<int> E, F;
    int A, B, N, R;

    A = 2, B = 3, N = 1, R = 1;
    E = {2}, F = {3};

    A = 41, B = 67, N = 5, R = 0;
    E = {17, 16, 12, 0, 40};
    F = {52, 61, 61, 25, 31};

    res = sol.solve(A, B, N, R, E, F);
    cout << "Result: " << res << endl;

    return 0;
}

