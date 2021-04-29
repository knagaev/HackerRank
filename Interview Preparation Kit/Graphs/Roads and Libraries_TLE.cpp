#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

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

    map<int, set<int>> roads;
    for (const auto& link : cities)
    {
        if (roads.find(link[0]) == end(roads))
            roads.insert(make_pair(link[0], set<int>()));
        roads[link[0]].insert(link[1]);
        if (roads.find(link[1]) == end(roads))
            roads.insert(make_pair(link[1], set<int>()));
        roads[link[1]].insert(link[0]);
    }

    set<int> visited;
    deque<int> q;
    long long  total = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        if (visited.find(i) != end(visited)) continue;

        q.push_back(i);
        visited.insert(i);
        while (!q.empty())
        {
            auto curCity = q.front();
            q.pop_front();

            set<int> notVisitedNeighbours;
            set_difference(begin(roads[curCity]), end(roads[curCity]), 
                begin(visited), end(visited),
                inserter(notVisitedNeighbours, begin(notVisitedNeighbours)));

            q.insert(end(q), begin(notVisitedNeighbours), end(notVisitedNeighbours));
            visited.insert(begin(notVisitedNeighbours), end(notVisitedNeighbours));
            total += notVisitedNeighbours.size() * c_road;
        }
        total += c_lib;
    }

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

        long long result = roadsAndLibraries(n, c_lib, c_road, cities);

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
