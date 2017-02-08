/*
Least Common Ancestor

Find the lowest common ancestor in an unordered binary tree given two values in the tree.

Lowest common ancestor : the lowest common ancestor (LCA) of two nodes v and w
in a tree or directed acyclic graph (DAG) is the lowest (i.e. deepest) node
that has both v and w as descendants. 

Example :
        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2_     0        8
         /   \
         7    4

For the above tree, the LCA of nodes 5 and 1 is 3.

    LCA = Lowest common ancestor 

Please note that LCA for nodes 5 and 4 is 5.

You are given 2 values. Find the lowest common ancestor of the two nodes
represented by val1 and val2
        
No guarantee that val1 and val2 exist in the tree. If one value doesn't
exist in the tree then return -1.

There are no duplicate values.
You can use extra memory, helper functions, and can modify the node struct but,
you can't add a parent pointer.
*/

#include <algorithm>
#include <array>
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
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

pair<int,TreeNode*> find_nodes(TreeNode* root, int val1, int val2)
{
    pair<int, TreeNode*> res(0, 0);
    if (!root) return res;

    res.first += val1 == root->val;
    res.first += val2 == root->val;
    if (res.first == 2)
    {
        res.second = root;
        return res;
    }

    pair<int,TreeNode*> lres = find_nodes(root->left, val1, val2);
    if (lres.first == 2)
        return lres;
    pair<int,TreeNode*> rres = find_nodes(root->right, val1, val2);
    if (rres.first == 2)
        return rres;
    res.first += lres.first + rres.first;
    if (res.first == 2)
        res.second = root;

    return res;        
}

class Solution {
public:
    int my_lca(TreeNode* root, int val1, int val2);
    TreeNode *LCA(TreeNode *root, int val1, int val2) {
        if (!root) return NULL;
        if (root->val == val1 || root->val == val2) return root;
        TreeNode *L = LCA(root->left, val1, val2);
        TreeNode *R = LCA(root->right, val1, val2);
        if (L && R) return root; // If val1, val2 are on both sides 
        return L ? L : R; // either one of val1, val2 is on one side
                          // OR val1, val2 is not in L&R subtrees
    }

    bool find(TreeNode *root, int val1) {
        if (!root) return false;
        if (root->val == val1) return true;
        return (find(root->left, val1) || find(root->right, val1));
    }

    int lca(TreeNode *root, int val1, int val2) {
        if (!find(root, val1) || !find(root, val2)) return -1;
        TreeNode *ans = LCA(root, val1, val2);
        if (!ans) return -1;
        return ans->val;
    }
};

int Solution::my_lca(TreeNode* root, int val1, int val2)
{
    pair<int,TreeNode*> res = find_nodes(root, val1, val2);
    if (res.first == 2)
        return res.second->val;
    else
        return -1;
}

int main()
{
    Solution sol;

    return 0;
}

