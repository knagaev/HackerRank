/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/

bool has_cycle(Node* head) 
{
  if(head == nullptr || head->next == nullptr) return 0;
  
  Node* slow = head;
  Node* fast = head;
  
  while(true)
  {
    if(fast->next == nullptr || fast->next->next == nullptr) return 0;
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) return 1;
  }
  
}
