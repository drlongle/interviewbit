/*
Largest Distance between nodes of a Tree

Given an arbitrary unweighted rooted tree which consists of N (2 <= N <= 40000) nodes. The goal of the problem is to find largest distance between two nodes in a tree. Distance between two nodes is a number of edges on a path between the nodes (there will be a unique path between any pair of nodes since it is a tree). The nodes will be numbered 0 through N - 1.

The tree is given as an array P, there is an edge between nodes P[i] and i (0 <= i < N). Exactly one of the i’s will have P[i] equal to -1, it will be root node.

Example:
If given P is [-1, 0, 0, 0, 3], then node 0 is the root and the whole tree looks like this:

          0
       /  |  \
      1   2   3
               \
                4  

One of the longest path is 1 -> 0 -> 3 -> 4 and its length is 3, thus the answer is 3.
Note that there are other paths with maximal distance.

Hint:
  https://www.geeksforgeeks.org/longest-path-undirected-tree/

Hint:
  How would you solve the problem if you knew the longest path certainly goes through root? Try to generalize this approach for other nodes.

The crucial step is to prove that x will be one of the endpoints of the path with maximal length (note that there might be more than one such path). If it is, then the longest path from x will be the longest path in the tree.

Let d(v1, v2) be length of path between v1 and v2

Let’s prove it by contradiction: assume there is a strictly longer path between s and t, neither of which is x. Let h be a node which is closest to u among the nodes on a path between s and t. Then there are two cases:
1) h is on path between u and x

    u
    |
    |
    |
    h   x
   / \ /
  /   *
 /     \
s       t 

then d(s, t) = d(s, h) + d(h, t) <= d(s, h) + d(h, x) = d(s, x), which contradicts assumption.

2) h is not on path between u and x

    u
    |
    *---x
    |
    h
   / \
  /   \
 /     \
s       t

then

d(u, s) <= d(u, x) <= d(u, h) + d(h, x)
d(u, t) <= d(u, x) <= d(u, h) + d(h, x)

d(s, t) = d(s, h) + d(h, t)
= d(u, s) + d(u, t) - 2 d(u, h)
<= 2 d(h, x)

2 d(s, t) <= d(s, t) + 2 d(h, x)
= d(s, h) + d(h, x) + d(x, h) + d(h, t)
= d(x, s) + d(x, t)

This means that max(d(v, s), d(v, t)) >= d(s, t), which also contradicts assumption.

Thus, we proved that farthest node of a node will be one of the endpoints of the longest path.
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

#define pb push_back
#define mp make_pair
#define N 111111
#define F first
#define S second

vector<int> g[N];
pair<int, int> ans;

void dfs(int v, int p = -1, int d = 0) {
	if(d > ans.F) {
		ans = mp(d, v);
	}
	for(int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if(to != p) {
			dfs(to, v, d + 1);
		}
	}
}

class Solution {
public:
    int solve(vector<int> &edges);
    int my_solve(vector<int> &edges);
};

int Solution::solve(vector<int> &A) {
	int n = A.size();
	for(int i = 0; i < n; ++i) {
		g[i].clear();
	}
	for(int i = 0; i < n; ++i) {
		int x = A[i];
		if(x != -1) {
			assert(x != i);
			g[x].pb(i);
			g[i].pb(x);
		}
	}

	int v = 0;

	ans = mp(-1, -1);
	dfs(v);

	v = ans.S;
	ans = mp(-1, -1);
	dfs(v);

	return ans.F;
}

struct Node {
    Node(int id) : m_id(id), m_dist(-1) { }
    int m_id, m_dist;
    vector<Node*> m_neighs;
};

pair<Node*, int> bfs(Node* root)
{
    pair<Node*, int> res = {root, 0};
    root->m_dist = 0;
    queue<Node*> visiting;
    visiting.emplace(root);
    while (visiting.size()) {
        Node* node = visiting.front();
        if (node->m_dist > res.second)
            res = {node, node->m_dist};
        visiting.pop();
        for (Node* neigh: node->m_neighs) {
            if (neigh->m_dist == -1) {
                neigh->m_dist = node->m_dist + 1;
                visiting.emplace(neigh);
            }
        }
    }

    return res;
}

int Solution::my_solve(vector<int> &edges) {
    map<int, Node*> nodes;
    Node* root;
    int size = edges.size();
    for (int i = 0; i < size; ++i)
        nodes[i] = new Node(i);

    for (int i = 0; i < size; ++i) {
        int p = edges[i];
        if (p != -1) {
            nodes[i]->m_neighs.emplace_back(nodes[p]);
            nodes[p]->m_neighs.emplace_back(nodes[i]);
        }
    }

    pair<Node*, int> res;
    res = bfs(nodes[0]);
    for (int i = 0; i < size; ++i)
        nodes[i]->m_dist = -1;
    res = bfs(res.first);

    return res.second;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> edges;
    int res;

    // Expected: 3
    edges = {-1, 0, 0, 0, 3};

    // Expected: 0
    //edges = { -1 };

    // Expected: 14
    //edges = { -1, 0, 1, 1, 2, 0, 5, 0, 3, 0, 0, 2, 3, 1, 12, 14, 0, 5, 9, 6, 16, 0, 13, 4, 17, 2, 1, 22, 14, 20, 10, 17, 0, 32, 15, 34, 10, 19, 3, 22, 29, 2, 36, 16, 15, 37, 38, 27, 31, 12, 24, 29, 17, 29, 32, 45, 40, 15, 35, 13, 25, 57, 20, 4, 44, 41, 52, 9, 53, 57, 18, 5, 44, 29, 30, 9, 29, 30, 8, 57, 8, 59, 59, 64, 37, 6, 54, 32, 40, 26, 15, 87, 49, 90, 6, 81, 73, 10, 8, 16 };

    res = sol.solve(edges);
    cout << "Result: " << res << endl;

    return 0;
}

