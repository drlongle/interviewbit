
import java.io.*;
import java.util.*;

public class Solution {
    public int searchInsert(ArrayList<Integer> A, int B) {
        int size = A.size();
        int index;
        index = lowerBound(A, 0, size - 1, B);

        if (index != -1)
            return index;

        for (int i = 0; i < size; i++) {
            if (A.get(i) > B)
                break;
            index = i;
        }

        return index + 1;
    }
	
    public int lowerBound(final List<Integer> A, int start, int end, int num) {
        int steps = end - start + 1;
        int mid;
        int low = -1;
        int val;

        while (steps > 0) {
            mid = (start + end) / 2;
            val = A.get(mid);
            if (num < val) {
                end = mid - 1;
            } else if (num > val) {
                start = mid + 1;
            } else {
                low = mid;
                end = mid - 1;
            }
            steps /= 2;
        }
        return low;
    }

  public static void main(String[] args) {
      Solution sol = new Solution();
  }
}
