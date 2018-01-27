/*
Smallest Multiple With 0 and 1

You are given an integer N. You have to find smallest multiple of N which consists of digits 0 and 1 only. Since this multiple could be large, return it in form of a string.

Note: Returned string should not contain leading zeroes.

For example,
For N = 55, 110 is smallest multiple consisting of digits 0 and 1.
For N = 2, 10 is the answer.

Hint:

Naive approach: We multiply N with positive numbers and then check it consists of only ones and zeros.

What could be a faster approach? A recursive solution where we build all possible numbers consists of digits ones and zeroes only.
For example, something like:

        1
       / \
      /   \
     /     \
    /       \
   10       11   
  /  \     /  \
 /    \   /    \
100  101  110  111

and so on.

How can we merge nodes in this based on values with modulo N in such a way that we don’t visit all possible states.

Let’s represent our numbers as strings here. Now, consider there are N states, where i’th state stores the smallest string which when take modulo with N gives i. Our aim is to reach state 0. Now, we start from state “1” and at each step we have two options, either to append “0” or “1” to current state. We try to explore both the options, but note that if I have already visited a state, why would I visit it again? It already stores the smallest string which achieves that state and if I visit it again with a new string it will surely have more characters than already stored string.

So, this is basically a BFS on the states. We’ll visit a state atmost once, hence overall complexity is O(N). Interesting thing is that I need not store the whole string for each state, I can just store the value modulo N and I can easily see which two new states I am going to.

But, how do we build the solution?
If I reach a state x, I store two values

From which node I arrived at node x from. Say this is node y.
What(0 or 1) did I append at string at node y to reach node x
Using this information, I can build my solution by repeatedly going to parents starting from node 0.

See also:
https://www.geeksforgeeks.org/find-the-smallest-binary-digit-multiple-of-given-number/
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std;

class Solution {
public:
    string multiple(int N);
    string my_multiple(int N);
};

struct Node {
    Node() : visited(false), ch('0'), parent(nullptr) { }
    bool visited;
    char ch;
    Node* parent;
};

int mod(string t, int N)
{
    int r = 0;
    for (size_t i = 0; i < t.length(); i++)
    {
        r = r * 10 + (t[i] - '0');
        r %= N;
    }
    return r;
}

void get_string(char* s, Node* node, int& index)
{
    if (node->parent)
        get_string(s, node->parent, index);
    else
        index = 0;
    s[index++] = node->ch;
}

string Solution::my_multiple(int N) {
    vector<Node> nodes(N+1);
    queue<Node*> q;
    Node *node, *new_node;
    char s[N+1];
    memset(s, 0, N+1);
    int s_index = 0;

    node = &nodes[1];
    node->ch = '1';
    node->visited = true;
    q.emplace(node);
    while (q.size()) {
        node = q.front();
        get_string(s, node, s_index);
        int rem = mod(s, N);
        q.pop();
        if (rem == 0)
            return s;
        for (int i = 0; i <= 1; ++i) {
            char ch = '0' + i;
            s[s_index] = ch;
            int new_rem = (rem*10 + i) % N;
            new_node = &nodes[new_rem];
            if (!new_node->visited) {
                new_node->visited = true;
                new_node->parent = node;
                new_node->ch = ch;
                q.emplace(new_node);
            }
        }
        s[s_index] = '\0';
    }

    return "0";
}

vector<int> flag,parent,val;

string solve(int n)
{
    int p,q;
    
    //final string
    string ret="";

    //queue for bfs
    queue < int > myq;

    //initial node
    int temp=1%n;
    flag[temp]=1;
    val[temp]=1;
    myq.push(temp);

    while(1)
    {
        //pop from queue
        temp=myq.front();
        myq.pop();
        p=temp;

        //reached final state
        //build solution here
        if(p==0)
        {
            p=0;
            ret+=(char)(val[p]+'0');
            p=parent[p];
            while(p!=0)
            {
                ret+=(char)(val[p]+'0');
                p=parent[p];
            }
            reverse(ret.begin(), ret.end());
            return ret;
        }
        
        //visit two neighbors p*10 and p*10+1
        //if already not visited
        q=(p*10)%n;
        if(flag[q]==0)
            myq.push(q),flag[q]=1,parent[q]=p,val[q]=0;

        q++;
        if(q>=n)q-=n;
        if(flag[q]==0)
            myq.push(q),flag[q]=1,parent[q]=p,val[q]=1;
    }
}

string Solution::multiple(int A) {
    flag.clear();
    parent.clear();
    val.clear();
    flag.resize(A);
    parent.resize(A);
    val.resize(A);
    return solve(A);
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int N;

    cout << "Input: ";
    cin >> N;
    cout << "Result: " << sol.multiple(N) << endl;

    return 0;
}

