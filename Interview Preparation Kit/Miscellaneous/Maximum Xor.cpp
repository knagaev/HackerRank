#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Trie 
{
    Trie* left;
    Trie* right;
    bool isLeaf;
    Trie() : left(nullptr), right(nullptr), isLeaf(false) {}
};

void insert(Trie* root, int x)
{
    Trie* temp = root;
    for (int i = 31; i >= 0; i--)
    {
        if (x & (1 << i))
        {
            if (temp->right == nullptr)
                temp->right = new Trie();
            temp = temp->right;
        }
        else
        {
            if (temp->left == nullptr)
                temp->left = new Trie();
            temp = temp->left;
        }
    }
    temp->isLeaf = true;
}

int search(Trie* root, int x)
{
    int result = 0;

    Trie* temp = root;
    for (int i = 31; i >= 0; i--)
    {
        if (x & (1 << i))
        {
            if (temp->left != nullptr && temp->isLeaf == false)
            {
                result = result + pow(2, i);
                temp = temp->left;
            }
            else
                temp = temp->right;
        }
        else
        {
            if (temp->right != nullptr && temp->isLeaf == false)
            {
                result = result + pow(2, i);
                temp = temp->right;
            }
            else
                temp = temp->left;
        }
    }
    return result;
}

vector<int> maxXor(vector<int> arr, vector<int> queries)
{
    Trie* root = new Trie();

    for (const auto& a : arr)
        insert(root, a);

    vector<int> result;
    for (const auto& q : queries)
        result.push_back(search(root, q));

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(m);

    for (int i = 0; i < m; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<int> result = maxXor(arr, queries);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
