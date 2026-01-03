A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.

The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:

lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]

 

Example 1:


Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
Example 2:

Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]
 

Constraints:

1 <= buildings.length <= 104
0 <= lefti < righti <= 231 - 1
1 <= heighti <= 231 - 1
buildings is sorted by lefti in non-decreasing order.


•	The city skyline can be thought of as the outline you would see if you "swept" a vertical line from left to right across all buildings and tracked the highest point at every step.
•	Since building edges are the only places where the skyline can climb or fall, we only need to pay attention to start and end positions of every building.
•	As the sweep line moves, the set of "active" buildings (those the line is passing through) changes; the skyline at any x-coordinate is thus determined by the highest of these active buildings.
•	When a new building starts whose height is taller than current skyline, the skyline rises. When the tallest active building ends, the skyline may drop.
•	By walking through the events in order, we can efficiently know when the shape of the skyline changes and exactly where these key turns (the "critical points") occur.


•	Break each building into two events: a start (at left edge with height) and an end (at right edge with height).
•	Collect all events and sort them by x coordinate; for same x, start events (higher height first) come before end events (lower height first).
•	Sweep a line from left to right, processing each event in order.
•	Maintain a multiset/heap of active building heights as you go: insert height on start, remove height on end.
•	At each event, check the maximum active height (the skyline at that position) using the multiset’s largest value.
•	If the current maximum height is different than the previous one, it means the skyline “turns” here, so record [x, new height] as a key point in the result.
•	Only output new key points when the skyline actually changes to avoid duplicate flat sections.
•	When all buildings have ended, the skyline returns to ground level, so a final key point at height 0 is always included.


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {


        vector<pair<int,int>> events;
        for(auto& b: buildings){
            events.push_back({b[0],-b[2]});
            events.emplace_back(b[1],b[2]);
        }
        
        sort(events.begin(),events.end());

        vector<vector<int>> result;
        multiset<int> heights;
        heights.insert(0);
        int prevMaxHeight=0;

        for( auto& [x,h]:events){
          
          if(h<0){
            heights.insert(-h);
          }
          else{
            heights.erase(heights.find(h));
          }
          
          int currMaxHeight = *heights.rbegin();
          if(currMaxHeight!=prevMaxHeight){
                result.push_back({x,currMaxHeight});
                prevMaxHeight=currMaxHeight;
          }
        }

        return result;
    }
};
