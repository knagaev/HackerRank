#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, int val)
{
    map<int, set<int>> edges;

    for (size_t i = 0; i < graph_from.size(); ++i)
    {
        auto a = graph_from[i];
        auto b = graph_to[i];

        auto itA = edges.lower_bound(a);
        if (itA != end(edges) && !(edges.key_comp()(a, itA->first)))
        {
            itA->second.insert(b);
        }
        else
        {
            edges.insert(itA, map<int, set<int>>::value_type{ a, set<int>({b}) });
        }

        auto itB = edges.lower_bound(b);
        if (itB != end(edges) && !(edges.key_comp()(b, itB->first)))
        {
            itB->second.insert(a);
        }
        else
        {
            edges.insert(itB, map<int, set<int>>::value_type{ b, set<int>({a}) });
        }
    }

    set<int> nodesWithColor;
    for (size_t i = 0; i < ids.size(); ++i)
    {
        if (ids[i] == val)
            nodesWithColor.insert(i + 1);
    }

    map<int, set<int>> visited;
    deque<vector<long>> q; // node, distance
    for (const auto& n : nodesWithColor)
    {
        if (edges[n].empty()) continue;
        visited[n] = set<int>({ n });
        q.push_back({ n, 0L, n });
    }

    while (!q.empty())
    {
        auto curNode = q.front();
        q.pop_front();

        for (const auto& next : edges[curNode[0]])
        {
            if (visited[curNode[2]].find(next) != end(visited[curNode[2]])) continue;

            if (nodesWithColor.find(next) != end(nodesWithColor) && curNode[2] != next)
            {
                return curNode[1] + 1;
            }

            q.push_back({ next, curNode[1] + 1, curNode[2] });
            visited[curNode[2]].insert(next);
        }
    }

    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int graph_nodes;
    int graph_edges;

    cin >> graph_nodes >> graph_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> graph_from(graph_edges);
    vector<int> graph_to(graph_edges);

    for (int i = 0; i < graph_edges; i++) {
        cin >> graph_from[i] >> graph_to[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ids_temp_temp;
    getline(cin, ids_temp_temp);

    vector<string> ids_temp = split_string(ids_temp_temp);

    vector<long> ids(graph_nodes);

    for (int i = 0; i < graph_nodes; i++) {
        long ids_item = stol(ids_temp[i]);

        ids[i] = ids_item;
    }

    int val;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

    fout << ans << "\n";

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
