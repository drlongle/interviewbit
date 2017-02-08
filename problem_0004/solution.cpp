/*
Merge Intervals

Given a set of non-overlapping intervals, insert a new interval into the
intervals (merge if necessary). You may assume that the intervals were
initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9] insert and merge [2,5] would result in [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] would result in
[1,2],[3,10],[12,16].
This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

Make sure the returned intervals are also sorted.
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <string.h>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> my_insert(vector<Interval> &invals, Interval newIntval);
    bool overlap(const Interval& i1, const Interval i2)
    {
        if (i2.end < i1.start || i1.end < i2.start) return false;
        else return true;
    }

    Interval merge_intervals(const Interval& i1, const Interval& i2)
    {
        return Interval(min(i1.start,i2.start),max(i1.end,i2.end));
    }

    bool doesIntersect(Interval a, Interval b) {
        if (min(a.end, b.end) < max(a.start, b.start)) return false;
        else return true;
    }

    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
        int sz = intervals.size();
        vector<Interval> result;

        // Case : Empty intervals array
        if (sz == 0) {
            result.push_back(newInterval);
            return result;
        }
        // Case : newInterval comes at the beginning or at the end without
        // overlap
        if (newInterval.start > intervals[sz - 1].end ||
            newInterval.end < intervals[0].start) {
            if (newInterval.end < intervals[0].start)
                result.push_back(newInterval);

            for (int i = 0; i < sz; i++)
                result.push_back(intervals[i]);

            if (newInterval.start > intervals[sz - 1].end)
                result.push_back(newInterval);

            return result;
        }

        for (int i = 0; i < sz; i++) {
            bool intersect = doesIntersect(intervals[i], newInterval);
            if (!intersect) {
                result.push_back(intervals[i]);
                // check if newInterval lies between
                // intervals[i] and intervals[i+1]
                if (i < sz - 1 && newInterval.start > intervals[i].end &&
                    newInterval.end < intervals[i+1].start)
                    result.push_back(newInterval);
                continue;
            }
            // Now we know the interval overlaps. Lets find out how many
            // intervals overlap.
            int st = i;
            while (i < sz && intersect) {
                i++;
                if (i == sz) intersect = false;
                else
                    intersect = doesIntersect(intervals[i], newInterval);
            }
            i--;
            // Now all intervals from st to i overlap.
            Interval toInsert(min(newInterval.start, intervals[st].start),
                max(newInterval.end, intervals[i].end));
            result.push_back(toInsert);
        }
        return result;
    }
};

vector<Interval> Solution::my_insert(vector<Interval> &intervals,
    Interval newInterval) {
    int size = static_cast<int>(intervals.size());
    if (!size)
    {
        intervals.push_back(newInterval);
        return intervals;
    }

    if (newInterval.end < intervals.front().start)
    {
        intervals.insert(intervals.begin(), newInterval);
        return intervals;
    }
    if (newInterval.start > intervals.back().end)
    {
        intervals.push_back(newInterval);
        return intervals;
    }

    if (newInterval.start <= intervals.front().start &&
        newInterval.end >= intervals.back().end)
    {
        vector<Interval> result = {newInterval};
        return result;
    }

    vector<Interval>::iterator it = intervals.begin();
    while (it != intervals.end())
    {
        if (overlap(*it, newInterval))
        {
            newInterval = merge_intervals(*it, newInterval);
            vector<Interval>::iterator it2 = it + 1;
            while (it2 != intervals.end() && overlap(*it2, newInterval))
            {
                newInterval = merge_intervals(*it2, newInterval);
                ++it2;
            }
            it2 = intervals.erase(it, it2);
            intervals.insert(it2, newInterval);
            return intervals;
        }
        else
        {
            if (newInterval.start < it->start)
            {
                intervals.insert(it, newInterval);
                return intervals;
            }
            else
                ++it;
        }
    }
    intervals.insert(it, newInterval);

    return intervals;
}

int main()
{
    vector<Interval> intervals;
    Interval newInterval;
    intervals = {{1,3}, {6,9}};
    newInterval = {2,5};

    intervals = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    newInterval = {4,9};

    Solution sol;
    vector<Interval> result = sol.insert(intervals, newInterval);

    for (size_t i = 0; i < result.size(); ++i)
        cout<< "start: " << result[i].start << ", end: " <<result[i].end<<endl;

    return 0;
}

