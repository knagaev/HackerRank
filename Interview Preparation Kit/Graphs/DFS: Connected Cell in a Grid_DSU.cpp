#include <bits/stdc++.h>

using namespace std;

class DsuMap
{
public:
    DsuMap() //: m_largest{ 0 } 
    {}

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

// Complete the maxRegion function below.
int maxRegion(vector<vector<int>> grid) 
{
    DsuMap dsu;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid.size(); ++j)
        {
            if (grid[i][j] == 1)
            {
                auto parent = dsu.find_set(i * grid[i].size() + j);
                for (int a = -1; a < 2; ++a)
                {
                    if (i + a < 0 || i + a >= grid.size()) continue;
                    for (int b = -1; b < 2; ++b)
                    {
                        if (j + b < 0 || j + b >= grid[i].size() || (a == 0 && b == 0)) continue;
                        if (grid[i + a][j + b] == 1)
                        {
                            dsu.union_sets(parent, (i + a) * grid[i].size() + j + b);
                        }
                    }
                }
            }
                
        }
    }

    auto tops = dsu.getTops();
    int maxArea = 0;
    for (const auto& t : tops)
    {
        maxArea = max(maxArea, dsu.getVolume(t));
    }
    return maxArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    fout << res << "\n";

    fout.close();

    return 0;
}
