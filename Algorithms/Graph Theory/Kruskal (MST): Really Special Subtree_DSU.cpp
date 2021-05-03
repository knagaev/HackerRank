#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class DsuMap
{
public:
    DsuMap() //: m_largest{ 0 } 
    {}

    DsuMap(int n) //: m_largest{ 0 } 
    {
        for (int i = 1; i < n + 1; ++i)
        {
            parent.insert({i, i});
            rank.insert({i, 0});
            volume.insert({i, 1});
            tops.insert(i);
        }
    }

    void make_set(int v)
    {
        parent[v] = v;
        rank[v] = 0;
        volume[v] = 1;
        tops.insert(v);
        //m_largest = max(m_largest, 1UL);
    }

    int find_set(int v)
    {
        if (parent.find(v) == end(parent))
            make_set(v);

        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            tops.erase(b);
            volume[a] += volume[b];
            //m_largest = max(m_largest, volume[a]);
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }

    int getVolume(int v)
    {
        return volume[v];
    }

    set<int> getTops()
    {
        return tops;
    }

    //size_t getLargest() { return m_largest; }
private:
    map<int, int> parent;
    map<int, int> rank;
    map<int, int> volume;
    set<int> tops;
    //size_t m_largest;
};


/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

 /*
  * For the weighted graph, <name>:
  *
  * 1. The number of nodes is <name>_nodes.
  * 2. The number of edges is <name>_edges.
  * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
  *
  */

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) 
{
    DsuMap dsu(g_nodes);

    auto comparator = [](const auto& lhs, const auto& rhs) 
    { 
        return lhs[2] > rhs[2]; 
    };
    priority_queue < vector<int>, vector<vector<int>>, decltype(comparator)> edges(comparator);
    auto itFrom = cbegin(g_from);
    auto itTo = cbegin(g_to);
    auto itWeight = cbegin(g_weight);
    for (; itFrom != cend(g_from) && itTo != cend(g_to) && itWeight != cend(g_weight); ++itFrom, ++itTo, ++itWeight)
    {
        edges.push({*itFrom, *itTo, *itWeight});
    }

    int result = 0;
    while(!edges.empty())
    {
        auto e = edges.top();
        edges.pop();

        //cout << e[0] << " " << e[1] << " " << e[2] << endl;

        auto leftTree = dsu.find_set(e[0]);
        auto rightTree = dsu.find_set(e[1]);

        if (leftTree != rightTree)
        {
            dsu.union_sets(e[0], e[1]);
            result += e[2];
        }
    }


    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    fout << res << endl;
    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
