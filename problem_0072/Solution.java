/*
Word Break

Given a string s and a dictionary of words dict, determine if s can be
segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].
Return 1 because "leetcode" can be segmented as "leet code". 

s = "myinterviewtrainer",
dict = ["trainer", "my", "interview"].

Return 1 ( corresponding to true ) because "myinterviewtrainer" can be segmented as "my interview trainer".

Return 0 / 1 ( 0 for false, 1 for true ) for this problem

Access Hint

Lets again look at the bruteforce solution.
You start exploring every substring from the start of the string, and check if
it is in the dictionary. If it is, then you check if it is possible to form
rest of the string using the dictionary words. If yes, my answer is true. If
none of the substrings qualify, then our answer is false.

So something like this :

    bool wordBreak(int index, string &s, unordered_set<string> &dict) {
                    // BASE CASES
        
        bool result = false;
        // try to construct all substrings.
        for (int i = index; i < s.length(); i++) {
            substring = *the substring s[index..i] with i inclusive*
            if (dict contains substring) {
                result |= wordBreak(i + 1, s, dict); // If true, we are done. 
            }
        }
        return result;
    }

This solution itself is exponential. However, do note that we are doing a lot of
repetitive work.
Do note, that index in the wordBreak function call can only take s.length()
number of values [0, s.length]. What if we stored the result of the function
somehow and did not process it everytime the function is called ?

*/

import java.io.*;
import java.util.*;

public class Solution {
    public int my_wordBreak(String s, ArrayList<String> stringList) {
        Set<String> wordDict = new HashSet<>();
        wordDict.addAll(stringList);

        int len = s.length();
        if (len == 0 || wordDict.contains(s)) return 1;
        boolean[] res = new boolean[len];

        for (int i = len-1; i >= 0; --i)
        {
            res[i] = false;
            if (wordDict.contains(s.substring(i)))
                res[i] = true;
            for (int j = i+1; j < len && !res[i]; ++j)
            {
                if (res[j] && wordDict.contains(s.substring(i,j)))
                    res[i] = true;
            }
        }

        return res[0] ? 1 : 0;
    }

    public int wordBreak(String s, ArrayList<String> B) {
        boolean[] t = new boolean[s.length()+1];
        t[0] = true; //set first to be true, why?
        //Because we need initial state
        Set<String> dict = new HashSet<>(B);
        for(int i=0; i<s.length(); i++) {
            //should continue from match position
            if(!t[i]) 
                continue;
 
            for(String a: dict){
                int len = a.length();
                int end = i + len;
                if(end > s.length())
                    continue;
 
                if(t[end]) continue;
 
                if(s.substring(i, end).equals(a)){
                    t[end] = true;
                }
            }
        }
 
        return t[s.length()]?1:0;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ArrayList<String> dict;
        String s;

        dict = new ArrayList<String>(Arrays.asList("leet","code"));
        s = "leetcode";
        s = "leetcodei";

        System.out.println("Result: " + sol.wordBreak(s,dict));
    }
}

