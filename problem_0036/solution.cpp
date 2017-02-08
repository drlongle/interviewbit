/*
Swap List Nodes in pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values
in the list, only nodes itself can be changed.

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
    ListNode* my_swapPairs(ListNode* head);
    ListNode *swapPairs(ListNode *head) {
        ListNode* start = new ListNode(0);//make head no longer a special case
        start->next = head;

        ListNode *cur = start;
        while (cur->next != NULL && cur->next->next != NULL) {
            cur->next = swap(cur->next, cur->next->next);
            cur = cur->next->next;
        }
        return start->next;
    }

    ListNode* swap(ListNode* next1, ListNode* next2) {
        next1->next = next2->next;
        next2->next = next1;
        return next2;
    }
};

ListNode* Solution::my_swapPairs(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* newhead = 0;
    ListNode* curr = head;
    ListNode* prev = 0;
    while (curr) {
        ListNode* next = curr->next;
        ListNode* temp = (next != 0) ? next->next : 0;
        if (!newhead)
            newhead = next;
        else
            prev->next = (next ? next : curr);
        if (next)
            next->next = curr;
        prev = curr;
        curr = temp;
    }
    if (prev)
        prev->next = 0;

    return newhead;
}

ListNode* generateList() {
    std::srand(std::time(0)); // use current time as seed for random generator
    int listsize = std::rand() % 20;
    listsize = 2;
    vector<int> nums;
    for (int i = 0; i < listsize; ++i)
        nums.push_back(std::rand() % 400);
    sort(nums.begin(), nums.end());
    ListNode *head = NULL, *node, *tail;

    for(const auto& n: nums) {
        node = new ListNode(n);
        if (head == NULL)
            head = node;
        else
            tail->next = node;
        tail = node;
    }

    return head;
}

void printList(ListNode* node) {
    while (node) {
        cout << node->val << ", ";
        node = node->next;
    }
    cout << endl;
}

int main()
{
    Solution sol;
    ListNode* head = generateList();
    cout << "Before:" << endl;
    printList(head);
    ListNode* result = sol.swapPairs(head);
    cout << "After:" << endl;
    printList(result);
    return 0;
}

