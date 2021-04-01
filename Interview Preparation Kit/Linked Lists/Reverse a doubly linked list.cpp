

// Complete the reverse function below.

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */
DoublyLinkedListNode* reverse(DoublyLinkedListNode* head) 
{
    if (head == nullptr) return head;

    auto currentNode = head;

    while (currentNode->next != nullptr)
    {
        swap(currentNode->next, currentNode->prev);

        currentNode = currentNode->prev;
    }
    swap(currentNode->next, currentNode->prev);

    return currentNode;
}

