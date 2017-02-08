/*
Add Two Numbers as Lists

You are given two linked lists representing two non-negative numbers. The
digits are stored in reverse order and each of their nodes contain a single
digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

    342 + 465 = 807

Make sure there are no trailing zeros in the output list. So,
7 -> 0 -> 8 -> 0 is not a valid response even though the value is still 807.
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
    ListNode* my_addTwoNumbers(ListNode* A, ListNode* B);

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;

        int carry = (l1->val + l2->val) / 10;
        ListNode *l3 = new ListNode((l1->val + l2->val) % 10);
        ListNode *tail = l3;
        l1 = l1->next;
        l2 = l2->next;

        while(l1 || l2 || carry)
        {
            int sum = ((l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry);
            ListNode *t  = new ListNode(sum % 10);
            carry = sum / 10;                                          

            if(l1)
                l1 = l1->next;
            if(l2)
                l2 = l2->next;
            tail->next = t;
            tail = t;
        }

        return l3;
    }
};

ListNode* Solution::my_addTwoNumbers(ListNode* A, ListNode* B) {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    int carry = 0;

    while (A || B || carry) {
        int temp = carry;
        if (A) {
            temp += A->val;
            A = A->next;
        }
        if (B) {
            temp += B->val;
            B = B->next;
        }
        carry = (temp >= 10) ? 1 : 0;
        ListNode *node = new ListNode(temp % 10);
        if (head)
            tail->next = node;
        else
            head = node;
        tail = node;
    }

    return head;
}

ListNode* generateList() {
    std::srand(std::time(0)); // use current time as seed for random generator
    int listsize = 1+std::rand() % 10;
    vector<int> nums;
    for (int i = 0; i < listsize; ++i)
        nums.push_back(std::rand() % 10);
    //sort(nums.begin(), nums.end());
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
    ListNode* A = generateList();
    ListNode* B = generateList();
    ListNode* result = sol.addTwoNumbers(A,B);
    printList(A);
    printList(B);
    printList(result);

    return 0;
}
