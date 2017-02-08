/*
Balanced Binary Tree
Total Accepted: 114900 Total Submissions: 334672 Difficulty: Easy

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Examples:

Input : 
          1
         / \
        2   3

Return : True or 1 

Input 2 : 
         3
        /
       2
      /
     1

Return : False or 0 
         Because for the root node, left subtree has depth 2 and right subtree has depth 0. 
         Difference = 2 > 1. 

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

pair<bool,int> is_balanced(TreeNode* node)
{
    if (!node) return {true,0};
    pair<bool, int> lres = is_balanced(node->left);
    pair<bool, int> rres = is_balanced(node->right);
    pair<bool,int> res = {lres.first && rres.first, 1 +
        max(lres.second,rres.second)};
    if (abs(lres.second-rres.second) > 1) res.first = false;
    return res;
}

class Solution {
public:
    bool my_isBalanced(TreeNode* node) {
        if (!node) return true;
        pair<bool, int> res = is_balanced(node);
        return res.first;
    }

    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        return isBalancedWithDepth(root).second;
    }

    pair<int, bool> isBalancedWithDepth(TreeNode *root) {
        if (root == NULL) return make_pair(0, true);
        pair<int, bool> left = isBalancedWithDepth(root->left);
        pair<int, bool> right = isBalancedWithDepth(root->right);
        int depth = max(right.first, left.first) + 1;
        // The subtree is balanced if right subtree is balanced, left subtree
        // is balanced and the depth difference is less than 1. 
        bool isbalanced = right.second && left.second &&
            (abs(right.first - left.first) < 2);
            return make_pair(depth, isbalanced);
    }
};

int main()
{
    Solution sol;

    return 0;
}

