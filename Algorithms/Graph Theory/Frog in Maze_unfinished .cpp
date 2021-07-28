#include <bits/stdc++.h>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

vector<vector<double>> inverseMatrix(const vector<vector<double>>& matrix)
{
    assert(matrix.size() > 0 && matrix.size() == matrix[0].size());

    const auto N = matrix.size();

    vector<vector<double>> result{matrix};

    vector<vector<double>> identity(N, vector<double>(N, .0));
    for (size_t i = 0; i < N; ++i)
        identity[i][i] = 1.0;

    for (size_t k = 0; k < N; ++k)
    {
        auto temp = result[k][k];

        for (size_t j = 0; j < N; ++j)
        {
            result[k][j] /= temp;
            identity[k][j] /= temp;

        }

        for (size_t i = k + 1; i < N; ++i)
        {
            auto temp = result[i][k];

            for (size_t j = 0; j < N; ++j)
            {
                result[i][j] -= result[k][j] * temp;
                identity[i][j] -= identity[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; --k)
    {
        for (int i = k - 1; i >= 0; --i)
        {
            auto temp = result[i][k];

            for (size_t j = 0; j < N; ++j)
            {
                result[i][j] -= result[k][j] * temp;
                identity[i][j] -= identity[k][j] * temp;
            }
        }
    }

    result = identity;

    return result;
}


int fillMazeMatrix(const vector<string>& maze, const vector<vector<int>>& tunnels,
    vector<vector<double>>& mazeMatrix, set<int>& bombs, set<int>& exits)
{
    const auto n = maze.size();
    const auto m = maze[0].size();

    const auto EXIT = '%';
    const auto BOMB = '*';
    const auto START = 'A';
    const auto WALL = '#';
    const auto EMPTY = 'O';

    mazeMatrix.insert(begin(mazeMatrix), n * m, vector<double>(n * m, 0.));

    int startPoint = -1;
    for (size_t i = 0; i < maze.size(); ++i)
    {
        for (size_t j = 0; j < maze[i].size(); ++j)
        {
            if (maze[i][j] == WALL)
                continue;

            if (maze[i][j] == BOMB)
            {
                bombs.insert(i * m + j);
                continue;
            }

            if (maze[i][j] == EXIT)
            {
                exits.insert(i * m + j);
                continue;
            }

            if (maze[i][j] == START)
            {
                startPoint = i * m + j;
            }

            for (auto y : { -1, 0, 1 })
            {
                if (i + y < 0 || i + y >= n) continue;
                for (auto x : { -1, 0, 1 })
                {
                    if (j + x < 0 || j + x >= m) continue;
                    if (abs(y) + abs(x) != 1) continue;
                    if (maze[i + y][j + x] != WALL)
                    {
                        mazeMatrix[i * m + j][(i + y) * m + (j + x)] = 1;
                    }
                }
            }
        }
    }

    for (const auto& t : tunnels)
    {
        auto t1 = t[0] * m + t[1];
        auto t2 = t[2] * m + t[3];

        for(auto& row : mazeMatrix)
            swap(row[t1], row[t2]);
    }

    for (size_t i = 0; i < mazeMatrix.size(); ++i)
    {
        auto sumRow = (double)accumulate(begin(mazeMatrix[i]), end(mazeMatrix[i]), 0);
        if (sumRow == 0)
            continue;

        for (size_t j = 0; j < mazeMatrix[i].size(); ++j)
        {
            mazeMatrix[i][j] /= sumRow;
        }
    }

    return startPoint;
}

double calcEscapeProb(const vector<string>& maze, const vector<vector<int>>& tunnels)
{
    vector<vector<double>> mazeMatrix;
    set<int> bombs;
    set<int> exits;

    auto startPoint = fillMazeMatrix(maze, tunnels, mazeMatrix, bombs, exits);

    set<int> bombsAndExits{bombs};
    bombsAndExits.insert(begin(exits), end(exits));

    vector<int> nonabsorbingStates;
    auto itAbsorbing = begin(bombsAndExits);
    for (int i = 0; i < mazeMatrix.size(); ++i)
    {
        if (itAbsorbing == end(bombsAndExits) || i < *itAbsorbing)
            nonabsorbingStates.push_back(i);
        else
            ++itAbsorbing;
    }

    vector<vector<double>> fundamentalMatrix;
    for (const auto rnas : nonabsorbingStates)
    {
        vector<double> row;
        for (const auto cnas : nonabsorbingStates)
        {
            row.push_back(mazeMatrix[rnas][cnas]);
        }
        fundamentalMatrix.push_back(row);
    }

    for (size_t i = 0; i < fundamentalMatrix.size(); ++i)
    {
        for (size_t j = 0; j < fundamentalMatrix[i].size(); ++j)
        {
            if (i == j)
                fundamentalMatrix[i][j] = 1 - fundamentalMatrix[i][j];
            else
                fundamentalMatrix[i][j] = -fundamentalMatrix[i][j];
        }
    }

    auto inversedFundamentalMatrix = inverseMatrix(fundamentalMatrix);

    double result = .0;

    auto startPointIndex = distance(begin(nonabsorbingStates), find(begin(nonabsorbingStates), end(nonabsorbingStates), startPoint));
    for (const auto e : exits)
    {
        double prob = .0;
        for (int i = 0; i < inversedFundamentalMatrix.size(); ++i)
        {
            prob += inversedFundamentalMatrix[startPointIndex][i] * mazeMatrix[nonabsorbingStates[i]][e];
        }
        result += prob;
    }

    return result;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);


    vector<string> maze;
    for (int n_itr = 0; n_itr < n; n_itr++) 
    {
        string row;
        getline(cin, row);

        maze.push_back(row);
    }

    vector<vector<int>> tunnels;
    for (int k_itr = 0; k_itr < k; k_itr++) {
        string second_multiple_input_temp;
        getline(cin, second_multiple_input_temp);

        vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

        int i1 = stoi(second_multiple_input[0]);

        int j1 = stoi(second_multiple_input[1]);

        int i2 = stoi(second_multiple_input[2]);

        int j2 = stoi(second_multiple_input[3]);

        tunnels.push_back({i1 - 1, j1 - 1, i2 - 1, j2 - 1});
    }

    cout << calcEscapeProb(maze, tunnels) << endl;

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
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
