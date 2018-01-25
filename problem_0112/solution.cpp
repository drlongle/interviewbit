/*
Clone Graph

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
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

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

unordered_map<int, UndirectedGraphNode*> cache;

class Solution {
public:
    UndirectedGraphNode* my_cloneGraph(UndirectedGraphNode *node);

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *graph) {
        if (!graph) return NULL;

        map<UndirectedGraphNode *, UndirectedGraphNode *> map;
        queue<UndirectedGraphNode *> q;
        q.push(graph);

        UndirectedGraphNode *graphCopy = new UndirectedGraphNode(graph->label);
        map[graph] = graphCopy;

        while (!q.empty()) {
            UndirectedGraphNode *node = q.front();
            q.pop();
            int n = node->neighbors.size();
            for (int i = 0; i < n; i++) {
                UndirectedGraphNode *neighbor = node->neighbors[i];
                // no copy exists
                if (map.find(neighbor) == map.end()) {
                    UndirectedGraphNode *p = new UndirectedGraphNode(neighbor->label);
                    map[node]->neighbors.push_back(p);
                    map[neighbor] = p;
                    q.push(neighbor);
                } else {     // a copy already exists
                    map[node]->neighbors.push_back(map[neighbor]);
                }
            }
        }

        return graphCopy;
    }
};

UndirectedGraphNode* clone(UndirectedGraphNode* node) {
    auto it = cache.find(node->label);
    if (it != cache.end())
        return it->second;
    UndirectedGraphNode* new_node = new UndirectedGraphNode(node->label);
    cache[node->label] = new_node;
    for (UndirectedGraphNode* n: node->neighbors)
        new_node->neighbors.emplace_back(clone(n));

    return new_node;
}

UndirectedGraphNode* Solution::my_cloneGraph(UndirectedGraphNode *node) {
    cache.clear();

    return clone(node);
}

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

