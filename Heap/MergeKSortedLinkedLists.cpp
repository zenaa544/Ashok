You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.
https://leetcode.com/problems/merge-k-sorted-lists/description/

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
