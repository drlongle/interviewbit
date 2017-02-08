/*
Prime Numbers

Given a number N, find all prime numbers upto N ( N included ).

Example:

if N = 7,

all primes till 7 = {2, 3, 5, 7}

Make sure the returned array is sorted.

 */

import java.io.*;
import java.util.*;

public class Solution {

    public ArrayList<Integer> my_sieve(int a) {
        boolean[] prime = new boolean[a+1];
        Arrays.fill(prime, true);
        ArrayList<Integer> res = new ArrayList<>();
        if (a >= 2)
            res.add(2);
        for (int i = 3; i <= a; i += 2)
        {
            if (prime[i])
            {
                res.add(i);
                for (int mult = 2; mult*i <= a; ++mult)
                    prime[mult*i] = false;
            }
        }
        return res;
    }
    
    public ArrayList<Integer> sieve(int A) {
        boolean prime [] = new boolean[A + 1];
        Arrays.fill(prime, true);
        prime[0] = prime[1] = false;
        
        for (int i = 2; i <= A; i++) {
            if (!prime[i])
                continue;

            for (long j = 1L * i * i; j <= (long) A; j += i)
                prime[(int) j] = false;
        }

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i <= A; i++) {
            if (prime[i])
                res.add(i);
        }

        return res;
    }

    public static void main(String[] args)
    {
        Solution sol = new Solution();
        int n = 10;
        ArrayList<Integer> res = sol.sieve(n);
        res.forEach(i -> System.out.println(i));
    }
}

