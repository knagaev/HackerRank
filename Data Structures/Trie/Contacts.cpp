#include <bits/stdc++.h>

using namespace std;

class TrieNode
{
public: 
    TrieNode* children[26];
    int quantity;
};

class Contacts
{
private:
    TrieNode* head;
    TrieNode* findNode(string prefix);

public:
    Contacts() : head(new TrieNode()) {}

    TrieNode* addContact(string contact);
    int countContacts(string contact);
};

TrieNode* Contacts::addContact(string contact)
{
    TrieNode* current = this->head;

    auto it = cbegin(contact);
    while (it != cend(contact))
    {
        ++(current->quantity);
        
        size_t i = *it - 'a';
        if (current->children[i] == nullptr)
            break;

        current = current->children[i];
        ++it;
    }

    while (it != cend(contact))
    {
        size_t i = *it - 'a';
        current->children[i] = new TrieNode();
        current->children[i]->quantity = 1;
        current = current->children[i];
        ++it;
    }

    return this->head;
};

TrieNode* Contacts::findNode(string prefix)
{
    TrieNode* current = this->head;

    auto it = cbegin(prefix);
    while (it != cend(prefix))
    {
        size_t i = *it - 'a';
        if (current->children[i] == nullptr)
            return nullptr;
        else
            current = current->children[i];

        ++it;
    }

    return current;
}

int Contacts::countContacts(string prefix)
{
    auto current = findNode(prefix);
    if (current == nullptr) return 0;

    return current->quantity;
}

/*
 * Complete the contacts function below.
 */
vector<int> contacts(vector<vector<string>> queries) 
{
    vector<int> counter;
    
    auto contacts = make_unique<Contacts>();
    for(const auto& q : queries)
    {
        if (q[0] == "add")
        {
            contacts->addContact(q[1]);
        }

        if (q[0] == "find")
        {
            counter.push_back(contacts->countContacts(q[1]));
        }
    }
    
    return counter;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
