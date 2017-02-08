/*
Spiral Order Matrix I

Given a matrix of m * n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example:

Given the following matrix:

[
    [ 1, 2, 3 ],
    [ 4, 5, 6 ],
    [ 7, 8, 9 ]
]

You should return

[1, 2, 3, 6, 9, 8, 7, 4, 5]
*/

import java.io.*;
import java.util.*;

public class Solution {

    public ArrayList<Integer> my_spiralOrder(
        final List<ArrayList<Integer>> matrix)
    {
        ArrayList<Integer> res = new ArrayList<Integer>();

        int m = matrix.size();
        if (m == 0) return res;
        int n = matrix.get(0).size();
        if (n == 0) return res;

        for (int i = 0; i < m/2; ++i)
        {
            for (int j = i; j < n-i; ++j)
            {
                res.add(matrix.get(i).get(j));
            }

            for (int j = i+1; j < m-1-i && 2*i <= n-1; ++j)
            {
                res.add(matrix.get(j).get(n-1-i));
            }

            for (int j = n-1-i; j >= i; --j)
            {
                res.add(matrix.get(m-1-i).get(j));
            }

            for (int j = m-2-i; j > i && 2*i < n-1; --j)
            {
                res.add(matrix.get(j).get(i));
            }
        }

        if ((m & 1) != 0)
        {
            int i = m >> 1;
            for (int j = i; j < n-i; ++j)
            {
                res.add(matrix.get(i).get(j));
            }
        }

        return res;
    }

    public ArrayList<Integer> spiralOrder(final List<ArrayList<Integer>> A) {
        ArrayList<Integer> result = new ArrayList<Integer>();

	int m, n;
	m = A.size();
	n = A.get(0).size();

        if (m == 0)
	    return result;
	int len;
	int dir = 0; // right
	int row, col, layer;
	row = col = layer = 0;
	result.add(A.get(0).get(0));

        for (int step = 1; step < m * n; step++) {
            switch(dir) {
                // Go right
                case 0:
                    if (col == n - layer - 1) {
                        dir = 1;
                        row++;
                    } else {
                        col++;
                    }
                    break;
                    
                // Go down
                case 1:
                    if (row == m - layer - 1) {
                        dir = 2;
                        col--;
                    } else {
                        row++;
                    }
                    break;
                    
                // Go left
                case 2:
                    if (col == layer) {
                        dir = 3;
                        row--;
                    } else {
                        col--;
                    }
                    break;
                
                // Go up
                case 3:
                    if (row == layer + 1) {
                        dir = 0;
                        col++;
                        layer++;
                    } else {
                        row--;
                    }
                    break;
            }
            
            result.add(A.get(row).get(col));
        }
        
        return result;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
    }
}

