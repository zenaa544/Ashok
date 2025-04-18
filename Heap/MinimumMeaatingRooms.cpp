https://leetcode.com/problems/meeting-rooms-ii/description/
253. Meeting Rooms II
Solved
Medium
Topics
Companies
Hint
Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

 

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1



  💡 Intuition:
We need a new room whenever a meeting starts before the earliest ended meeting has finished.

Sort all meetings by their start time.

Use a min-heap to track the end times of ongoing meetings.

If the current meeting can reuse a room (i.e., starts after or when another ends), pop that room’s end time.

Push the current meeting's end time to the heap.

✅ C++ Solution (Using Priority Queue):
cpp
Copy
Edit
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;

    // Sort by start time
    sort(intervals.begin(), intervals.end());

    // Min-heap to keep track of meeting end times
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Add the end time of the first meeting
    minHeap.push(intervals[0][1]);

    for (int i = 1; i < intervals.size(); ++i) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        // If the earliest ending meeting is done before the current starts, reuse the room
        if (start >= minHeap.top()) {
            minHeap.pop();
        }

        // Allocate a new room (or reuse the one we just popped)
        minHeap.push(end);
    }

    // The size of the heap is the number of rooms needed
    return minHeap.size();
}
