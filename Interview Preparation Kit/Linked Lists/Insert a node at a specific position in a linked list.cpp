

// Complete the insertNodeAtPosition function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* head, int data, int position) 
{
    auto newNode = new SinglyLinkedListNode(data);
    if(head == nullptr)
        return newNode;
        
    if (position == 0)
    {
        newNode->next = head;
        return newNode;
    }
    
    int i = 0;
    auto currNode = head;
    while(i < position - 1)
    {
        currNode = currNode->next;
        ++i;
    }
    newNode->next = currNode->next;
    currNode->next = newNode;
    return head;
}

