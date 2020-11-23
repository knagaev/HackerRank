#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


vector<string> getStringField(vector<vector<int>> field)
{
    vector<string> result;
    for (const auto& fieldRow : field)
    {
        auto stringRow = accumulate(begin(fieldRow), end(fieldRow),
            string(),
            [](string& acc, const auto& c)
            {
                acc += (c > 3) ? '.' : 'O';
                return acc;
            }
        );
        result.push_back(stringRow);
    }

    return result;
}

// Complete the bomberMan function below.
vector<string> bomberMan(int n, vector<string> grid)
{
    vector<vector<int>> fields[6];
    for (const auto& row : grid)
    {
        vector<int> fieldRow(row.length());
        transform(cbegin(row), cend(row),
            begin(fieldRow),
            [](const auto& c)
            {
                return (c == '.') ? 5 : 3;
            }
        );
        fields[0].push_back(fieldRow);
    }

    for (int t = 1; t < 6; ++t)
    {
        fields[t] = fields[t-1];

        // tick processing
        for (auto& fieldRow : fields[t])
            for (auto& fieldCell : fieldRow)
                --fieldCell;

        //explode processing
        for (size_t i = 0; i < fields[t - 1].size(); ++i)
        {
            for (size_t j = 0; j < fields[t - 1][i].size(); ++j)
            {
                if (fields[t - 1][i][j] == 1)
                {
                    fields[t][i][j] = 4;
                    if (i > 0 && fields[t - 1][i - 1][j] != 0) 
                        fields[t][i - 1][j] = 4;
                    if (i < fields[t - 1].size() - 1 && fields[t - 1][i + 1][j] != 0) 
                        fields[t][i + 1][j] = 4;
                    if (j > 0 && fields[t - 1][i][j - 1] != 0) 
                        fields[t][i][j - 1] = 4;
                    if (j < fields[t - 1][i].size() - 1 && fields[t - 1][i][j + 1] != 0) 
                        fields[t][i][j + 1] = 4;
                }
            }
        }
    }

    if (n > 3)
    {
        if (n % 2 == 0)
            n = 2;
        else
            n = (n + 2) % 4 + 2;
    }

    return getStringField(fields[n]);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string rcn_temp;
    getline(cin, rcn_temp);

    vector<string> rcn = split_string(rcn_temp);

    int r = stoi(rcn[0]);

    int c = stoi(rcn[1]);

    int n = stoi(rcn[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
