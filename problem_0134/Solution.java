/*
59. Spiral Order Matrix II

    Total Accepted: 56688
    Total Submissions: 158350
    Difficulty: Medium

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
For example,
Given n = 3,
You should return the following matrix:

[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

*/

import java.io.*;
import java.util.*;

public class Solution {

    public int[][] generateMatrix(int n) {
        int[][] res = new int[n][n];
        int running = 1;

        for (int i = 0; i < n/2; ++i)
        {
            for (int j = i; j < n-i; ++j)
                res[i][j] = running++;

            for (int j = i+1; j < n-i-1; ++j)
                res[j][n-1-i] = running++;

            for (int j = n-i-1; j >= i; --j)
                res[n-i-1][j] = running++;

            for (int j = n-i-2; j > i; --j)
                res[j][i] = running++;
        }

        if ((n & 1) != 0)
        {
            int mid = n >> 1;
            res[mid][mid] = running;
        }

        return res; 
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] res;

        res = sol.generateMatrix(3);

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < res.length; ++i)
        {
            for (int j = 0; j < res[i].length; ++j)
            {
                sb.append(res[i][j]);
                sb.append("\t");
            }
            sb.append("\n");
        }

        System.out.println(sb);
    }
}

