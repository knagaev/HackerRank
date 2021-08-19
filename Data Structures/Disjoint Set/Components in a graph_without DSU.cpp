#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */

int dfs(int node, const map<int, vector<int>>& adjMatrix, vector<int>& visited)
{
    visited[node] = 1;
    int componentSize = 1;

    auto& nbs = adjMatrix.at(node);

    for (const auto& nb : nbs)
    {
        if (visited[nb] < 0)
            componentSize += dfs(nb, adjMatrix, visited);
    }

    return componentSize;
}

vector<int> componentsInGraph(vector<vector<int>> gb) 
{
    map<int, vector<int>> adjMatrix;

    for (const auto& e : gb)
    {
        adjMatrix[e[0]].push_back(e[1]);
        adjMatrix[e[1]].push_back(e[0]);
    }

    vector<int> visited(2 * gb.size() + 1, -1);

    auto minSize = numeric_limits<int>::max();
    auto maxSize = numeric_limits<int>::min();

    for (const auto& v : adjMatrix)
    {
        if (visited[v.first] < 0)
        {
            auto componentSize = dfs(v.first, adjMatrix, visited);

            if (componentSize > 1)
            {
                minSize = min(minSize, componentSize);
                maxSize = max(maxSize, componentSize);
            }
        }
    }

    return {minSize, maxSize};
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> gb(n);

    for (int i = 0; i < n; i++) {
        gb[i].resize(2);

        string gb_row_temp_temp;
        getline(cin, gb_row_temp_temp);

        vector<string> gb_row_temp = split(rtrim(gb_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int gb_row_item = stoi(gb_row_temp[j]);

            gb[i][j] = gb_row_item;
        }
    }

    vector<int> result = componentsInGraph(gb);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
