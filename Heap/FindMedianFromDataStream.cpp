The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 

Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
 

Follow up:

If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
  ==================================================================================
Intuition
We want a way to quickly find the median as numbers arrive in any order.
Median is the "middle value" when data is sorted.
If we split data into two halves—lower (smaller numbers) and upper (larger numbers)—the median is either the max of lower, min of upper, or their average.
Main Logic
Keep two heaps:

maxHeap: max-heap for the lower half of all numbers (smaller numbers; root is biggest of smaller numbers).
minHeap: min-heap for the upper half (bigger numbers; root is smallest of bigger numbers).
Steps when adding a number:

Add to maxHeap — Always push new number to maxHeap.
Balance the halves — Pop the largest value from maxHeap and push it to minHeap.
Now, all values in maxHeap are ≤ values in minHeap.
Maintain size property:
If minHeap has more elements than maxHeap, move the smallest value from minHeap back to maxHeap.
This way, maxHeap always has equal or 1 more than minHeap.
Finding the median:

If total count is odd, maxHeap has 1 more element: median is maxHeap.top().
If total count is even, both are equal-sized: median is (maxHeap.top() + minHeap.top()) / 2.0.
Quick Intuitive Picture
maxHeap contains the smallest half of numbers (but biggest of them on top).
minHeap contains the largest half (but smallest of them on top).
This split is always kept balanced.
Max of small half and min of large half are always instantly available for computing the median.
Why does it work for ANY order?
New numbers, no matter their value, always start in maxHeap:
No need to check where they fit: the balancing steps will place them correctly.
The two heaps will always "wrap" the two halves around the middle of the sorted sequence.



  ==================================================================================

class MedianFinder {
public:
    
    priority_queue<int,vector<int>> maxHeap;
    priority_queue<int,vector<int>,greater<int>> minHeap;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
     
     maxHeap.push(num);

     minHeap.push(maxHeap.top());
     maxHeap.pop();

     if(maxHeap.size()<minHeap.size()){
        maxHeap.push(minHeap.top());
        minHeap.pop();
     }

    }
    
    double findMedian() {
        

        if(minHeap.size()<maxHeap.size()){
            return double(maxHeap.top());
        }
        else
            return double((minHeap.top()+maxHeap.top())/2.0);
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
