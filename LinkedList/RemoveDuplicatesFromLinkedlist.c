/* Outer loop traverses each node one by one current=current->next
Check all nodes from head till current in another loop
if found duplicate then remove current node

NOTE: DONT Do any operations on list inside inner loop;
Removal of node has to be done in outer loop to correctly keep track of previous node
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node* removeDuplicates_keepFirst(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *runner = current->next;
        Node *prev = current;  // prev is always just before runner
        while (runner != NULL) {
            if (runner->data == current->data) {
                // Duplicate found after current, remove runner
                Node *to_del = runner;
                prev->next = runner->next; // unlink runner
                runner = runner->next;     // move to the next node
                free(to_del);              // free removed node
                // prev stays at the same position
            } else {
                // advance both pointers
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return head;
}
********************************************
Node* removeDuplicates_keepLast(Node *head) {
    Node dummy;
    dummy.data = -1;
    dummy.next = head;
    Node *current = head;
    while(current != NULL) {
        Node *runner = dummy.next;
        Node *prev = &dummy;
        while(runner != current) {
            if(runner->data == current->data) {
                Node *to_del = runner;
                prev->next = runner->next;
                runner = runner->next;
                free(to_del);
                break; // Remove only one previous
            } else {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return dummy.next;
}

***********************************************
#include <stdbool.h>
#define SIZE 1000 // (for small ranges; for large/unbounded, use a real hashset)

Node* removeDuplicates_hash(Node *head) {
    bool found[SIZE] = {0};
    Node dummy;
    dummy.data = -1;
    dummy.next = head;
    Node *prev = &dummy;
    Node *current = head;
    while(current != NULL) {
        if(found[current->data]) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            found[current->data] = 1;
            prev = current;
            current = current->next;
        }
    }
    return dummy.next;
}
