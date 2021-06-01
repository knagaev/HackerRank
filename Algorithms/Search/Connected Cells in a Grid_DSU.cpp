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
 * Complete the 'connectedCell' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

int connectedCell(vector<vector<int>> matrix) 
{
    DsuMap dsu;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.size(); ++j)
        {
            if (matrix[i][j] == 1)
            {
                auto parent = dsu.find_set(i * matrix[i].size() + j);
                for (int a = -1; a < 2; ++a)
                {
                    if (i + a < 0 || i + a >= matrix.size()) continue;
                    for (int b = -1; b < 2; ++b)
                    {
                        if (j + b < 0 || j + b >= matrix[i].size() || (a == 0 && b == 0)) continue;
                        if (matrix[i + a][j + b] == 1)
                        {
                            dsu.union_sets(parent, (i + a) * matrix[i].size() + j + b);
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

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < m; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = connectedCell(matrix);

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
