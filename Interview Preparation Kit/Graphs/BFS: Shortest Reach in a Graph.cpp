#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <deque>
using namespace std;

class Graph 
{
public:
    Graph(int n) : n(n) {}

    void add_edge(int u, int v) 
    {
        auto itA = edges.lower_bound(u);
        if (itA != end(edges) && !(edges.key_comp()(u, itA->first)))
            itA->second.insert(v);
        else
            edges.insert(itA, map<int, set<int>>::value_type{ u, set<int>({v}) });

        auto itB = edges.lower_bound(v);
        if (itB != end(edges) && !(edges.key_comp()(v, itB->first)))
            itB->second.insert(u);
        else
            edges.insert(itB, map<int, set<int>>::value_type{ v, set<int>({u}) });
    }

    vector<int> shortest_reach(int start) 
    {
        // node, distance
        map<int, int> visited({ make_pair(start, 0) }); 
        deque<pair<int, int>> q({ make_pair(start, 0) }); // node, distance

        while (!q.empty())
        {
            auto curNode = q.front();
            q.pop_front();

            for (const auto& next : edges[curNode.first])
            {
                if (visited.find(next) != end(visited)) continue;

                q.push_back(make_pair(next, curNode.second + 1));
                visited[next] = curNode.second + 1;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; ++i)
        {
            auto it = visited.find(i);
            result.push_back(it != end(visited) ? it->second * 6 : -1);
        }
        
        return result;
    }
private:
    int n;
    map<int, set<int>> edges;
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
