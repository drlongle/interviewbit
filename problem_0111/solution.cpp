/*
Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

Hint: What will happen if you will make the middle element of linked list the root element of BST?

Bruteforce : 
Find the middle of the list, make it the root. Left part of the tree comes from the first half and right part of the tree comes from the later half.

Can you think of making it better ? 
Note that you can construct the left tree first by passing the size of the left tree that you expect.
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    ListNode *list;
    int count(ListNode *node){
        int size = 0;
        while (node) {
            ++size;
            node = node->next;
        }
        return size;
    }

    TreeNode *generate(int n){
        if (n == 0)
            return NULL;
        TreeNode *node = new TreeNode(0);
        node->left = generate(n / 2);
        node->val = list->val;
        list = list->next;
        node->right = generate(n - n / 2 - 1);
        return node;
    }

    TreeNode *sortedListToBST(ListNode *head) {
        this->list = head;
        return generate(count(head));
    }


    TreeNode* my_sortedListToBST(ListNode* head) {
         return sortedListToBST(head, NULL);
    }

    TreeNode* sortedListToBST(ListNode* head, ListNode* tail) {
        if (!head || head == tail) return NULL;
        if (head->next == tail) return new TreeNode(head->val);
        ListNode* fast = head, *slow = head;
        while(fast != tail && fast->next != tail) {
            fast = fast->next->next;
            slow = slow->next;
        }
        TreeNode* node = new TreeNode(slow->val);
        node->left = sortedListToBST(head, slow);
        node->right = sortedListToBST(slow->next, tail);
        return node;
    }
};


int main()
{
    return 0;
}
