

/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode_huff(node * root, string s) 
{
    vector<char> result;
    auto currentNode = root;
    for (const auto& c : s)
    {
        currentNode = (c == '0') ? currentNode->left : currentNode->right;

        if (currentNode->data != '\0')
        {
            result.push_back(currentNode->data);
            currentNode = root;
        }
    }

    copy(begin(result), end(result), ostream_iterator<char>(cout));
    return;
    
}

