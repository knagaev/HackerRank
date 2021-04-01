

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) 
{
    set<SinglyLinkedListNode*> ptrs1, ptrs2;

    auto currentNode1 = head1;
    auto currentNode2 = head2;

    while (currentNode1 != nullptr || currentNode2 != nullptr)
    {
        if (currentNode1 != nullptr)
        {
            ptrs1.insert(currentNode1);
            auto foundNode1 = ptrs2.find(currentNode1);
            if (foundNode1 != ptrs2.end())
            {
                return currentNode1->data;
            }
        }

        if (currentNode2 != nullptr)
        {
            ptrs2.insert(currentNode2);
            auto foundNode2 = ptrs1.find(currentNode2);
            if (foundNode2 != ptrs1.end())
            {
                return currentNode2->data;
            }
        }

        if(currentNode1->next != nullptr)
            currentNode1 = currentNode1->next;
        if (currentNode2->next != nullptr)
            currentNode2 = currentNode2->next;
    }

    return 0;
}

