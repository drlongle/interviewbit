/*
Order of People Heights

You are given the following :

    - A positive number N
    - Heights : A list of heights of N persons standing in a queue. Note that
    the order of this list is random.
    - Infronts : A list of numbers corresponding to each person (P) that gives
    the number of persons who are taller than P and standing in front of P

You need to return list of actual order of persons' height (return the ordered
list of people standing in the queue)

Consider that heights will be unique

Example

Input : 
Heights: 5 3 2 6 1 4
InFronts: 0 1 2 0 3 2

Output : 
actual order is: 5 3 2 1 6 4 

Hint 1:

This problem is slightly tricky.

Really inefficient but correct approach :

Try out all possible permutation of the give numbers, and verify if the infronts
numbers match for the given sequence. This is obviously too inefficient. O(N!).
Lets see if we can do something better.

Hint towards something better

What can you say about the position of the shortest person ? If the position of
the shortest person is i, how many people would be in front of the shortest person ?

Once you fix the position of the shortest person, what can you say about the
position of the second shortest person ?

If we take that approach, do we need to sort the heights first ?

Hint 2:

O(N^2) approach

Sort people by heights. Then iterate from shortest to tallest. In each step you
need an efficient way to put the next person to the correct position. Notice
that people we've already placed are not taller than the current person. And
the people we place after are taller than the current. So we have to find a
place such that the number of empty positions in the front is equal to the
inFronts value of this person.

Lets take an example :

For example after sorting,
Height - 1, 2, 3, 4, 5, 6 Infront - 3, 2, 1, 2, 0, 0.

1st element should go in position 3. Hence final array becomes:

---1--

2nd element shall go in position 2. Hence final array becomes:

--21--

3rd element should go in position 1. Hence final array becomes:

-321--

4th element shall go in position 2. This is the position among the empty ones.
Hence final array becomes:

-321-4

5th element shall go in position 0. Hence final array becomes:

5321-4

6th element should go in position 0. Hence final array becomes:
532164

Hint towards an even better solution

Can we make the process of finding the ith empty position even more efficient ?
Think binary tree / segment tree ? Oh, by the way, this would be a nice time to
read up on Segment Trees which are incredibly useful
( http://codeforces.com/blog/entry/3327 )
What if you knew how many elements are there in first half of the array, and the
second half of the array ?

Access Hint

Here, we will explore how to efficiently answer the query of finding the ith empty space.

The query can be solved using segment / interval tree.
The root contains the number of elements in [0, N].
Left node contains the number of elements in [0, N/2]
Right node contains the number of elements in [N/2 + 1, N]

Lets say we need to find the ith empty position.
We look at the number of elements X in [0, N/2].

If
    N / 2 - X >= i, the position lies in the left part of array and we move down to the left node.
    N / 2 - X < i, we now look for i - (N / 2 - X) th position in the right part of the array and move to the right node in the tree.
    
    This is a fairly standard use of the segment tree.
 */

#include <algorithm>
#include <array>
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
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

struct Node {
    int data;
    int best;
    int pri;
    int size;
    struct Node *left;
    struct Node *rig;
};

struct Node arr[400000];
struct Node *dummy;
struct Node *ptr = arr;
struct Node *root;

class Solution {
public:
    vector<int> my_order(vector<int> &heights, vector<int> &infronts);

    void init()
    {
        srand(time(NULL));
        ptr ->left = ptr ->rig = dummy;
        ptr ->pri = -1;
        ptr ->size = 0;
        ptr ->data = -1e9;
        ptr ->best = -1e9;
        root = dummy = ptr;
        ptr++;
    }

    void update(struct Node *A)
    {
        A ->size = A ->left ->size + A ->rig ->size + 1;
        A ->best = max(A ->data, max(A ->left ->best, A ->rig ->best));
    }

    struct Node *rot(struct Node *A, struct Node *B)
    {
        if(A ->left == B) {
            A ->left = B ->rig;
            B ->rig = A;
        } else {
            A ->rig = B ->left;
            B ->left = A;
        }
        
        update(A);
        update(B);
        
        return B;
    }

