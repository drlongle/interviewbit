/*
Merge k Sorted Lists
Total Accepted: 88560 Total Submissions: 373506 Difficulty: Hard

Merge k sorted linked lists and return it as one sorted list. Analyze and
describe its complexity. 

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void append_node(ListNode*& head, ListNode*& tail, ListNode* node)
{
    if (head)
        tail->next = node;
    else
        head = node;
    tail = node;
    node->next = 0;
}

class Solution {
public:

    struct CompareNode {
        bool operator()(ListNode* const & p1, ListNode* const & p2) {
            // return "true" if "p1" is ordered before "p2", for example:
            return p1->val > p2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        priority_queue<ListNode*,vector<ListNode*>,CompareNode> queue;

        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != NULL) {
                queue.push(lists[i]);
            }
        }

        while (!queue.empty()) {
            tail->next = queue.top();
            queue.pop();
            tail = tail->next;

            if (tail->next) {
                queue.push(tail->next);
            }
        }

        return dummy->next;
    } 

    ListNode* my_mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = 0, *tail = 0;
        multimap<int, size_t> candidates;
        for (size_t i = 0; i < lists.size(); ++i)
        {
            ListNode* node = lists[i];
            if (!node) continue;
            candidates.emplace(node->val, i);
        }

        while (candidates.size())
        {
            size_t index = candidates.begin()->second;
            candidates.erase(candidates.begin());
            ListNode* node = lists[index];
            ListNode* newnode = node->next;
            append_node(head, tail, node);
            if (!newnode) continue;
                lists[index] = newnode;
            candidates.emplace(newnode->val, index);
        }

        return head;
    }
};

int main()
{
    Solution sol;
    ListNode* node = new ListNode(1);
    vector<ListNode*> lists = {node};
    sol.mergeKLists(lists);

    return 0;
}

