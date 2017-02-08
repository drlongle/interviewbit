/*
Word Break II

    Total Accepted: 59700
    Total Submissions: 293118
    Difficulty: Hard

Given a string s and a dictionary of words dict, add spaces in s to construct
a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

Make sure the strings are sorted in your result.

Access Hint:
Lets again look at the bruteforce solution.
You start exploring every substring from the start of the string, and check if
its in the dictionary. If it is, then you check if it is possible to form rest
of the string using the dictionary words. If yes, you append the current
substring to all the substring possible from rest of the string. If none of the
substrings qualify, then there are no sentences possible from this string.

So something like this :

vector<string> wordBreak(int index, string &s, unordered_set<string> &dict) {
                    // BASE CASES
        
        vector<string> sentences;
        // try to construct all substrings.
        for (int i = index; i < s.length(); i++) {
            substring = *the substring s[index..i] with i inclusive*
            if (dict contains substring) {
                                  vector<string> ret = wordBreak(i + 1, s, dict);
                foreach (sentence in ret) {
                    sentences.push_back(substring + " " + sentence);
                }          
            }
        }
        return sentences;
    }

This solution itself is exponential. However, do note that we are doing a lot of
repetitive work.
Do note, that index in the wordBreak function call can only take s.length()
number of values [0, s.length]. What if we stored the result of the function
somehow and did not process it everytime the function is called ?

*/

import java.io.*;
import java.util.*;

class StringComparator implements Comparator<String>
{
    @Override
    public int compare(String s1, String s2) {
        return s1.compareTo(s2);
    }
}

public class Solution {

    class Entry
    {
        Entry(int i, String w)
        {
            index = i;
            word = w;
        }

        int index;
        String word;
    }

    public ArrayList<String> getStrings(List<ArrayList<Entry>> entries,
        int index)
    {
        ArrayList<String> res = new ArrayList<String>();
        if (index == 0)
        {
            res.add(new String());
            return res;
        }

        HashSet<String> hash = new HashSet<>();
        List<String> ls;
        for (Entry e: entries.get(index))
        {
            ls = getStrings(entries, e.index);
            for (String s: ls)
            {
                String temp;
                if (s.isEmpty())
                    temp = e.word;
                else
                    temp = s + " " + e.word;
                if (hash.contains(temp) == false)
                {
                    hash.add(temp);
                    res.add(temp);
                }
            }
        }

        return res;
    }

    public ArrayList<String> my_wordBreak(String s, ArrayList<String> wordDict)
    {
        int len = s.length();
        if (len == 0 || wordDict.size() == 0)
            return new ArrayList<>();

        List<ArrayList<Entry>> res = new ArrayList<>();
        for (int i = 0; i <= len; ++i)
            res.add(new ArrayList<Entry>());

        for (int i = 0; i < len; ++i)
        {
            if (i != 0 && res.get(i).size() == 0)
                continue;
            for (String w : wordDict)
            {
                int wlen = w.length();
                if (i+wlen <= len && s.regionMatches(i, w, 0, wlen))
                    res.get(i+wlen).add(new Entry(i,w));
            }
        }

        ArrayList<String> result = getStrings(res, len);
        Collections.sort(result, new StringComparator());
        return result;
    }

    public ArrayList<String> wordBreak(String s, ArrayList<String> dict) {
	//create an array of ArrayList<String>
	Set<String> foo = new HashSet<>(dict);
        ArrayList<String> dp[] = new ArrayList[s.length()+1];
        dp[0] = new ArrayList<String>();

        for(int i=0; i<s.length(); i++){
            if( dp[i] == null ) 
                continue; 

            for(String word:foo){
                int len = word.length();
                int end = i+len;
                if(end > s.length()) 
                    continue;

                if(s.substring(i,end).equals(word)){
                    if(dp[end] == null){
                        dp[end] = new ArrayList<String>();
                    }
                    dp[end].add(word);
                }
            }
        }
     
        ArrayList<String> result = new ArrayList<String>();
        if(dp[s.length()] == null) 
            return result; 

        ArrayList<String> temp = new ArrayList<String>();
        dfs(dp, s.length(), result, temp);
        Collections.sort(result);
        return result;
    }

    private void dfs(List<String> dp[],int end,List<String> result,
        ArrayList<String> tmp){
        if(end <= 0){
            String path = tmp.get(tmp.size()-1);
            for(int i=tmp.size()-2; i>=0; i--){
                path += " " + tmp.get(i) ;
            }
 
            result.add(path);
            return;
        }
 
        for(String str : dp[end]){
            tmp.add(str);
            dfs(dp, end-str.length(), result, tmp);
            tmp.remove(tmp.size()-1);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ArrayList<String> dict;
        String s;
        ArrayList<String> result;

        dict = new ArrayList<String>(Arrays.asList("leet","code"));
        s = "leetcode";

        result = sol.wordBreak(s,dict);
        for (int i = 0; i < result.size(); ++i)
            System.out.println(i + " -> " + result.get(i));
    }
}