    struct Node *insert_tree(struct Node *root, int data)
    {
        if(root == dummy) {
            ptr ->data = data;
            ptr ->best = data;
            ptr ->pri = rand();
            ptr ->size = 1;
            ptr ->left = ptr ->rig = dummy;
            return ptr++;
        } else if(root ->data < data) {
            root ->rig = insert_tree(root ->rig, data);
            if(root ->rig ->pri > root ->pri) { //Need Rotation
                root = rot(root, root ->rig);
            }
        } else {
            root ->left = insert_tree(root ->left, data);
            if(root ->left ->pri > root ->pri) {//Need rotation
                root = rot(root, root ->left);
            }
        }

        update(root);
        return root;    
    }

    struct Node *remove(struct Node *root, int data) 
    {
        if(root != dummy) {
            if(root ->data > data) {
                root ->left = remove(root ->left, data);
            } else if(root ->data < data) {
                root ->rig = remove(root ->rig, data);
            } else {
                if(root ->left == dummy && root ->rig == dummy) {
                    root = dummy;
                    return root;
                }
                        
                if(root ->left ->pri > root ->rig ->pri) {
                    root = rot(root, root ->left);
                } else {
                    root = rot(root, root ->rig);
                }
                        
                if(root != dummy) {
                    root = remove(root, data);
                } else {
                    root ->left = dummy;
                }
            }
        }
        update(root);
        return root;
    }

    int Find(struct Node *root, int K)
    {
        if(root ->left ->size > K) 
            return Find(root ->left, K);
        else if(root ->left ->size < K)
            return Find(root ->rig, K - root ->left ->size - 1);
        return root ->data;
    }

    int Count(struct Node *root, int data)
    {
        if(root == dummy)
            return 0;

        if(root ->data > data) {
            return Count(root ->left, data);
        } else if(root ->data < data) {
            return root ->left ->size + Count(root ->rig, data) + 1;
        }
        return root ->left ->size;
    }

    bool find(struct Node *root, int data)
    {
        if(root == dummy)
            return false;

        if(root ->data > data) {
            return find(root ->left, data);
        } else if(root ->data < data) {
            return find(root ->rig, data);
        } else
            return root ->data == data;
        }

    void insert(int data)
    {
        root = insert_tree(root, data);
    }

    void delet(int data)
    {
        root = remove(root, data);
    }

    int FindKth(int K)
    {
        if(root ->size <= K) {
            return -1;
        } else {
            return Find(root, K);
        }
    }

    int Count_Element(int x)
    {
        return Count(root, x);
    }
        
    vector<int> order(vector<int> Heights, vector<int> InFronts)
    {
        init();

        int sz = Heights.size();
        for(int i = 0; i < sz; ++i) {
            insert(i);
        }

        vector<pair<int, int> > vec;
        for(int i = 0; i < sz; ++i) {
            vec.push_back(make_pair(Heights[i], InFronts[i]));
        }
        sort(vec.begin(), vec.end());

        vector<int> Ans(sz, 0);

        for(int i = 0; i < sz; ++i) {
            int idx = FindKth(vec[i].second);
            Ans[idx] = vec[i].first;
            delet(idx);
        }

        return Ans;
    }
};

class aux
{
public:
    aux(int h, int i): height(h), infront(i)
    {

    }

    bool operator<(const aux& other) const
    {
        return (height > other.height);
    }

    int height;
    int infront;
};

vector<int> Solution::my_order(vector<int> &heights, vector<int> &infronts)
{
    vector<int> res;
    vector<aux> auxs;
    int size = heights.size();

    for (int i = 0; i < size; ++i)
        auxs.emplace_back(heights[i], infronts[i]);
    sort(auxs.begin(), auxs.end());
    for (auto& a: auxs)
        res.insert(res.begin()+a.infront, a.height);

    return res;
}

int main()
{
  Solution sol;
  vector<int> heights, infronts, res;
  
  // Expected: 5 3  2  1  6  4 
  heights =  {5, 3, 2, 6, 1, 4};
  infronts = {0, 1, 2, 0, 3, 2};

  // Expected: 49  62  21  27  92  90  59  86 
  heights =   {86, 92, 49, 21, 62, 27, 90, 59};
  infronts =  {2,  0,  0,  2,  0,  2,  1,  3 };

  // Expected: 62 35 30 23 82 67 29
  heights =  { 29, 82, 30, 62, 23, 67, 35 };
  infronts = { 5, 0, 2, 0, 3, 1, 1 };

  res = sol.order(heights, infronts);
  
  copy(res.begin(), res.end(), ostream_iterator<int>(cout, ","));

  return 0;
}

