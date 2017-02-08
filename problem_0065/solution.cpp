/*
Max Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node
down to the nearest leaf node.

    NOTE : The path has to end on a leaf node. 

Example :

         1
        /
       2

max depth = 2.

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

class Solution {
public:
    int my_maxDepth(TreeNode* A);

    int maxDepth(TreeNode *root) {
        // Corner case.
        if (root == NULL) return 0;
        // Base case : Leaf node. This accounts for height = 1.
        if (root->left == NULL && root->right == NULL) return 1;

        if (!root->left) return maxDepth(root->right) + 1;
        if (!root->right) return maxDepth(root->left) + 1;

        return max(maxDepth(root->left), maxDepth(root->right)) + 1; 
    }
};

int Solution::my_maxDepth(TreeNode* root)
{
    if (!root) return 0;
    return 1 + max(maxDepth(root->left),maxDepth(root->right));
}

int main()
{
    Solution sol;

    return 0;
}

