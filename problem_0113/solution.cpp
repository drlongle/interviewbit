/*
Binary Tree Level Order Traversal
Total Accepted: 108255 Total Submissions: 324452 Difficulty: Easy

Given a binary tree, return the level order traversal of its nodes' values.
(i.e., from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

Hint: Can you maintain depth of a node while traversing the tree. How can it help you after the tree traversal?

There are 2 ways to solve this problem.

Approach 1: Maintain a vector of size ‘depth’ of the tree. Do any kind of tree traversal keeping track of the current depth. Append the current element to vector[currentDepth]. Since we need stuff left to right, make sure left subtree is visited before the right subtree ( Any of traditional pre/post/inorder traversal should suffice ).

Approach 2: This is important. A lot of times, you’d be asked to do a traditional level order traversal. Or to put in formal words, a traversal where the extra memory used should be proportional to the nodes on a level rather than the depth of the tree. To do that, you need to make sure you are accessing all the nodes on a level before accessing the nodes on next. This is a typical breadth first search problem. Queue FTW.

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
    void buildVector(TreeNode *root, int depth, vector<vector<int> > &ret) {
        if(root == NULL) return;
        if(ret.size() == depth)
            ret.push_back(vector<int>());

        ret[depth].push_back(root->val);
        buildVector(root->left, depth + 1, ret);
        buildVector(root->right, depth + 1, ret);
    }

    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > ret;
        buildVector(root, 0, ret);
        return ret;
    }

    vector<vector<int>> my_levelOrder(TreeNode* root) {
        vector<vector<int> > res;
        array<queue<TreeNode*>,2> visits;
        if (!root) return res;
        int queue_index = 0, result_index = 0;

        visits[0].emplace(root);
        while (visits[0].size() || visits[1].size())
        {
            res.emplace_back(vector<int>());
            while (visits[queue_index].size())
            {
                TreeNode* node = visits[queue_index].front();
                visits[queue_index].pop();
                res[result_index].emplace_back(node->val);
                if (node->left) visits[1-queue_index].emplace(node->left);
                if (node->right) visits[1-queue_index].emplace(node->right);
            }
            queue_index = 1 - queue_index;
            ++result_index;
        }

        return res;
    }
};

int main()
{
    Solution sol;

    return 0;
}

