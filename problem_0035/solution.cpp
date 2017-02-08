/*
Partition List

Given a linked list and a value x, partition it such that all nodes less than
x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the
two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
 */

#include <algorithm>
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
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* my_partition(ListNode* A, int B);
    ListNode *partition(ListNode *head, int x) {

        if (!head) return NULL;
        ListNode * iterator = head; 

        ListNode * start = new ListNode(0); // list of nodes greater than x
        ListNode * tail = start;

        ListNode * newHead = new ListNode(0); 
        newHead -> next = head;
        ListNode * pre = newHead; // previous node, we need it for removing

        while (iterator) {
            if (iterator -> val >= x) {
                pre -> next = iterator -> next; // remove from our list
                tail -> next = iterator; // add to list of nodes greater than x
                tail = tail -> next;
                iterator = iterator -> next;
                tail -> next = NULL;
            }
            else
                pre = iterator, iterator = iterator -> next;
        }
        pre -> next = start -> next;
        return newHead -> next;
    }
};

void appendNode(ListNode*&head, ListNode*& tail, ListNode* node)
{
    if (tail)
        tail->next = node;
    else
        head = node;
    tail = node;
}

ListNode* Solution::my_partition(ListNode* A, int B) {
    ListNode* head1 = 0;
    ListNode* tail1 = 0;
    ListNode* head2 = 0;
    ListNode* tail2 = 0;
    
    while (A) {
        if (A->val < B)
            appendNode(head1,tail1,A);
        else
            appendNode(head2,tail2,A);
        A = A->next;
    }
    
    if (tail1) tail1->next = 0;
    if (tail2) tail2->next = 0;
    if (head1) {
        tail1->next = head2;
        return head1;
    }
    else
        return head2;
}

int main()
{
    Solution sol;

    return 0;
}
