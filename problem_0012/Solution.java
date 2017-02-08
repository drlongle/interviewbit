/*
 Rearrange Array
 Rearrange a given array so that Arr[i] becomes Arr[Arr[i]] with O(1)
 extra space.
 */

import java.io.*;
import java.util.*;

public class Solution {
    public void arrange(ArrayList<Integer> A) {
        int n = A.size();
        for (int i = 0; i < n; i++)
            A.set(i, A.get(i) + (A.get(A.get(i)) % n) * n);
        for (int i = 0; i < n; i++)
            A.set(i, A.get(i) / n);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
    }
}
