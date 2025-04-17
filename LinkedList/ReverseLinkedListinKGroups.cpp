/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // Reverses first k nodes starting from head, sets nextGroupHead to the next node after reversed group
    ListNode* reverseFirstK(ListNode* head, int k, ListNode*& nextGroupHead) {
        if (k == 1) {
            nextGroupHead = head->next;
            return head;
        }

        ListNode* newHead = reverseFirstK(head->next, k - 1, nextGroupHead);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        // Count if there are at least k nodes left to reverse
        ListNode* temp = head;
        int count = 0;
        while (temp && count < k) {
            count++;
            temp = temp->next;
        }

        if (count < k) return head; // Not enough nodes to reverse

        // Reverse first k nodes
        ListNode* nextGroupHead = nullptr;
        ListNode* newHead = reverseFirstK(head, k, nextGroupHead);

        // head is now the tail of reversed group
        head->next = reverseKGroup(nextGroupHead, k);

        return newHead;
    }
};
===================================

    Iterative
    temp=head;
    prevLast=null;
    while(temp!=NULL){
        kthNode= getKthNode(tmep,k);
    }
    if(kthNode==NULL)
        if(prevLast) prevLast->next=temp;
          break;
    }
    nextNode= kthNode->next;
    kthNode->next=NULL;
    reverse(temp);
    if(temp==head)
         head=kthNode;
    else
        prevLast-.next=kthNode;

    prevLast=temp;
    temp=nextNode

}//while

return head;
