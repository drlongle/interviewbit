/*
Next Greater Number BST

Given a BST node, return the node which has value just greater than the given node.

Example:

Given the tree

               100
              /   \
            98    102
           /  \
         96    99
          \
           97

Given 97, you should return the node corresponding to 98 as thats the value just greater than 97 in the tree.
If there are no successor in the tree ( the value is the largest in the tree, return NULL).

Using recursion is not allowed.

Assume that the value is always present in the tree.
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
    TreeNode* my_getSuccessor(TreeNode* A, int B) ;

    TreeNode* Find(TreeNode *root, int data) {
        while (root != NULL && root->val != data) {
            if (data < root->val) root = root->left; 
            else root = root->right; 
        }
        if (root != NULL && root->val == data) return root; 
        return NULL;
    }

    TreeNode* FindMin(TreeNode *root) {
        while (root->left != NULL) root = root->left; 
        return root;
    }

    TreeNode* getSuccessor(TreeNode* root, int data) {
        // Search the node O(h)
        TreeNode* current = Find(root, data);
        if (current == NULL) return NULL;
        if (current->right != NULL)  { // Case 1 : Node has right subtree
            return FindMin(current->right);
        } else {
            TreeNode *successor = NULL, *ancestor = root; 
            while (ancestor != current) {
                if (data < ancestor->val) {
                    successor = ancestor; // so far this is the deepest node
                                          // for which current node is in left. 
                    ancestor = ancestor->left; 
                } else 
                    ancestor = ancestor->right;
            }
            return successor;
        }
    }
};

TreeNode* Solution::my_getSuccessor(TreeNode* root, int value) {
    TreeNode* res = 0;
    while (root)
    {
        if (root->val > value)
            res = root;
        if (root->val <= value)
            root = root->right;
        else
            root = root->left;
    }
    return res;
}

int main()
{
    Solution sol;

    return 0;
}

