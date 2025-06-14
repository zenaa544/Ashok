You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.
https://leetcode.com/problems/merge-k-sorted-lists/description/


Following 2 solutions are bruteforce solutions with TC O(n log m) ;
For optimal solution with heap check last one.TC (n log k)

n	Total number of all nodes across all k linked lists
k	Number of input linked lists
m	Number of unique values across all nodes (used in the map<int, ...> methods)

ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head(INT_MIN, nullptr); // Dummy head node
        for (int i = 0; i < lists.size(); i++) {
            ListNode* ptr1 = lists[i];
            ListNode* ptr2 = head.next;
            ListNode* dummy = &head; // 🔁 Reset dummy every iteration

            head.next = nullptr; // 🔁 Clear old result before re-building it

            while (ptr1 && ptr2) {
                if (ptr1->val > ptr2->val) {
                    dummy->next = ptr2;
                    ptr2 = ptr2->next;
                } else {
                    dummy->next = ptr1;
                    ptr1 = ptr1->next;
                }
                dummy = dummy->next;
            }
            dummy->next = ptr1 ? ptr1 : ptr2;
        }
        return head.next;

    }
=======================================================
    map<int,list<ListNode*>> nodeMap;

    // Step 1: Bucket all nodes into map
    for (ListNode* list : lists) {
        while (list) {
            ListNode* next = list->next;
            list->next = nullptr;  // disconnect
            nodeMap[list->val].push_back(list);
            list = next;
        }
    }

    // Step 2: Stitch all nodes in order
    ListNode dummy(0);
    ListNode* tail = &dummy;

    for (auto& [val, nodeList] : nodeMap) {
        for (ListNode* node : nodeList) {
            tail->next = node;
            tail = tail->next;
        }
    }

    return dummy.next;
    }
==================================================

🔄 Logic to Merge k Sorted Lists Using a Min-Heap:

Use a min heap to keep all nodes in ascending order, so that when pop you get
the smallest node value, and build the linklist connecting one by one from min heap.

        priority_queue is max heap by default, to make it mean heap you need to create custom comparator
             std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

        
Create an empty min-heap (priority queue) that stores nodes by their value.
Push the head of each non-empty list into the heap.
Initialize a dummy node to serve as the starting point of the result list.
Set a pointer tail to the dummy node.
This will track the end of the merged list.
While the heap is not empty:
        a. Pop the node with the smallest value from the heap.
        b. Append this node to tail->next.
        c. Move tail to this node.
        d. If the popped node has a next, push that next node into the heap.

Once the heap is empty, all nodes are merged — return dummy->next as the head of the new sorted list.

class Solution {

    struct Compare{
        bool operator()(ListNode* a, ListNode* b){
            return a->val>b->val;
        }
    };
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode* , vector<ListNode*>,Compare>minHeap;

        for(auto list:lists){

            if(list!=nullptr)
            minHeap.push(list); 
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;

        while(!minHeap.empty()){

            ListNode* top = minHeap.top();
            minHeap.pop();
            tail->next=top;
            tail=tail->next;
            if(top->next)
            minHeap.push(top->next);
            tail->next=nullptr;//for safety not strictly neceseery

        }
        return dummy.next;
    }
};
