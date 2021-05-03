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

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

long long journeyToMoon(int n, vector<vector<int>> astronaut) 
{
    DsuMap dsu(n, 0);

    for (const auto& a : astronaut)
    {
        dsu.union_sets(a[0], a[1]);
    }

    long long currentSum = 0;
    long long result = 0;
    for (const auto& t : dsu.getTops())
    {
        auto volume = dsu.getVolume(t);
        result += currentSum * volume;
        currentSum += volume;
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int p = stoi(first_multiple_input[1]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    long long result = journeyToMoon(n, astronaut);

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
