
/*The tree node has data, left child and right child 
class Node {
    int data;
    Node* left;
    Node* right;
};

*/
    int height(Node* root) 
    {
        if(root == nullptr) return -1;
        auto maxHeight = max(height(root->left) + 1, height(root->right) + 1);
        return maxHeight;
    }

