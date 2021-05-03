/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
    // pair<min, max>
    pair<int, int> getMinMax(Node* node)
    {
        //if (node->left == nullptr && node->right == nullptr) return {node->data, node->data};
        
        pair<int, int> fromLeft = {node->data, node->data};
        if(node->left != nullptr)
        {
            fromLeft = getMinMax(node->left);
            if(fromLeft.first < 0 || 
               fromLeft.second < 0 || 
               fromLeft.second >= node->data) 
                    return {-1, -1};
        }
        
        pair<int, int> fromRight = {node->data, node->data};
        if(node->right != nullptr)
        {
            fromRight = getMinMax(node->right);
            if(fromRight.first < 0 || 
               fromRight.second < 0 || 
               fromRight.first <= node->data) 
                    return {-1, -1};
        }
        
        //cout << node->data << " l:" << fromLeft.first << "," << fromLeft.second << " r:" << fromRight.first << "," << fromRight.second << endl; 
        
        return {min(fromLeft.first, fromRight.first), max(fromLeft.second, fromRight.second)};
   }

/*
    void printBST(Node* node) 
    {
        cout << node->data << " l:" << (node->left != nullptr ? node->left->data : -2) << " r:" << (node->right != nullptr ? node->right->data : -2) << endl;
        if(node->left != nullptr)
            printBST(node->left);
        if(node->right != nullptr)
            printBST(node->right);
    }

    bool checkBST(Node* root) 
    {
        printBST(root); 
        return true;
    }
*/
	bool checkBST(Node* root) 
    {
        //cout << root->data << " l:" << (root->left != nullptr ? root->left->data : -2) << " r:" << (root->right != nullptr ? root->right->data : -2) << endl; 
        
		if(root == nullptr) return true;
        
        if (root->left != nullptr)
        {
            auto fromLeft = getMinMax(root->left);
            if(fromLeft.first == -1 || 
               fromLeft.second == -1 ||
               fromLeft.second >= root->data)
                return false;
        }
        if (root->right != nullptr)
        {
            auto fromRight = getMinMax(root->right);
            if(fromRight.first == -1 || 
               fromRight.second == -1 ||
               fromRight.first <= root->data)
                return false;
        }
        
        return true;
	}
