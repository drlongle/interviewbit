/*
Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
]

*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <climits>
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
#include <vector>

#include <string.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> my_zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        array<vector<TreeNode*>, 2> visiting;
        if (!root) return result;
        visiting[0].push_back(root);
        int index = 0;
        while(visiting[0].size() || visiting[1].size())
        {
            vector<int> row;
            int size = static_cast<int>(visiting[index].size());
            for (int i = 0; i < size; ++i) {
                TreeNode* node = visiting[index][i];
                if(index == 0) row.push_back(node->val);
                if (node->left) visiting[1-index].emplace_back(node->left);
                if (node->right) visiting[1-index].emplace_back(node->right);
            }
            if (index != 0) {
                for (int i = size-1; i >= 0; --i) {
                    TreeNode* node = visiting[index][i];
                    row.push_back(node->val);
                }
            }
            visiting[index].clear();
            index = 1-index;
            result.emplace_back(row);
        }

        return result;
    }

    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> > output;
        if (root == NULL) return output;
        stack<TreeNode*> cur_layer;
        cur_layer.push(root);
        stack<TreeNode*> next_layer;
        vector<int> layer_output;
        int d = 0; // 0: left to right; 1: right to left.

        while (!cur_layer.empty()) {
            TreeNode* node = cur_layer.top();
            cur_layer.pop();
            layer_output.push_back(node->val);
            if (d == 0) {
                if (node->left != NULL) next_layer.push(node->left);
                if (node->right != NULL) next_layer.push(node->right);
            } else {
                if (node->right != NULL) next_layer.push(node->right);
                if (node->left != NULL) next_layer.push(node->left);
            }

            if (cur_layer.empty()) {
                output.push_back(layer_output);
                layer_output.clear();
                cur_layer.swap(next_layer);
                if (d == 1) d = 0;
                else d = 1;
            }
        }
        return output;
    }
};

int main()
{
    return 0;
}
