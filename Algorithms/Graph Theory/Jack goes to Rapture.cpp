#include <bits/stdc++.h>

using namespace std;
/*
 * Complete the 'getCost' function below.
 *
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

void getCost(const vector<vector<long>>& adjNodes, const vector<vector<long>>& adjWeights)
{
    auto g_nodes = adjNodes.size();

    vector<long> maxFares(g_nodes, numeric_limits<long>::max());
    maxFares[0] = numeric_limits<long>::min();

    queue<long> q({ 0 });
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();

        auto itNbNodes = cbegin(adjNodes[cur]);
        auto itEndNbNodes = cend(adjNodes[cur]);
        auto itNbWeights = cbegin(adjWeights[cur]);
        for (; itNbNodes != itEndNbNodes; ++itNbNodes, ++itNbWeights)
        {
            auto curMax = max(maxFares[cur], *itNbWeights);
            if (curMax < maxFares[*itNbNodes])
            {
                maxFares[*itNbNodes] = curMax;
                if(*itNbNodes < g_nodes - 1)
                    q.push(*itNbNodes);
            }
        }
    }

    if (maxFares[g_nodes - 1] == numeric_limits<long>::max())
        cout << "NO PATH EXISTS" << endl;
    else
        cout << maxFares[g_nodes - 1] << endl;

    return;
}

int main()
{
    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    auto end = g_nodes_edges_temp.find(" ");

    long g_nodes = stol(g_nodes_edges_temp.substr(0, end));
    long g_edges = stol(g_nodes_edges_temp.substr(end + 1));

    vector<vector<long>> adjNodes(g_nodes, vector<long>());
    vector<vector<long>> adjWeights(g_nodes, vector<long>());

    for (long i = 0; i < g_edges; i++) 
    {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        auto end = g_from_to_weight_temp.find(" ");
        auto end2 = g_from_to_weight_temp.find(" ", end + 1);

        long g_from_temp = stol(g_from_to_weight_temp.substr(0, end)) - 1;
        long g_to_temp = stol(g_from_to_weight_temp.substr(end + 1, end2)) - 1;
        long g_weight_temp = stol(g_from_to_weight_temp.substr(end2));

        adjNodes[g_from_temp].push_back(g_to_temp);
        adjWeights[g_from_temp].push_back(g_weight_temp);

        adjNodes[g_to_temp].push_back(g_from_temp);
        adjWeights[g_to_temp].push_back(g_weight_temp);
    }

    getCost(adjNodes, adjWeights);

    return 0;
}
