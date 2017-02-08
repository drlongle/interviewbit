/*
Inorder Traversal of Cartesian Tree

Given an inorder traversal of a cartesian tree, construct the tree.

    Cartesian tree : is a heap ordered binary tree, where the root is greater than all the elements in the subtree. 

    Note: You may assume that duplicates do not exist in the tree. 

Example :

Input : [1 2 3]

Return :   
          3
         /
        2
       /
      1

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
    TreeNode* my_buildTree(vector<int> &nums);

    TreeNode *buildTree(vector<int> &inorder, int start, int end) {
        if (start == end) {
            return new TreeNode(inorder[start]);
        }
        if (start > end) return NULL;

        // find max which will be the root. 
        int maxVal = INT_MIN, maxIndex = -1;
        for (int i = start; i <= end; i++) {
            if (inorder[i] > maxVal) {
                maxVal = inorder[i];
                maxIndex = i;
            }
        }

        TreeNode *root = new TreeNode(maxVal);
        root->left = buildTree(inorder, start, maxIndex - 1);
        root->right = buildTree(inorder, maxIndex + 1, end);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder) {
        if (inorder.size() == 0) return NULL;
            return buildTree(inorder, 0, inorder.size() - 1);
    }
};

TreeNode* build_tree(vector<int> &nums, int begin, int end)
{
    if (begin >= end) return NULL;
    vector<int>::iterator max_it =
        max_element(nums.begin()+begin, nums.begin()+end);
    int max_pos = max_it - nums.begin();
    TreeNode* root = new TreeNode(*max_it);
    root->left = build_tree(nums, begin, max_pos);
    root->right = build_tree(nums, max_pos+1, end);

    return root;
}

TreeNode* Solution::my_buildTree(vector<int> &nums)
{
    return build_tree(nums, 0, nums.size());
}

void traverse(TreeNode* node)
{
    cout << node->val << ", ";
    if (node->left)
        traverse(node->left);
    if (node->right)
        traverse(node->right);
}

int main()
{
    Solution sol;
    vector<int> nums;
    TreeNode* res;

    nums = {1,2,3};
    nums = {1,2,3,7,9};
    nums = {1,2,13,8,7,9};
    res = sol.buildTree(nums);
    traverse(res);
    cout << endl;

    return 0;
}

