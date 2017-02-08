/*
Invert Binary Tree
Total Accepted: 96025 Total Submissions: 207955 Difficulty: Easy

Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9

to

     4
   /   \
  7     2
 / \   / \
9   6 3   1
*/

#include <algorithm>
#include <array>
#include <cassert>
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* my_invertTree(TreeNode* root);
    TreeNode* invertTree(TreeNode *root) {
        if (!root) return root;
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
        return root;
    }
};

TreeNode* Solution::my_invertTree(TreeNode* root)
{
    if (!root) return 0;
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    root->left = invertTree(right);
    root->right = invertTree(left);
    return root;
}

int main()
{
    Solution sol;

    return 0;
}

