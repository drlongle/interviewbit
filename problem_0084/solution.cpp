/*
Max Sum Path in Binary Tree

Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

Example :

Given the below binary tree,

       1
      / \
     2   3
Return 6.
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int my_maxPathSum(TreeNode* root);

    int maxPathSum(TreeNode *root) {
        int maxAns = INT_MIN;
        maxPathAndGlobalUpdate(root, maxAns);
        return maxAns;
    }

    int maxPathAndGlobalUpdate(TreeNode *root, int &global_max) {
        if (root == NULL) return 0;
        int l = max(0, maxPathAndGlobalUpdate(root->left, global_max));
        int r = max(0, maxPathAndGlobalUpdate(root->right, global_max));
        global_max = max(global_max, l + r + root->val);
        return root->val + max(l, r);
    }

};

pair<int, int> maxPathHeight(TreeNode* root)
{
    if (!root) return make_pair(0, 0);
    int sum, height; 
    sum = height = root->val;
    pair<int, int> lres = maxPathHeight(root->left);
    pair<int, int> rres = maxPathHeight(root->right);

    if (root->left) {
        height = max(height, max(lres.second, lres.second + root->val));
        sum = max(sum, lres.first);
    }

    if (root->right) {
        height = max(height, max(rres.second, rres.second + root->val));
        sum = max(sum, rres.first);
    }

    if (root->left && root->right)
        sum = max(sum, lres.second + root->val + rres.second);
    return make_pair(sum, height);
}

int Solution::my_maxPathSum(TreeNode* root) {
    pair<int, int> res = maxPathHeight(root);
    return res.first;
}

int main(int argc, const char* argv[])
{
    Solution sol;

    // -100 -200 -1 -300 -400 -1 -1 -1 -1

    return 0;
}

