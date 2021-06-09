#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'hanoi' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY posts as parameter.
 */

set<array<vector<int>, 4>> possibleNextPositions(const array<vector<int>, 4>& position)
{
    set<array<vector<int>, 4>> result;
    for (size_t i = 0; i < position.size(); ++i)
    {
        if (position[i].empty()) continue;
        for (size_t j = 0; j < position.size(); ++j)
        {
            if (i == j || (!position[j].empty() && position[i].back() > position[j].back())) continue;

            auto newPosition{position};
            newPosition[j].push_back(newPosition[i].back());
            newPosition[i].pop_back();

            sort(next(begin(newPosition)), end(newPosition), 
                [](const auto& lhs, const auto& rhs) 
                { 
                    if (rhs.empty() && lhs.empty()) return false;
                    if (rhs.empty() && !lhs.empty()) return true;
                    if (lhs.empty() && !rhs.empty()) return false;
                    return lhs.back() > rhs.back();
                });
            
            result.insert(newPosition);
        }
    }
    return result;
}


int hanoi(vector<int> posts) 
{
    array<vector<int>, 4> initPosition;

    for (size_t i = 0; i < posts.size(); ++i)
    {
        initPosition[posts[i] - 1].push_back(i + 1);
    }

    for (auto& r : initPosition)
        reverse(begin(r), end(r));

    deque<pair<array<vector<int>, 4>, int>> q({ make_pair(initPosition, 0) });
    set<array<vector<int>, 4>> visited{ initPosition };

    while (!q.empty())
    {
        auto curState = q.front();
        q.pop_front();

        for (const auto& position : possibleNextPositions(curState.first))
        {
            if (visited.find(position) != end(visited)) continue;
            if (position[0].size() == posts.size())
                return curState.second + 1;

            q.push_back(make_pair(position, curState.second + 1));
            visited.insert(position);
        }
    }

    return 0;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string loc_temp_temp;
    getline(cin, loc_temp_temp);

    vector<string> loc_temp = split(rtrim(loc_temp_temp));

    vector<int> loc(n);

    for (int i = 0; i < n; i++) {
        int loc_item = stoi(loc_temp[i]);

        loc[i] = loc_item;
    }

    int res = hanoi(loc);

    fout << res << "\n";

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
