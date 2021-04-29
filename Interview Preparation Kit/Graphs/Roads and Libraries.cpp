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

    void make_set(long long v)
    {
        parent[v] = v;
        rank[v] = 0;
        volume[v] = 1;
        tops.insert(v);
        //m_largest = max(m_largest, 1UL);
    }

    int find_set(long long v)
    {
        if (parent.find(v) == end(parent))
            make_set(v);

        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(long long a, long long b)
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

    long long getVolume(long long v)
    {
            return volume[v];
    }

    set<long long> getTops()
    {
        return tops;
    }

    //size_t getLargest() { return m_largest; }
private:
    map<long long, long long> parent;
    map<long long, long long> rank;
    map<long long, long long> volume;
    set<long long> tops;
    //size_t m_largest;
};


/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) 
{
    if (c_lib < c_road)
        return static_cast<long long>(c_lib) * n;

    DsuMap dsu;

    for (const auto& link : cities)
    {
        dsu.union_sets(link[0], link[1]);
    }

    long long  total = 0;
    long long  chained = 0;
    for (const auto& t : dsu.getTops())
    {
        auto volume = dsu.getVolume(t);
        total += (volume - 1) * c_road + c_lib;
        chained += volume;
    }

    total += (n - chained) * c_lib;

    return total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

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
