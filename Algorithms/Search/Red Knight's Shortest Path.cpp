#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'printShortestPath' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER i_start
 *  3. INTEGER j_start
 *  4. INTEGER i_end
 *  5. INTEGER j_end
 */

vector<array<int, 4>> possibleNextStates(const array<int, 4>& position, int n)
{
    vector<array<int, 4>> result;

    array<pair<int, int>, 6> possibleMoves{ {{-2, -1}, {-2, 1}, {0, 2}, {2, 1}, {2, -1}, {0, -2}} };

    for (auto m : possibleMoves)
    {
        auto newI = position[0] + m.first;
        auto newJ = position[1] + m.second;
        if (newI < 0 || newI >= n || newJ < 0 || newJ >= n) continue;
        result.push_back({newI, newJ, position[0], position[1]});
    }
    return result;
}



void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) 
{
    deque<array<int, 4>> q({ {i_start, j_start, -1, -1} });
    map<pair<int, int>, pair<int, int>> visited = { {{i_start, j_start}, {-1, -1}} };

    while (!q.empty())
    {
        auto curState = q.front();
        q.pop_front();

        for (const auto& state : possibleNextStates(curState, n))
        {
            if (visited.find(make_pair(state[0], state[1])) != end(visited)) continue;
            visited[make_pair(state[0], state[1])] = make_pair(curState[0], curState[1]);

            if (state[0] == i_end && state[1] == j_end)
            {
                map<pair<int, int>, string> moves = { {{-2, -1}, "UL"},
                                                      {{-2, 1}, "UR"},
                                                      {{0, 2}, "R"},
                                                      {{2, 1}, "LR"},
                                                      {{2, -1}, "LL"},
                                                      {{0, -2}, "L"} };
                auto curPosition = make_pair(state[0], state[1]);
                vector<string> result;
                while (true)
                {
                    auto previousPosition = visited[curPosition];

                    if (previousPosition.first == -1 && previousPosition.second == -1)
                    {
                        cout << result.size() << endl;
                        for(auto it = crbegin(result); it != crend(result); ++it)
                            cout << *it << " ";
                        cout << endl;
                        return;
                    }

                    result.push_back(moves[{ curPosition.first - previousPosition.first, curPosition.second - previousPosition.second }]);
                    curPosition = previousPosition;
                }
            }

            q.push_back(state);
        }
    }

    cout << "Impossible" << endl;
    return;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int i_start = stoi(first_multiple_input[0]);

    int j_start = stoi(first_multiple_input[1]);

    int i_end = stoi(first_multiple_input[2]);

    int j_end = stoi(first_multiple_input[3]);

    printShortestPath(n, i_start, j_start, i_end, j_end);

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
