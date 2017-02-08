/*

Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

Example :
Given


         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

Note that the left child of all nodes should be NULL.



Hint:
If you notice carefully in the flattened tree, each node’s right child points to
the next node of a pre-order traversal.

Now, if a node does not have left node, then our problem reduces to solving it
for the node->right. If it does, then the next element in the preorder traversal
is the immediate left child. But if we make the immediate left child as the right
child of the node, then the right subtree will be lost. So we figure out where
the right subtree should go. In the preorder traversal, the right subtree comes
right after the rightmost element in the left subtree. So we figure out the
rightmost element in the left subtree, and attach the right subtree as its right
child. We make the left child as the right child now and move on to the next node.

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

    void my_flatten(TreeNode* root)
    {
       TreeNode *tail;
       flatten(root, &tail);
    }

    void flatten(TreeNode* root, TreeNode**tail) {
        if (!root) {
            *tail = NULL;
            return;
        }

        *tail = root;
        if (root->left) flatten(root->left, tail);
        (*tail)->right = root->right;
        if (root->right) flatten(root->right, tail);
        if (root->left) root->right = root->left;
        root->left = NULL;
    }

    void flatten(TreeNode *root) {
        if (!root) return;
        TreeNode* node = root;
        while (node) {
            // Attatches the right sub-tree to the rightmost leaf of
            // the left sub-tree:
            if (node->left) {
                TreeNode *rightMost = node->left;
                while (rightMost->right) {
                    rightMost = rightMost->right;
                }
                rightMost->right = node->right;

                // Makes the left sub-tree to the right sub-tree:
                node->right = node->left;
                node->left = NULL;
            }

            // Flatten the rest of the tree:
            node = node->right;
        }
    }
};

TreeNode* generateTree()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    return root;
}

int main()
{
    Solution sol;
    TreeNode* root = generateTree();
    sol.flatten(root);

    return 0;
}

