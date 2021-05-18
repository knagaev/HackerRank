#include <bits/stdc++.h>

using namespace std;

struct Vertex
{
    char ch{'\0'};
    long parent{-1};
    array<long, 26> next{ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } };
    long suffixLink{-1};
    Vertex(char ch, long parent) : ch(ch), parent(parent), suffixLink(-1){}
    Vertex() = default;
};

class Bor
{
public:
    Bor() : stringsQty(0), vertexNum(0) { tree.push_back(Vertex('\0', -1)); }

    void AddString(long stringTag, const string& s);
    void Load(const string& s);
    long Transfer(long currentVertex, int nextChar);
    void CalcSuffixLinks();
    void PrintSuffixLinks();
    vector<long> Match(const string& s);
    long long GetHealth(const string& s, const vector<long>& healths, long first, long last, vector<vector<long>>& memoTransfer);
    size_t GetTreeSize();
private:
    vector<Vertex> tree;
    vector<vector<long>> leafMap;
    long stringsQty;
    long vertexNum;
};

void Bor::Load(const string& s)
{
    tree.reserve(s.size());
    leafMap.resize(s.size());

    long stringTag = 0;

    auto curVertex = 0;
    for (const auto ch : s)
    {
        if (ch == ' ')
        {
            leafMap[curVertex].push_back(stringTag);
            ++stringsQty;
            curVertex = 0;
            ++stringTag;
            continue;
        }
        if (tree[curVertex].next[ch - 'a'] == -1)
        {
            ++vertexNum;
            //tree[vertexNum] = move(Vertex(ch, curVertex));
            tree.push_back(move(Vertex(ch, curVertex)));
            tree[curVertex].next[ch - 'a'] = vertexNum;
        }
        curVertex = tree[curVertex].next[ch - 'a'];
    }
    leafMap[curVertex].push_back(stringTag);
    ++stringsQty;
}


void Bor::PrintSuffixLinks()
{
    deque<long> d;
    std::copy_if(begin(tree[0].next), end(tree[0].next), back_inserter(d), [](auto v) { return v > 0; });

    while (!d.empty())
    {
        auto curVertex = d.front();
        d.pop_front();
        std::copy_if(begin(tree[curVertex].next), end(tree[curVertex].next), back_inserter(d), [](auto v) { return v > 0; });

        cout << curVertex << ":" << tree[curVertex].ch << " . " << tree[curVertex].suffixLink << endl;
    }
}

void Bor::CalcSuffixLinks()
{
    deque<long> d;
    tree[0].suffixLink = -1;
    for (const auto& n : tree[0].next)
        if(n > 0) d.push_back(n);

    while (!d.empty())
    {
        auto curVertex = d.front();
        d.pop_front();
        for (const auto& n : tree[curVertex].next)
            if (n > 0) d.push_back(n);

        auto parent = tree[curVertex].parent;

        if (parent == 0)
        {
            tree[curVertex].suffixLink = 0;
        }
        else
        {
            auto curSuffix = tree[parent].suffixLink;
            while (true)
            {
                if (tree[curSuffix].next[tree[curVertex].ch - 'a'] > 0)
                {
                    tree[curVertex].suffixLink = tree[curSuffix].next[tree[curVertex].ch - 'a'];
                    break;
                }
                if (curSuffix == 0)
                {
                    tree[curVertex].suffixLink = 0;
                    break;
                }
                curSuffix = tree[curSuffix].suffixLink;
            }
        }
    }
    return;
}

size_t Bor::GetTreeSize()
{
    return vertexNum + 1;
}

long Bor::Transfer(long currentVertex, int nextChar)
{
    if (tree[currentVertex].next[nextChar] > 0)
        return tree[currentVertex].next[nextChar];
    else
    {
        auto suffixLink = tree[currentVertex].suffixLink;
        while (suffixLink > -1)
        {
            if (tree[suffixLink].next[nextChar] > 0)
                return tree[suffixLink].next[nextChar];

            suffixLink = tree[suffixLink].suffixLink;
        }
        return 0;
    }
}

long long Bor::GetHealth(const string& s, const vector<long>& healths, long first, long last, vector<vector<long>>& memoTransfer)
{
    long long totalHealth = 0;

    long curVertex = 0;
    for (const auto& ch : s)
    {
        if (memoTransfer[curVertex][ch - 'a'] == -1)
            memoTransfer[curVertex][ch - 'a'] = this->Transfer(curVertex, ch - 'a');

        curVertex = memoTransfer[curVertex][ch - 'a'];

        for (const auto& l : leafMap[curVertex])
        {
            if (l >= first && l <= last)
                totalHealth += healths[l];
        }

        auto curLink = tree[curVertex].suffixLink;
        while (curLink > 0)
        {
            if (!leafMap[curLink].empty())
            {
                for (const auto& l : leafMap[curLink])
                {
                    if (l >= first && l <= last)
                        totalHealth += healths[l];
                }
            }
            curLink = tree[curLink].suffixLink;
        }
    }

    return totalHealth;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(n_temp);

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    Bor bor;

    bor.Load(genes_temp_temp);
    bor.CalcSuffixLinks();

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<long> health(n);
    string health_string;
    size_t from = 0, to = 0, num = 0;
    for (; to < health_temp_temp.length(); ++to)
    {
        if (health_temp_temp[to] == ' ')
        {
            health_string.assign(health_temp_temp.c_str() + from, to - from);
            health[num++] = stol(health_string);
            from = to + 1;
        }
    }
    health_string.assign(health_temp_temp.c_str() + from, to - from);
    health[num++] = stol(health_string);

    string s_temp;
    getline(cin, s_temp);

    long s = stol(s_temp);

    long long minHealth = numeric_limits<long long>::max();
    long long maxHealth = numeric_limits<long long>::min();
    vector<vector<long>> memoTransfer(bor.GetTreeSize(), vector<long>(26, -1));
    string temp_arg;
    for (long s_itr = 0; s_itr < s; s_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        from = 0, to = 0;
        while (first_multiple_input_temp[++to] != ' ');

        temp_arg.assign(first_multiple_input_temp.c_str() + from, to - from);

        long first = stol(temp_arg);

        from = to + 1;
        while (first_multiple_input_temp[++to] != ' ');

        temp_arg.assign(first_multiple_input_temp.c_str() + from, to - from);
        long last = stol(temp_arg);

        from = to + 1;
        temp_arg.assign(first_multiple_input_temp.c_str() + from, first_multiple_input_temp.length() - from);

        long long totalHealth = bor.GetHealth(temp_arg, health, first, last, memoTransfer);
        minHealth = min(minHealth, totalHealth);
        maxHealth = max(maxHealth, totalHealth);
    }

    cout << minHealth << " " << maxHealth << endl;

    return 0;
}
