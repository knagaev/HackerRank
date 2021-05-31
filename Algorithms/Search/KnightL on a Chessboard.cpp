#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'knightlOnAChessboard' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER n as parameter.
 */

vector<pair<int, int>> getNewPositions(int n, pair<int, int> pos, pair<int, int> offset)
{
    vector<pair<int, int>> steps;

    for (auto inverse : { true, false })
    {
        auto iOffset = inverse ? offset.second : offset.first;
        auto jOffset = inverse ? offset.first : offset.second;

        for (auto i : { -1, 1 })
        {
            for (auto j : { -1, 1 })
            {
                auto step = make_pair(pos.first + iOffset * i, pos.second + jOffset * j);
                if (step.first >= 0 &&
                    step.first < n &&
                    step.second >= 0 &&
                    step.second < n)
                {
                    steps.push_back(step);
                }

            }
        }
    }
    return steps;
}

int getBfsQty(int n, pair<int, int> offset)
{
    auto startPosition = make_pair(0, 0);
    deque<pair<pair<int, int>, int>> q{ make_pair(startPosition, 0) };
    set<pair<int, int>> used{ startPosition };

    while (!q.empty())
    {
        auto curStatus = q.front();
        q.pop_front();

        auto newPositions = getNewPositions(n, curStatus.first, offset);
        for (const auto& np : newPositions)
        {
            if (np.first == n - 1 && np.second == n - 1)
                return curStatus.second + 1;

            if (used.find(np) == end(used))
            {
                q.push_back(make_pair(np, curStatus.second + 1));
                used.insert(np);
            }
        }
    }
    
    return -1;
}

vector<vector<int>> knightlOnAChessboard(int n)
{
    vector<vector<int>> result(n - 1, vector<int>(n - 1));

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i; j < n - 1; ++j)
        {
            result[i][j] = getBfsQty(n, make_pair(i + 1, j + 1));
        }
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            result[i][j] = result[j][i];
        }
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
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
