/*
Min Stack

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

        push(x) – Push element x onto stack.
        pop() – Removes the element on top of the stack.
        top() – Get the top element.
        getMin() – Retrieve the minimum element in the stack.

Note that all the operations have to be constant time operations.

Questions to ask the interviewer :
Q: What should getMin() do on empty stack? 
A: In this case, return -1.

Q: What should pop do on empty stack? 
A: In this case, nothing. 

Q: What should top() do on empty stack?
A: In this case, return -1

*/

#include <algorithm>
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

class MinStack {
    private:
        stack<int> elementStack;
        stack<int> minimumStack;
        int minElement = -1;
    public:
        void push(int x) {
            elementStack.push(x);
            if(elementStack.size() == 1 || x <= minElement) {
                minimumStack.push(x);
                minElement = x;
            } 
        }

        void pop() {
            if (elementStack.top() == minElement) {
                minimumStack.pop();
                if (!minimumStack.empty()) {
                    minElement = minimumStack.top();
                } else {
                    minElement = -1;
                }
            }
            elementStack.pop();
        }

        int top() {
            if (elementStack.empty()) return -1;
            return elementStack.top();
        }

        int getMin() {
            return minElement;
        }
};


/*
stack<int> m_numbers;
stack<int> m_mins;

MinStack::MinStack() {
    while (m_numbers.size()) m_numbers.pop();
    while (m_mins.size()) m_mins.pop();
}

void MinStack::push(int x) {

    if (m_mins.empty() || m_mins.top() >= x) 
        m_mins.emplace(x);
    m_numbers.emplace(x);
}

void MinStack::pop() {
    if (m_numbers.empty()) return;
    int x = m_numbers.top(); 
    if (x == m_mins.top())
        m_mins.pop();
    m_numbers.pop();
}

int MinStack::top() {
    if (m_numbers.empty()) return -1;
    return m_numbers.top();
}

int MinStack::getMin() {
    if (m_mins.empty()) return -1;
    return m_mins.top(); 
}
*/


/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl;//   --> Returns -3.
    minStack.pop();
    cout << minStack.top() << endl;  //      --> Returns 0.
    cout << minStack.getMin() << endl; //   --> Returns -2.

    return 0;
}

