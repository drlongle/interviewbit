/*
List Cycle

Given a linked list, return the node where the cycle begins.
If there is no cycle, return null.

Try solving it using constant additional space.
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
    ListNode* my_detectCycle(ListNode* head);
    
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return NULL;

        ListNode* firstp = head;
        ListNode* secondp = head;
        bool isCycle = false;

        while(firstp != NULL && secondp != NULL) {
            firstp = firstp->next;
            if (secondp->next == NULL) return NULL;
            secondp = secondp->next->next;
            if (firstp == secondp) { isCycle = true; break; }
        }

        if(!isCycle) return NULL;
        firstp = head;
        while( firstp != secondp) {
            firstp = firstp->next;
            secondp = secondp->next;
        }

        return firstp;
    }
};

ListNode* Solution::my_detectCycle(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    bool cycle = false;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast) {
            cycle = true;
            break;
        }
    }

    if (!cycle)
        return 0;
    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}

int main()
{
    Solution sol;

    return 0;
}

