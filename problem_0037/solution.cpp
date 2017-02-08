/*
Reverse Link List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

    Note:
    Given m, n satisfy the following condition:
    1 <= m <= n <= length of list.

    Note 2:
    Usually the version often seen in the interviews is reversing the whole
    linked list which is obviously an easier version of this question. 
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

ListNode* reverseList(ListNode* head) {
    ListNode* newhead = 0;
    ListNode* prev = 0;
    while (head) {
        newhead = head;
        ListNode* temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
    }
    
    return newhead;
}

ListNode* findTail(ListNode* head) {
    ListNode* tail = head;
    while (head) {
        tail = head;
        head = head->next;
    }
    return tail;
}

class Solution {
public:
    ListNode* my_reverseBetween(ListNode* A, int m, int n);
    
    // Reverses the linkedList which starts from head, and extends
    // to size nodes. Returns the end node.
    // Also sets the head->next as endNode->next. 
    ListNode *reverseLinkedList(ListNode *head, int size) {
        if (size <= 1) return head; 
        ListNode *cur = head, *nextNode = head->next, *tmp;

        for (int i = 0; i < (size - 1); i++) {
            tmp = nextNode->next;
            nextNode->next = cur; 
            cur = nextNode;
            nextNode = tmp; 
        }

        head->next = nextNode;
        return cur;
    }

    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Introduce dummyhead to not handle corner cases. 
        ListNode* dummyHead = new ListNode(0); 
        dummyHead->next = head; 

        // Figure out the start node of the sublist we are going to reverse
        ListNode* prev = dummyHead;
        ListNode* cur = head; 
        int index = 1;
        while (index < m) {
            prev = cur;
            cur = cur->next;
            index++;
        }

        // At this point, we have start of sublist in cur, prev of startSubList
        // in prev. Lets reverse the sublist now.
        ListNode* endSubList = reverseLinkedList(cur, n - m + 1);
        prev->next = endSubList; 

        return dummyHead->next;
    }
};

ListNode* Solution::my_reverseBetween(ListNode* A, int m, int n) {
    ListNode* head1 = 0;
    ListNode* tail1 = 0;
    ListNode* head2 = 0;
    ListNode* tail2 = 0;
    ListNode* head3 = 0;
    
    if (!A || !A->next) return A;
    
    head1 = A;
    tail1 = 0;
    for (int i = 1; i < m; i++) {
        tail1 = A;
        A = A->next;
    }
    
    head2 = tail2 = A;
    for (int i = m; i < n; ++i) {
        tail2 = tail2->next;
    }
    head3 = tail2->next;
    tail2->next = 0;
    reverseList(head2);
    swap(head2,tail2);
    tail2->next = head3;

    if (tail1) {
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
