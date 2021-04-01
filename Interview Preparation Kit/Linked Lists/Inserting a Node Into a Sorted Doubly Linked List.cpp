

// Complete the sortedInsert function below.

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
DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, int data) 
{
    if (head == nullptr)
    {
        auto newList = new DoublyLinkedList();
        newList->insert_node(data);
        return newList->head;
    }

    auto currentNode = head;
    while (data >= currentNode->data && currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }

    auto newNode = new DoublyLinkedListNode(data);
    if (data < currentNode->data)
    {
        auto prevNode = currentNode->prev;

        newNode->prev = prevNode;
        newNode->next = currentNode;

        currentNode->prev = newNode;
        if (prevNode != nullptr)
        {
            prevNode->next = newNode;
            return head;
        }
        return newNode;
    }
    else
    {
        newNode->prev = currentNode;
        currentNode->next = newNode;
        return head;
    }
}

