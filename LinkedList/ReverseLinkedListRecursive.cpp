class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // Base case: if head is NULL or only one node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Recursively reverse the rest of the list
        ListNode* newHead = reverseList(head->next);

        // Put current head at the end
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};
