/*
Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

Example :
Given binary tree

   1
    \
     2
    /
   3

return [1,3,2].

Using recursion is not allowed.

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
    vector<int> my_inorderTraversal(TreeNode* root);

    vector<int> inorderTraversal_1(TreeNode *root) {
        vector<int> vector;
        if(!root)
            return vector;
        stack<TreeNode *> stack;
        stack.push(root);
        while(!stack.empty())
        {
            TreeNode *pNode = stack.top();
            if(pNode->left)
            {
                stack.push(pNode->left);
                pNode->left = NULL;
            }
            else
            {
                vector.push_back(pNode->val);
                stack.pop();
                if(pNode->right)
                    stack.push(pNode->right);
            }
        }
        return vector;
    }

    vector<int> inorderTraversal_2(TreeNode *root) {
        vector<int> vector;
        if(!root)
            return vector;
        unordered_map<TreeNode *, bool> map;//left child has been visited:true.
        stack<TreeNode *> stack;
        stack.push(root);
        while(!stack.empty())
        {
            TreeNode *pNode = stack.top();
            if(pNode->left && !map[pNode])
            {
                stack.push(pNode->left);
                map[pNode] = true;
            }
            else
            {
                vector.push_back(pNode->val);
                stack.pop();
                if(pNode->right)
                    stack.push(pNode->right);
            }
        }
        return vector;
    }

    vector<int> inorderTraversal_3(TreeNode *root) {
        vector<int> vector;
        stack<TreeNode *> stack;
        TreeNode *pCurrent = root;

        while(!stack.empty() || pCurrent)
        {
            if(pCurrent)
            {
                stack.push(pCurrent);
                pCurrent = pCurrent->left;
            }
            else
            {
                TreeNode *pNode = stack.top();
                vector.push_back(pNode->val);
                stack.pop();
                pCurrent = pNode->right;
            }
        }
        return vector;
    }
};

vector<int> Solution::my_inorderTraversal(TreeNode* node)
{
    stack<TreeNode*> visits;
    vector<int> res;

    while (visits.size() || node) 
    {
        if (node)
        {
            visits.emplace(node);
            node = node->left;
        }
        else
        {
            node = visits.top();
            visits.pop();
            res.emplace_back(node->val);
            if (node->right)
                node = node->right;
            else
                node = 0;
        }
    }

    return res;
}

int main()
{
    Solution sol;

    return 0;
}

