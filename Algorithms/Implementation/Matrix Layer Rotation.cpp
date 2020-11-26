#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<vector<int>> convertToRings(const vector<vector<int>>& matrix)
{
    vector<vector<int>> rings;
    auto numRings = min(matrix.size(), matrix[0].size()) / 2;
    for (size_t i = 0; i < numRings; ++i)
    {
        vector<int> ring(next(cbegin(matrix[i]), i), prev(cend(matrix[i]), i));

        for (auto it = next(cbegin(matrix), i + 1); it != prev(cend(matrix), i + 1); ++it)
        {
            ring.push_back(*prev(cend(*it), i + 1));
        }

        auto bottomRow = *prev(cend(matrix), i + 1);
        for (auto it = next(crbegin(bottomRow), i); it != prev(crend(bottomRow), i); ++it)
        {
            ring.push_back(*it);
        }

        for (auto it = next(crbegin(matrix), i + 1); it != prev(crend(matrix), i + 1); ++it)
        {
            ring.push_back(*next(cbegin(*it), i));
        }

        rings.push_back(ring);
    }

    return rings;
}

vector<vector<int>> convertToMatrix(const vector<vector<int>>& rings, const pair<size_t, size_t>& mn)
{
    //const auto mSize = rings.size() * 2;
    auto m = mn.first;
    auto n = mn.second;

    vector<vector<int>> matrix(m, vector<int>(n));

    for (size_t i = 0; i < rings.size(); ++i)
    {
        for (size_t j = 0; j < n - i * 2; ++j)
        {
            matrix[i][j + i] = rings[i][j];
        }
        for (size_t j = 0; j < m - i * 2 - 2; ++j)
        {
            matrix[i + 1 + j][n - 1 - i] = rings[i][n - i * 2 + j];
        }
        for (size_t j = 0; j < n - i * 2; ++j)
        {
            matrix[m - 1 - i][n - 1 - i - j] = rings[i][n + m - i * 4 - 2 + j];
        }
        for (size_t j = 0; j < m - i * 2 - 2; ++j)
        {
            matrix[m - 2 - i - j][i] = rings[i][2 * n + m  - i * 6 - 2 + j];
        }
    }

    return matrix;
}

// Complete the matrixRotation function below.
void matrixRotation(vector<vector<int>> matrix, int r)
{
    auto rings = convertToRings(matrix);

    for (auto& ring : rings)
    {
        auto adjustedR = r % ring.size();
        rotate(begin(ring), begin(ring) + adjustedR, end(ring));
    }

    auto rotated = convertToMatrix(rings, make_pair(matrix.size(), matrix[0].size()));

    for (const auto& row : rotated)
    {
        for (const auto& c : row)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    return;
}

int main()
{
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);

    int n = stoi(mnr[1]);

    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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
