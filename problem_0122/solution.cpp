/*
Possibility of finishing all courses given pre-requisites

There are a total of N courses you have to take, labeled from 1 to N. Some courses may have prerequisites, for example to take course 2 you have to first take course 1, which is expressed as a pair: [1,2].

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses. return 1/0 if it is possible/not possible.
The list of prerequisite pair are given in two integer arrays B and C where B[i] is a prerequisite for C[i].

Example: If N = 3 and the prerequisite pairs are [1,2] and [2,3], then you can finish courses in the following order: 1, 2 and 3. But if N = 2 and the prerequisite pairs are [1,2] and [2,1], then it is not possible for you to finish all the courses. 

Hint: Think in terms of directed graphs and dependencies. What’s the minimal property of the graph for a solution to exist?

Consider a graph with courses from 1 to N representing the nodes of the graph and each prerequisite pair [u, v] correspond to a directed edge from u to v.

It is obvious that we will get several disjoint components of the graph.

When is it possible for you to finish all the courses? 
The problem reduces down to finding a directed cycle in the whole graph. If any such cycle is present, it is not possible to finish all the courses.

Depth First Traversal(DFS) can be used to detect cycle in a Graph. There is a cycle in a graph only if there is a back edge present in the graph. A back edge is an edge that is from a node to itself (self loop) or one of its ancestor in the tree produced by DFS.

For a disconnected graph, we can check for cycle in individual DFS trees by checking back edges.

We can use various methods for detecting a back edge. One of the method is by using the method of coloring. Assume the non-visited node are colored black, the nodes currently present in the recursion stack are colored blue and the nodes already visited and out of the recursion stack are colored grey. The edge that connects current vertex in DFS to the vertex in the recursion stack(blue coloured node) is back edge.


See also: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
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

#define MAXN 100005
#define BLACK 0
#define BLUE 1
#define GREY 2

using namespace std;

vector<int> g[MAXN];
void check_cycle(int u, int visited[],bool &f) {
  visited[u] = BLUE;
  for(auto v : g[u]) {
    if(visited[v] == BLACK) {
      check_cycle(v, visited, f);
    } else if(visited[v] == BLUE) {
      //cycle found
      f = true;
    }
  }
  visited[u] = GREY;
}

class Solution {
public:
    int solve(int N, vector<int> &B, vector<int> &C);
    int my_solve(int N, vector<int> &B, vector<int> &C);
};

int Solution::solve(int N, vector<int> &B, vector<int> &C) {
    bool f = false;
    int visited[MAXN] = {0};
    for(int i = 1;i <= N; i++) {
      g[i].clear();
    }
    for(int i=0; i<B.size(); i++) {
      g[B[i]].push_back(C[i]);
    }
    for(int i = 1; i <= N; i++) {
      if(visited[i] == BLACK) {
        check_cycle(i, visited, f);
        if(f) {
          break;
        }
      }
    }
    return !f;
}

struct Node {
    Node() : visited(false), current_visit(false) { }
    bool visited, current_visit;
    vector<Node*> neighs;
};

bool has_cycle(Node* node) {
    if (node->visited) return false;

    node->visited = true;
    node->current_visit = true;
    for (auto& n: node->neighs) {
        if (!n->visited && has_cycle(n))
            return true;
        else if (n->current_visit)
            return true;
    }

    node->current_visit = false;

    return false;
}

int Solution::my_solve(int N, vector<int> &B, vector<int> &C) {
    vector<Node> nodes(N);
    for (size_t i = 0; i < B.size(); ++i) {
        int from = B[i] - 1;
        int to = C[i] - 1;
        nodes[from].neighs.emplace_back(&nodes[to]);
    }

    for (int i = 0; i < N; ++i) {
        if (has_cycle(&nodes[i]))
            return 0;
    }

    return 1;
}

int main(int argc, const char* argv[])
{
    return 0;
}

