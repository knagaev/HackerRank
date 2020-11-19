#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumDistances function below.
int minimumDistances(vector<int> a) 
{
   map<int, vector<size_t>> positions;

    for (size_t i = 0; i < a.size(); ++i)
    {
        positions[a[i]].push_back(i);
    }

    auto minDistances = accumulate(begin(positions), end(positions), 
        vector<size_t>(),
        [](auto& acc, const auto& p) 
        {
            const auto& elementPositions(p.second);
            if (elementPositions.size() < 2) return acc;
            vector<size_t> distances;
            transform(begin(elementPositions), prev(end(elementPositions)),
                next(begin(elementPositions)),
                back_inserter(distances),
                [](const auto& lhs, const auto& rhs)
                {
                    return rhs - lhs;
                }
            );

            acc.push_back(*min_element(begin(distances), end(distances)));
            return acc;
        }
    );

    return minDistances.empty() ? -1 : static_cast<int>(*min_element(begin(minDistances), end(minDistances)));

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = minimumDistances(a);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
