/*
Shortest Unique Prefix

Find shortest unique prefix to represent each word in the list.

Input: [zebra, dog, duck, dove]
Output: {z, dog, du, dov}
where we can see that
zebra = z
dog = dog
duck = du
dove = dov

NOTE : Assume that no word is prefix of another. In other words, the representation is always possible. 

Hint : Prefix tree or Trie ( https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/ )

Assume you have all the prefixes of the word stored in the tree along with their frequencies. Is it possible to arrive at the solution now ?


Lets take an example:

input: ["zebra", "dog", "duck", "dot"]

Now we will build prefix tree and we will also store count of characters

                root
                /|
         (d, 3)/ |(z, 1)
              /  |
          Node1  Node2
           /|        \
     (o,2)/ |(u,1)    \(e,1)
         /  |          \
   Node1.1  Node1.2     Node2.1
      | \         \            \
(g,1) |  \ (t,1)   \(c,1)       \(b,1)
      |   \         \            \
    Leaf Leaf       Node1.2.1     Node2.1.1
    (dog)  (dot)        \                  \
                         \(k, 1)            \(r, 1)
                          \                  \
                          Leaf               Node2.1.1.1
                          (duck)                       \
                                                        \(a,1)
                                                         \
                                                         Leaf
                                                         (zebra)

Now, for every leaf / word , we find the character nearest to the root with frequency as 1. 
The prefix that the path from root to this character corresponds to, is the representation of the word. 

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std;

class TrieNode
{
public:
    TrieNode(TrieNode* parent, string prefix):
        m_parent(parent), m_prefix(prefix), m_word_count(0)
    {

    }

    TrieNode* find(char ch)
    {
        map<char,TrieNode*>::iterator it = m_children.find(ch);
        return it == m_children.end() ? 0 : it->second;
    }

    TrieNode* insert(char ch)
    {
        TrieNode* child = new TrieNode(this, m_prefix + ch);
        m_children[ch] = child;
        return child;
    }

    map<char, TrieNode*> m_children;
    TrieNode* m_parent;
    string m_prefix;
    int m_word_count;
};

class MyTrie
{
public:
    MyTrie(): m_root(new TrieNode(NULL, "")) { }

    void insert(string& word)
    {
        TrieNode* node = m_root;
        int wsize = word.size();
        for (int i = 0; i < wsize; ++i)
        {
            char ch = word[i];
            TrieNode* child = node->find(ch);
            if (!child)
                child = node->insert(ch);
            node = child;
        }

        while (node)
        {
            ++node->m_word_count;
            node = node->m_parent;
        }
    }

    string find_unique_prefix(string& word)
    {
        TrieNode* node = m_root;
        int i, wsize = word.size();
        for (i = 0; i < wsize && node && node->m_word_count > 1; ++i)
            node = node->find(word[i]);

        return node->m_prefix;
    }

    TrieNode* m_root;
};

class Solution {
public:
    vector<string> my_prefix(vector<string> &words) ;

    int IDX;
    vector<vector<int> > Cnt;
    vector<vector<int> > Trie;
    
    void insert(string str)
    {
        int len = str.size();
        int root = 0;
        int i = 0;

        while(i < len) {
            int chr = str[i] - 'a';
            if(Trie[root][chr] == -1) {
                ++IDX;
                Trie[root][chr] = IDX;
                Cnt[root][chr] = 1;
            } else {
                Cnt[root][chr]++;
            }
            root = Trie[root][chr];
            i++;
        }
    }

    string Query(string str) 
    {
        int root = 0;
        string ans = "";
        int i = 0;
        int len = str.size();

        while(i < len) {
            int chr = str[i] - 'a';
            ans += str[i];
            if(Cnt[root][chr] == 1)
                return ans;
            root = Trie[root][chr];
            i++;
        }
        return "";
    }

    vector<string> prefix(vector<string> Vec)
    {
        int mx_len = 0;
        int N = Vec.size();
        for(int i = 0; i < N; ++i) {
            mx_len = max(mx_len, (int)Vec[i].size());
        }

        Trie.clear();
        Cnt.clear();
        Trie.resize(N * mx_len + 1, vector<int>(27, -1));
        Cnt.resize(N * mx_len + 1, vector<int>(27, -1));
        IDX = 0;

        for(int i = 0; i < N; ++i) {
            insert(Vec[i]);
        } 

        vector<string> Ans;
        for(int i = 0; i < N; ++i) {
            string ans = Query(Vec[i]);
            Ans.push_back(ans); 
        }

        return Ans;
    }
};

vector<string> Solution::my_prefix(vector<string> &words) {
    vector<string> res;
    MyTrie trie;
    for (auto& w: words)
        trie.insert(w);

    for (auto& w: words)
        res.emplace_back(trie.find_unique_prefix(w));

    return res;
}

int main()
{
    Solution sol;
    vector<string> words, res;

    // {z, dog, du, dov}
    words = {"zebra", "dog", "duck", "dove"};

    // bea ber 
    words = {"bearcat", "bert" };

    res = sol.prefix(words);
    copy(res.begin(), res.end(), ostream_iterator<string>(cout, ","));
    cout << endl;

    return 0;
}

