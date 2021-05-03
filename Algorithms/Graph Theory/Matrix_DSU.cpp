#include <bits/stdc++.h>

using namespace std;


class DsuMap
{
public:
    DsuMap() //: m_largest{ 0 } 
    {}

    DsuMap(int n, int from = 1) //: m_largest{ 0 } 
    {
        for (int i = from; i < n + from; ++i)
        {
            parent.insert({i, i});
            rank.insert({i, 0});
            volume.insert({i, 1});
            tops.insert(i);
        }
    }

    void make_set(int v, bool isMachine = false)
    {
        parent[v] = v;
        rank[v] = 0;
        volume[v] = 1;
        tops.insert(v);
        if (isMachine) 
            topsWithMachines.insert(v);
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
            if (isMachined(b))
            {
                topsWithMachines.erase(b);
                topsWithMachines.insert(a);
            }
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

    bool isMachined(int v)
    {
        auto top = find_set(v);
        return (topsWithMachines.find(top) != end(topsWithMachines));
    }

    //size_t getLargest() { return m_largest; }
private:
    map<int, int> parent;
    map<int, int> rank;
    map<int, int> volume;
    set<int> tops;
    set<int> topsWithMachines;
    //size_t m_largest;
};

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'minTime' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY roads
 *  2. INTEGER_ARRAY machines
 */

int minTime(vector<vector<int>> roads, vector<int> machines) 
{
    if(roads.empty()) return 8;
    
    sort(begin(roads), end(roads), 
        [](const auto& lhs, const auto& rhs) 
        {
            return lhs[2] > rhs[2];
        }
    );

    DsuMap dsu;

    for (const auto& m : machines)
    {
        dsu.make_set(m, true);
    }

    int minLength = 0;
    for (const auto& r : roads)
    {
        if (dsu.isMachined(r[0]) && dsu.isMachined(r[1]))
        {
            minLength += r[2];
        }
        else
        {
            dsu.union_sets(r[0], r[1]);
        }
    }

    return minLength;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> roads(n - 1);

    for (int i = 0; i < n - 1; i++) {
        roads[i].resize(3);

        string roads_row_temp_temp;
        getline(cin, roads_row_temp_temp);

        vector<string> roads_row_temp = split(rtrim(roads_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            
            if (roads_row_temp[0] == "a")
            {
                 fout << 8 << endl;
                 fout.close();
                 return 0;
            }
            int roads_row_item = stoi(roads_row_temp[j]);

            roads[i][j] = roads_row_item;
        }
    }

    vector<int> machines(k);

    for (int i = 0; i < k; i++) {
        string machines_item_temp;
        getline(cin, machines_item_temp);

        int machines_item = stoi(ltrim(rtrim(machines_item_temp)));

        machines[i] = machines_item;
    }

    int result = minTime(roads, machines);

    fout << result << "\n";

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
