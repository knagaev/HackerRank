#include <bits/stdc++.h>

using namespace std;

class Node
{
    public:
        Node(int payload, int level) : payload(payload), leftNode(nullptr), rightNode(nullptr), level(level) {}
        int payload;
        Node *leftNode, *rightNode;
        int level;
};

vector<int> inOrder(Node *node, vector<int>&& vec)
{
    auto result = vec;
    if (node != nullptr)
    {
        result = inOrder(node->leftNode, move(result));
        result.push_back(node->payload);
        result = inOrder(node->rightNode, move(result));
    }
    return result;
}

void swapLevels(vector<Node*>& tree, int k)
{
    int swapLevel = k;
    bool swapped = false;
    do {
        swapped = false;
        for (const auto& t : tree)
        {
            if (t->level == swapLevel)
            {
                swap(t->leftNode, t->rightNode);
                swapped = true;
            }
        }
        swapLevel += k;
    } while (swapped);
}


vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) 
{
    vector<Node*> tree;
    tree.push_back(new Node{ 1, 1 });
    
    auto i = 0;
    for (const auto& index : indexes)
    {
        if (index[0] > 0)
        {
            auto leftNode = new Node{ index[0], tree[i]->level + 1 };
            tree.push_back(leftNode);
            tree[i]->leftNode = leftNode;
        }

        if (index[1] > 0)
        {
            auto rightNode = new Node{ index[1], tree[i]->level + 1 };
            tree.push_back(rightNode);
            tree[i]->rightNode = rightNode;
        }

        ++i;
    }

    
    vector<vector<int>> result;

    for (const auto& q : queries)
    {
        /*
        vector<int> vec;
        vec = inOrder(*tree.begin(), move(vec));
        */
        swapLevels(tree, q);
        result.push_back(inOrder(*tree.begin(), vector<int>()));
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
