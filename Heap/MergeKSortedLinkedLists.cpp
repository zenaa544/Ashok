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
