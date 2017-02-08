/*
Simplify Path  
Total Accepted: 51756 Total Submissions: 235024 Difficulty: Medium

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:
  Did you consider the case where path = "/../"?
  In this case, you should return "/".
  Another corner case is the path might contain multiple slashes '/' together,
  such as "/home//foo/". In this case, you should ignore redundant slashes and
  return "/home/foo".
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

int find_char(const string& st, const char ch, int pos)
{
    int nsize = st.size();
    for (int i = pos; i < nsize; ++i) {
        if (st[i] == ch)
            return i;
    }
    return -1;
}

class Solution {
public:
    string simplifyPath(string path) {
        vector<string>   nameVect;
        string name;

        path.push_back('/');

        for (int i = 0; i < path.size(); i++) {
            if (path[i] == '/') {
                if (name.size() == 0) continue;
                if (name == "..") { //special case 1: double dot, pop dir
                    if (nameVect.size() > 0) nameVect.pop_back();
                } else if (name == ".") {
                    //special case 2: single dot, don't push
                } else {          
                    nameVect.push_back(name);
                }
                name.clear();
            } else {
                name.push_back(path[i]);//record the name
            }
        }

        string result;
        if (nameVect.empty()) return "/";
        for (int i = 0; i < nameVect.size(); i++) {
            result.append("/" + nameVect[i]);
        }
        return result;
    }

    string my_simplifyPath(string path) {
        int pos = 0, next_pos;
        bool string_end = false;
        stack<string> parts;

        if (path[0] == '/') {
            parts.push("/");
            pos = 1;
        }
      
        while (!string_end) {
            next_pos = find_char(path, '/', pos);
            string part;
            if (next_pos >= 0) {
                part = path.substr(pos, next_pos-pos);
                pos = next_pos+1;
            }
            else {
                part = path.substr(pos);
                string_end = true;
            }

            if (part == "." || part.empty() ||
                (part == ".." && parts.size() && parts.top() == "/"))
                continue;
            if (part == ".." && parts.size())
                parts.pop();
            else
                parts.push(part);
        }

        vector<string> ss;
        while (parts.size()) {
            string s = parts.top();
            parts.pop();
            ss.emplace_back(s);
        }
        reverse(ss.begin(),ss.end());

        ostringstream oss;
        for (int i = 0; i < static_cast<int>(ss.size())-1; ++i) {
            oss << ss[i];
            if (ss[i] != "/")
                oss << "/";
        }
        if (ss.size())
            oss << ss.back();
        return oss.str();
    }
};

int main()
{
    Solution sol;
    string path, result;
  
    path = "/home/foo//";
    path = "/home/foo/../";
    path = "/..";

    result = sol.simplifyPath(path);
    cout << "Result: " << result << endl;

    return 0;
}
