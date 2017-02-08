/*
Kth Smallest Element in a BST  
Total Accepted: 44592 Total Submissions: 118625 Difficulty: Medium

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 <= k <= BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Example :

Input : 
  2
 / \
1   3

and k = 2

Return : 2

As 2 is the second smallest element in the tree.
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
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

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int getSize(TreeNode* node) {
        int count = 1;
        if (node->left)
            count += getSize(node->left);
        if (node->right)
            count += getSize(node->right);
        return count;
    }

    int my_kthsmallest(TreeNode* root, int k) {
        int leftsize = 0;
        if (root->left)
            leftsize = getSize(root->left);
        if (leftsize + 1 == k)
            return root->val;
        if (leftsize >= k)
            return kthsmallest(root->left, k);
        else
            return kthsmallest(root->right, k-leftsize-1);
    }

    int find(TreeNode* root, int &k) {
        if (!root) return -1;
        // We do an inorder traversal here. 
        int k1 = find(root->left, k);
        if (k == 0) return k1; // left subtree has k or more elements.
        k--; 
        if (k == 0) return root->val; // root is the kth element.
        return find(root->right, k); // answer lies in the right node.
    }

    int kthsmallest(TreeNode* root, int k) {
        return find(root, k); // Call another function to pass k by reference.
    }
};

int main()
{
    return 0;
}

